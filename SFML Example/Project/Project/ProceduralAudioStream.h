#pragma once
#include <vector>

#include "SFML/Audio.hpp"
using namespace sf;

class ProceduralAudioStream : public sf::SoundStream
{
public:
	ProceduralAudioStream();
	//void Init(unsigned int channelCount, unsigned int sampleRate);
	void load(const sf::SoundBuffer& buffer);
	
private:


	virtual bool onGetData(Chunk& data);

	virtual void onSeek(sf::Time timeOffset) {};

	std::vector<sf::Int16> samples;
	size_t currentSample;

	float chunkDuraton;

	int sampleRate;
};