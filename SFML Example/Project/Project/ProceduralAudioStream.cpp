#include "ProceduralAudioStream.h"




ProceduralAudioStream::ProceduralAudioStream() 
	// owned objects
	: audioGenerator(std::make_shared< AudioGenerator>())
	, hotBufferMutex(audioGenerator->GetBufferMutex())

	//, generatorThread(new std::thread(&AudioGenerator::MainGeneration,audioGenerator))
	// initial values
	,chunkDuraton(1)
	// default values
	,currentSample(0)
	,sampleRate(44100)
	
{
	SoundStream::initialize(1, sampleRate);
	//generatorThread
	generatorThread = std::thread ( &AudioGenerator::MainGeneration, audioGenerator );
	
}

ProceduralAudioStream::~ProceduralAudioStream()
{
	generatorThread.join();
	audioGenerator->End();
}

void ProceduralAudioStream::Begin()
{
	audioGenerator->Begin();
	loadToSamples();
	play();
}






void ProceduralAudioStream::loadToSamples()
{
	std::lock_guard<std::mutex> lock(*hotBufferMutex); // raii mutex as audio stream is threaded
	auto buffer = audioGenerator->LoadFromHotBuffer();
	samples.assign(buffer->getSamples(), buffer->getSamples() + buffer->getSampleCount());
	audioGenerator->FinishedWithHotBuffer(move(buffer));
}

// based on standard onGetData from https://www.sfml-dev.org/tutorials/2.5/audio-streams.php
bool ProceduralAudioStream::onGetData(Chunk& data)
{
	

	int samplesToStream = sampleRate * chunkDuraton; // 44100 (chunk duration) seconds of samples per chunk

	// set the pointer to the next audio samples to be played
	

	// can't stream full chunk
	if (currentSample + samplesToStream >= samples.size()) {
		if (currentSample < samples.size()-1) // stream whatever's left
		{
			samplesToStream = samples.size() - currentSample-1;
			data.samples = &samples[currentSample];
			//currentSample = samples.size();
		}
		else // nothing else to stream
		{
			loadToSamples();
			currentSample = 0;
			data.samples = &samples[currentSample];
		}
	}
	else {
		data.samples = &samples[currentSample];
	}


	data.sampleCount = samplesToStream;
	currentSample += samplesToStream;
	return true;

}
