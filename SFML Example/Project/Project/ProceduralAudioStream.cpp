#include "ProceduralAudioStream.h"




ProceduralAudioStream::ProceduralAudioStream() :
	// initial values
	chunkDuraton(1),
	// default values
	currentSample(0),
	sampleRate(44100)
{
}

// standard load from https://www.sfml-dev.org/tutorials/2.5/audio-streams.php
void ProceduralAudioStream::load(const sf::SoundBuffer& buffer)
{
	// extract the audio samples from the sound buffer to our own container
	samples.assign(buffer.getSamples(), buffer.getSamples() + buffer.getSampleCount());

	// reset the current playing position 
	currentSample = 0;

	sampleRate = buffer.getSampleRate();
	
	// initialize the base class
	SoundStream::initialize(buffer.getChannelCount(),sampleRate);

}

// standard onGetData from https://www.sfml-dev.org/tutorials/2.5/audio-streams.php
bool ProceduralAudioStream::onGetData(Chunk& data)
{
	// number of samples to stream every time the function is called;
	   // in a more robust implementation, it should be a fixed
	   // amount of time rather than an arbitrary number of samples

	const int samplesToStream = sampleRate * chunkDuraton; // (chunk duration) seconds of samples per chunk

	// set the pointer to the next audio samples to be played
	data.samples = &samples[currentSample];

	// have we reached the end of the sound?
	if (currentSample + samplesToStream <= samples.size())
	{
		// end not reached: stream the samples and continue
		data.sampleCount = samplesToStream;
		currentSample += samplesToStream;
		return true;
	}
	else
	{
		// end of stream reached: stream the remaining samples and stop playback
		data.sampleCount = 0;
		currentSample = samples.size();
		return false;
	}
}
