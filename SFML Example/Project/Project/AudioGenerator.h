#pragma once
#include "SFML/Audio.hpp"
#include <memory>
#include <mutex>
#include <condition_variable>
#define PI 3.1415



using namespace sf;
class AudioGenerator
{
public:
	AudioGenerator();

	//void GenerateAudio(sf::Int16* buffer, const int numberOfSamples);
	std::unique_ptr<const sf::SoundBuffer> LoadFromHotBuffer();
	void FinishedWithHotBuffer(std::unique_ptr<const sf::SoundBuffer>);

	void ClearBuffer();

	//void setSampleRate(float val);
	void trigger(float pitch, int sample);

	void FillBuffer();
	std::shared_ptr<std::mutex> GetBufferMutex() { return hotbufferMutex; };

private:
	void GenerateNote(float pitch, int startSampleIndex);
	const float sampleRate;
	const float bps;
	const int noteSize;
	const int chunksPerBuffer;
	const int bufferSize;

	bool bufferReady;
	std::condition_variable bufferReadyCv;
	std::mutex bufferReadyMutex;
	
	std::condition_variable bufferSentCv;
	std::mutex bufferSentMutex;
	bool bufferSent;


	std::shared_ptr<std::mutex> hotbufferMutex;
	struct preBuffer
	{

	};

	//float frequency;

//	int startSample;

//	float sinIndex = 0; // ?? 
//	float sinIncriment = 0.01; // ?? 440 / 44100 
	//float ampIndex = 0;

	std::unique_ptr<const SoundBuffer> hotBuffer;
	std::unique_ptr<SoundBuffer> backBuffer;

	sf::SoundBuffer buffer1;
	sf::SoundBuffer buffer2;

	


};

