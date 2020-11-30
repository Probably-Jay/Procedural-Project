#include "ProceduralAudioStream.h"




ProceduralAudioStream::ProceduralAudioStream() 
	// owned objects
	: audioGenerator(std::make_unique< AudioGenerator>())
	, hotBufferMutex(audioGenerator->GetBufferMutex())
	// initial values
	,chunkDuraton(1)
	// default values
	,currentSample(0)
	,sampleRate(44100)
{
	SoundStream::initialize(1, sampleRate);
}




// based off standard load from https://www.sfml-dev.org/tutorials/2.5/audio-streams.php
// made threadsafe by me
void ProceduralAudioStream::load(const sf::SoundBuffer& hotBuffer)
{
	std::lock_guard<std::mutex> lock(*hotBufferMutex); // raii mutex as audio stream is threaded

	// extract the audio samples from the sound buffer to our own container

	// reset the current playing position 
	currentSample = 0;

}
	

void ProceduralAudioStream::loadToSamples()
{
	std::lock_guard<std::mutex> lock(*hotBufferMutex); // raii mutex as audio stream is threaded
	auto buffer = audioGenerator->GetHotBuffer();
	samples.assign(buffer->getSamples(), buffer->getSamples() + buffer->getSampleCount());
}

// standard onGetData from https://www.sfml-dev.org/tutorials/2.5/audio-streams.php
bool ProceduralAudioStream::onGetData(Chunk& data)
{
	

	int samplesToStream = sampleRate * chunkDuraton; // 44100 (chunk duration) seconds of samples per chunk

	// set the pointer to the next audio samples to be played
	data.samples = &samples[currentSample];

	// can't stream full chunk
	if (currentSample + samplesToStream > samples.size()) {
		if (currentSample < samples.size()) // stream whatever's left
		{
			samplesToStream = samples.size() - currentSample;
			currentSample = samples.size();
		}
		else // nothing else to stream
		{
			loadToSamples();
			currentSample = 0;
		}
	}


	data.sampleCount = samplesToStream;
	currentSample += samplesToStream;
	return true;

}
