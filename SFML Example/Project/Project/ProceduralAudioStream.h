#pragma once
#include <vector>
#include <memory>
#include <mutex>
#include "SFML/Audio.hpp"
#include "AudioGenerator.h"
#include <thread>
//using namespace sf;

class ProceduralAudioStream : public sf::SoundStream
{
public:
	ProceduralAudioStream();
	~ProceduralAudioStream();

	//void Init(unsigned int channelCount, unsigned int sampleRate);
	
private:
	//void Init(std::unique_ptr<AudioGenerator> audioGeneratorPrt);
	void loadToSamples();

	std::shared_ptr<AudioGenerator> audioGenerator;
	std::shared_ptr<std::mutex> hotBufferMutex;

	virtual bool onGetData(Chunk& data);

	virtual void onSeek(sf::Time timeOffset) {};

	//std::unique_ptr<std::thread> generatorThread;
	std::thread generatorThread;


	std::vector<sf::Int16> samples;
	size_t currentSample;

	float chunkDuraton;

	int sampleRate;
};