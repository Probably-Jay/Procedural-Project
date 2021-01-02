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

	void Begin();
	
private:
	void loadToSamples();

	std::shared_ptr<AudioGenerator> audioGenerator;
	std::shared_ptr<std::mutex> hotBufferMutex;

	virtual bool onGetData(sf::SoundStream::Chunk& data);

	virtual void onSeek(sf::Time timeOffset) {}; // overload unused pure virtual function

	std::thread generatorThread;


	std::vector<sf::Int16> samples;
	size_t currentSample;

	float chunkDuraton;

	int sampleRate;
};