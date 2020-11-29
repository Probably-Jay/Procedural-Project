#pragma once
#include "SFML/Audio.hpp"
#include <memory>
#define PI 3.1415
using namespace sf;
class AudioGenerator
{
public:
	AudioGenerator();

	void GenerateAudio(sf::Int16* buffer, const int numberOfSamples);

	void setSampleRate(float val);
	void trigger(float pitch, int sample);

	void FillBuffer();

private:
	const float sampleRate;
	const int bpm;


	struct preBuffer
	{

	};

	float frequency;

	int startSample;

	float sinIndex = 0; // ?? 
	float sinIncriment = 0.01; // ?? 440 / 44100 
	float ampIndex = 0;

	std::unique_ptr<SoundBuffer> hotBuffer;
	std::unique_ptr<SoundBuffer> backBuffer;

	sf::SoundBuffer buffer1;
	sf::SoundBuffer buffer2;

	


};

