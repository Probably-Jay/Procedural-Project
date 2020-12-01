#include "AudioGenerator.h"

//const float AudioGenerator::sampleRate = 44100;
//const float AudioGenerator::bps = 2;
//const int AudioGenerator::samplesPerNote = AudioGenerator::sampleRate * 1.f / AudioGenerator::bps;
//const int AudioGenerator::chunksPerBuffer = 4;
//const int AudioGenerator::bufferSize = AudioGenerator::chunksPerBuffer * AudioGenerator::sampleRate;

AudioGenerator::AudioGenerator()
	: hotBuffer(&buffer1)
	, backBuffer(&buffer2)
	//, bps(BPS)
	, began(false)
	, ended(false)
	, bufferReady(false)
	, bufferSent(true) // init both buffers
	, sampleArray()
{
	hotbufferMutex = std::make_unique<std::mutex>();
	sinIndex = 0;

}

void AudioGenerator::Begin()
{
	ended = false;
	began = true;
	beginCv.notify_one();
}


void AudioGenerator::End()
{
	ended = true;
	// in unlikley event somehow stuck at barrier
	bufferSent = true;
	bufferSentCv.notify_all();

	bufferReady = true;
	bufferReadyCv.notify_all();

	began = true;
	beginCv.notify_all();
}


void AudioGenerator::MainGeneration()
{
	std::unique_lock<std::mutex> lk(beginMutex);
	beginCv.wait(lk, [this] {return this->began; }); // wait for signal to begin

	//InitialGeneration();
	while (!ended) {
		CleanSampleArray();
		Generate();
		FillBackBuffer();
		SwapBuffers(); // execution suspends here if not ready for more
	}
}

void AudioGenerator::CleanSampleArray()
{
	std::fill(std::begin(sampleArray), std::end(sampleArray), 0);
}


void AudioGenerator::Generate()
{
	std::vector<float> pitches = {
		  440 * powf(2, 0/12.f)
		, 440 * powf(2, 2/12.f)
		, 440 * powf(2, 4/12.f)
		, 440 * powf(2, 7/12.f)
		, 440 * powf(2, 9/12.f)
					    
		, 440 * powf(2, 0/12.f)
		, 440 * powf(2, 2/12.f)
		, 440 * powf(2, 4/12.f)
		, 440 * powf(2, 7/12.f)
		, 440 * powf(2, 9/12.f)
					    
		, 440 * powf(2, 0/12.f)
		, 440 * powf(2, 2/12.f)
		, 440 * powf(2, 4/12.f)
		, 440 * powf(2, 7/12.f)
		, 440 * powf(2, 9/12.f)
					    
		, 440 * powf(2, 0 / 12.f)
		, 440 * powf(2, 4 / 12.f)

		, 440 * powf(2, 5/12.f)
		, 440 * powf(2, 11/12.f)
	};
	srand(time(0));
	for (size_t i = 0; i < NOTESPERCHUNK; i++)
	{

		GenerateNote(pitches[rand()% pitches.size()], i * SAMPLESPERNOTE_s);
	}


}

// adapted from lecture
void AudioGenerator::GenerateNote(float pitch, int startSampleIndex)
{
	//int envelopeIndex = 0;
	//float sinIndex = startSampleIndex;
	const float sinIncrimentValue = (2.f * PI * pitch) / (float)SAMPLERATE;
	const int samplesPerNote = SAMPLESPERNOTE_s;

	// amp envelope shape
	const int attack = startSampleIndex + (0.02f) * samplesPerNote;	// 0.023 %
	const int decay = (0.9f) * samplesPerNote;	// 90.7 %
	const int silence = startSampleIndex + (samplesPerNote - (attack + decay));



	//const int sanity = startSampleIndex+samplesPerNote - (attack + decay);

	const float envelopeFactor = 0.33f;

	for (size_t i = startSampleIndex; i < startSampleIndex + samplesPerNote; i++)
	{
		if (i < (attack + decay)) // silence
		{
			float audio = sinf(sinIndex);

			sinIndex += sinIncrimentValue;
			if (sinIndex > 2 * 3.14f) sinIndex = 0;

			float ampEnvelope = 0;

			if (i < attack) {
				ampEnvelope = Lerp(0, 1, InvLerp(0, attack, i));
			}
			else if (i < (attack + decay)) {
				//float p =
				ampEnvelope = Lerp(1, 0, InvLerp(attack, (attack + decay), i));
			}

			audio *= ampEnvelope * envelopeFactor;

			if (i < sampleArray.size()) {
				sampleArray[i] += audio;
			}

		}
	}
}


void AudioGenerator::FillBackBuffer()
{
	for (size_t i = 0; i < sampleArray.size(); i++)
	{
		sampleArray[i] = Clamp(sampleArray[i],-1, 1 );
		samplePreBuffer[i] = sampleArray[i] * (sf::Int16)(0.4999 * std::numeric_limits<sf::Int16>::max()); // un-normalise volume for sfml
	}	

	backBuffer->loadFromSamples(
		samplePreBuffer.data(),
		sampleArray.size(),
		1,
		SAMPLERATE
	);
}

void AudioGenerator::SwapBuffers()
{
	// if last hot buffer has not been sent yet, suspend here
	std::unique_lock<std::mutex> lock(bufferSentMutex);
	bufferSentCv.wait(lock, [this] {return bufferSent; });
	lock.unlock();

	// mutex to modify hot buffer, just in case
	std::unique_lock<std::mutex> lk(*hotbufferMutex);
	hotBuffer.swap(backBuffer);
	lk.unlock();

	// signal that the hot buffer can not be sent
	bufferReady = true;
	bufferReadyCv.notify_one(); // signal that the hot buffer can be read
}

std::unique_ptr<sf::SoundBuffer> AudioGenerator::LoadFromHotBuffer()
{
	hotbufferMutex->unlock(); // we might get stuck here
	std::unique_lock<std::mutex> lock(bufferReadyMutex);
	bufferReadyCv.wait(lock, [this] {return this->bufferReady; });
	hotbufferMutex->lock();
	bufferReady = false;
 
	lock.unlock();
	return std::move(hotBuffer);
}

void AudioGenerator::FinishedWithHotBuffer(std::unique_ptr<sf::SoundBuffer> buffer)
{
	hotBuffer.swap(buffer);

	bufferSent = true;
	bufferSentCv.notify_one();
}


void AudioGenerator::InitialGeneration()
{
	CleanSampleArray();
	Generate();
	FillBackBuffer();

	throw;
}


void AudioGenerator::FillBuffer()
{
}

//void AudioGenerator::trigger(float pitch, int sample)
//{
//	frequency = pitch;
//	sinIncriment = (2 * PI * frequency) / sampleRate;
//
//	ampIndex = 0;
//	startSample = sample; 
//}



// from lecture
//void AudioGenerator::GenerateAudio(sf::Int16* buffer, const int numberOfSamples)
//{
//
//	for (size_t i = startSample; i < numberOfSamples; i++)
//	{
//		if (ampIndex < 2)
//		{
//			float audio = sinf(sinIndex);
//
//			sinIndex += sinIncriment;
//			if (sinIndex > 2 * 3.14f) sinIndex = 0;
//
//			float ampEnvelope;
//
//			if (ampIndex < 1.f) {
//				ampEnvelope = ampIndex;
//				ampIndex += 0.1f;
//			}
//			else if (ampIndex < 2.f) {
//				ampEnvelope = 1.f - (ampIndex - 1.f);
//				ampIndex += 0.00005f;
//			}
//
//			audio *= ampEnvelope * 0.33f;
//
//			buffer[i] += (audio*32000);
//
//		}
//
//	}
//	startSample = 0;
//}


