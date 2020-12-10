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

	std::fill(std::begin(sampleArray), std::end(sampleArray), 0); // clean the sample array

	//InitialGeneration();
	while (!ended) {
		Generate();
		FillBackBuffer();
		SwapBuffers(); // execution suspends here if not ready for more
		FillOverflow();
	}
}

void AudioGenerator::FillOverflow()
{
	// copy anything past the end of the buffer to the beggining of this ons
	for (size_t i = 0; i < BUFFERSIZE; i++)
	{
		sampleArray[i] = sampleArray[i + BUFFERSIZE];
	}

	// clean the end of the buffer
	for (size_t i = BUFFERSIZE; i < 2*BUFFERSIZE; i++)
	{
		sampleArray[i] = 0;
	}
}


void AudioGenerator::Generate()
{
	
	std::vector<float> notes = {
		  440 * powf(2, 0/12.f)
		, 440 * powf(2, 2/12.f)
		, 440 * powf(2, 4/12.f)
		, 440 * powf(2, 5 / 12.f)
		, 440 * powf(2, 7/12.f)
		, 440 * powf(2, 9/12.f)
		, 440 * powf(2, 11 / 12.f)
	};

	enum class NoteEnum
	{
		A = 0,
		B,
		Cs,
		D,
		E,
		Fs,
		G,
	};

	enum class ChordsEnum {
		A,
		D,
		E,
	};

	std::vector<NoteEnum> penta = {
		NoteEnum::A,
		NoteEnum::B,
		NoteEnum::Cs,
		NoteEnum::E,
		NoteEnum::Fs,
	};

	std::vector<NoteEnum> spicy = {
		NoteEnum::D,
		NoteEnum::G
	};

	std::vector<std::vector<float>> chords = {
		{notes[(int)NoteEnum::A],	notes[(int)NoteEnum::Cs],	notes[(int)NoteEnum::E]},
		{notes[(int)NoteEnum::D],	notes[(int)NoteEnum::Fs],	notes[(int)NoteEnum::A]},
		{notes[(int)NoteEnum::E],	notes[(int)NoteEnum::G],	notes[(int)NoteEnum::B]},
	};

	std::vector<ChordsEnum> Amaj = {
		ChordsEnum::A,
		ChordsEnum::D,
		ChordsEnum::E,
	};


	srand(time(0));
	for (size_t i = 0; i < NOTESPERCHUNK; i++)
	{
		int index;
		int r = rand() % 10;
		const int noteSize = SAMPLESPERNOTE_s * 1;
		if (r<5) {
			index = (int)penta[rand() % penta.size()];
			GenerateNote(notes[index], i* noteSize, noteSize);
		}
		else if (r < 7){
			index = (int)spicy[rand() % spicy.size()];
			GenerateNote(notes[index], i* noteSize, noteSize);
		}
		else {

		}
		
		
	}

	for (size_t i = 0; i < NOTESPERCHUNK/4; i++)
	{
		int index = rand() % Amaj.size();
		const int noteSize = SAMPLESPERNOTE_s * 4;
		for (size_t j = 0; j < 3; j++)
		{
			GenerateNote(chords[index][j], i * noteSize, noteSize);

		}
	}


}

// adapted from lecture
void AudioGenerator::GenerateNote(float pitch, int startSampleIndex,const int samplesPerNote)
{
	const float incrimentValue = (2.f * PI * pitch) / (float)SAMPLERATE;

	// amp envelope
	const int attack = startSampleIndex + (0.02f) * samplesPerNote;	// 0.023 %
	const int decay = (0.9f) * samplesPerNote;	// 90.7 %

	const float envelopeFactor = 0.33f;

	GenerateSamples(startSampleIndex, samplesPerNote, attack, decay, incrimentValue, envelopeFactor);
}

void AudioGenerator::GenerateSamples(int startSampleIndex, const int samplesPerNote, const int attack, const int& decay, const float  sinIncrimentValue, const float envelopeFactor)
{
	float index = 0;
	for (size_t i = startSampleIndex; i < startSampleIndex + samplesPerNote; i++)
	{
		if (i < (attack + decay)) // silence
		{
			float audio = SquareWave(index, sinIncrimentValue);


			FillSamples(i, attack, decay, audio, envelopeFactor);

		}
	}
}

float AudioGenerator::SinWave(float& index, const float incrimentValue)
{
	float audio  = sinf(index);

	index += incrimentValue;
	if (index > 2 * 3.14f) index = 0;
	return audio;
}

float AudioGenerator::SawWave(float& index, const float incrimentValue)
{
	float audio = -1 + index;

	index += incrimentValue;
	if (index > 2) index = 0;
	return audio;
}

float AudioGenerator::SquareWave(float& index, const float incrimentValue)
{
	float audio = index < 1 ? -1 : 1;

	index += incrimentValue;
	if (index > 2) index = 0;
	return audio;
}

float AudioGenerator::TriangleWave(float& index, const float incrimentValue)
{
	float audio = index < 1 ? -1 : 1;

	index += incrimentValue;
	if (index > 2) index = 0;
	return audio;
}





void AudioGenerator::FillSamples(const size_t i, const int attack, const int decay, float audio, const float envelopeFactor)
{
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


void AudioGenerator::FillBackBuffer()
{
	for (size_t i = 0; i < BUFFERSIZE; i++)
	{
		sampleArray[i] = Clamp(sampleArray[i],-1, 1 );
		samplePreBuffer[i] = sampleArray[i] * (sf::Int16)(0.4999 * std::numeric_limits<sf::Int16>::max()); // un-normalise volume for sfml
	}	

	backBuffer->loadFromSamples(
		samplePreBuffer.data(),
		samplePreBuffer.size(),
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
	FillOverflow();
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


