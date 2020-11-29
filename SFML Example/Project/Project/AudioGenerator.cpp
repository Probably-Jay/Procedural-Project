#include "AudioGenerator.h"

AudioGenerator::AudioGenerator()
	: sampleRate(44100)
	, bpm
{
}

// from lecture
void AudioGenerator::GenerateAudio(sf::Int16* buffer, const int numberOfSamples)
{

	for (size_t i = startSample; i < numberOfSamples; i++)
	{
		if (ampIndex < 2)
		{
			float audio = sinf(sinIndex);

			sinIndex += sinIncriment;
			if (sinIndex > 2 * 3.14f) sinIndex = 0;

			float ampEnvelope;

			if (ampIndex < 1.f) {
				ampEnvelope = ampIndex;
				ampIndex += 0.1f;
			}
			else if (ampIndex < 2.f) {
				ampEnvelope = 1.f - (ampIndex - 1.f);
				ampIndex += 0.00005f;
			}

			audio *= ampEnvelope * 0.33f;

			buffer[i] += (audio*32000);

		}

	}
	startSample = 0;
}

void AudioGenerator::setSampleRate(float val)
{
	sampleRate = val;

	sinIncriment = (2 * PI * frequency) / sampleRate;
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
