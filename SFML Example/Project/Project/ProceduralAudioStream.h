#pragma once
#include <vector>
#include <memory>
#include <mutex>
#include "SFML/Audio.hpp"
#include "AudioGenerator.h"
//using namespace sf;

class ProceduralAudioStream : public sf::SoundStream
{
public:
	ProceduralAudioStream();

	//void Init(unsigned int channelCount, unsigned int sampleRate);
	
private:
	//void Init(std::unique_ptr<AudioGenerator> audioGeneratorPrt);
	void loadToSamples();

	std::unique_ptr<AudioGenerator> audioGenerator;
	std::shared_ptr<std::mutex> hotBufferMutex;

	virtual bool onGetData(Chunk& data);

	virtual void onSeek(sf::Time timeOffset) {};


	std::vector<sf::Int16> samples;
	size_t currentSample;

	float chunkDuraton;

	int sampleRate;
};