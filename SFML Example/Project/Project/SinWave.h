#pragma once
#include "SFML/Audio.hpp"
#define PI 3.1415
class SinWave
{
public:
	SinWave();

	void GenerateAudio(sf::Int16* buffer, const int numberOfSamples);

	void setSampleRate(float val);
	void trigger(float pitch, int sample);

private:
	float sampleRate;

	float frequency;

	int startSample;

	float sinIndex = 0; // ?? 
	float sinIncriment = 0.01; // ?? 440 / 44100 
	float ampIndex = 0;

};

