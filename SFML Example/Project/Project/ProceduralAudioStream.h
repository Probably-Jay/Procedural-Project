#pragma once

#include "SFML/Audio.hpp"
using namespace sf;

class ProceduralAudioStream : public sf::SoundStream
{
	virtual bool onGetData(Chunk& data);

	virtual void onSeek(sf::Time timeOffset) {};
};