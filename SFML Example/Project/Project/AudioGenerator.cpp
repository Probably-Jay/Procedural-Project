#include "AudioGenerator.h"

AudioGenerator::AudioGenerator()
	: sampleRate(44100)
	, bps(2)
	, noteSize(sampleRate * 1.f/bps)
	, chunksPerBuffer(4)
	, bufferSize(chunksPerBuffer * sampleRate)
	, hotBuffer(&buffer1)
	, backBuffer(&buffer2)
{
	hotbufferMutex = std::shared_ptr<std::mutex>();
	//MainGeneration();
}

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


// adapted from lecture
void AudioGenerator::GenerateNote(float pitch, int startSampleIndex)
{
	int sinIndex = 0;
	int envelopeIndex = 0;
	int sinIncrimentValue = (2 * PI * pitch) / sampleRate;
	for (size_t i = startSampleIndex; i < startSampleIndex + noteSize; i++)
	{
		if (envelopeIndex < 2)
		{
			float audio = sinf(sinIndex);

			sinIndex += sinIncrimentValue;
			if (sinIndex > 2 * 3.14f) sinIndex = 0;

			float ampEnvelope;

			if (envelopeIndex < 1.f) {
				ampEnvelope = envelopeIndex;
				envelopeIndex += 0.1f;
			}
			else if (envelopeIndex < 2.f) {
				ampEnvelope = 1.f - (envelopeIndex - 1.f);
				envelopeIndex += 0.00005f;
			}

			audio *= ampEnvelope * 0.33f;

		//	buffer[i] += (audio*32000);

		}

	}
	startSampleIndex = 0;
}





std::unique_ptr<sf::SoundBuffer> AudioGenerator::LoadFromHotBuffer()
{
	std::unique_lock<std::mutex> lock(bufferReadyMutex);
	bufferReadyCv.wait(lock, [this] {return this->bufferReady; });
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



void AudioGenerator::MainGeneration()
{
	running = true;
	InitialGeneration();
	while (running) {
		Generate();
	}
}

void AudioGenerator::InitialGeneration()
{
}

void AudioGenerator::Generate()
{
	CleanBackBuffer();
	/*
		do generation on back buffer
	*/
	std::unique_lock<std::mutex> lock(bufferSentMutex);
	bufferSentCv.wait(lock, [this] {return bufferSent; });
	
	//backBuffer.swap(std::make_unique<sf::SoundBuffer>(&hotBuffer));
	hotBuffer.swap(backBuffer);

	

	lock.unlock();
}

void AudioGenerator::CleanBackBuffer()
{
	//backBuffer->loadFromSamples()
}




//void AudioGenerator::trigger(float pitch, int sample)
//{
//	frequency = pitch;
//	sinIncriment = (2 * PI * frequency) / sampleRate;
//
//	ampIndex = 0;
//	startSample = sample; 
//}

void AudioGenerator::FillBuffer()
{
}
