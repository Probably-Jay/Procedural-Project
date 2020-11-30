#include "AudioGenerator.h"

AudioGenerator::AudioGenerator()
	: sampleRate(44100)
	, bps(2)
	, noteSize(sampleRate * 1.f/bps)
	, chunksPerBuffer(4)
	, bufferSize(chunksPerBuffer * sampleRate)
{
	hotbufferMutex = std::shared_ptr<std::mutex>();
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

			buffer[i] += (audio*32000);

		}

	}
	startSampleIndex = 0;
}





std::unique_ptr<const sf::SoundBuffer> AudioGenerator::LoadFromHotBuffer()
{
	std::unique_lock<std::mutex> lock(bufferReadyMutex);
	bufferReadyCv.wait(lock, [this] {return this->bufferReady; });
	bufferReady = false;
	//sf::SoundBuffer temp = *hotBuffer; // as soon as we signal the cv then hotBuffer will be swapped

	//bufferSent = true;
	lock.unlock();
	return std::move(hotBuffer);
}

void AudioGenerator::FinishedWithHotBuffer()
{
}

void AudioGenerator::ClearBuffer()
{
	for(backBuffer)
}




void AudioGenerator::trigger(float pitch, int sample)
{
	frequency = pitch;
	sinIncriment = (2 * PI * frequency) / sampleRate;

	ampIndex = 0;
	startSample = sample; 
}

void AudioGenerator::FillBuffer()
{
}
