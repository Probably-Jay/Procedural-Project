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
	std::unique_ptr<sf::SoundBuffer> LoadFromHotBuffer();
	void FinishedWithHotBuffer(std::unique_ptr<sf::SoundBuffer>);



	void FillBuffer();
	std::shared_ptr<std::mutex> GetBufferMutex() { return hotbufferMutex; };

	void MainGeneration();
private:
	void InitialGeneration();
	void Generate();

	void CleanBackBuffer();
	void GenerateNote(float pitch, int startSampleIndex);
	const float sampleRate;
	const float bps;
	const int noteSize;
	const int chunksPerBuffer;
	const int bufferSize;


	//void setSampleRate(float val);
	void trigger(float pitch, int sample);

	bool bufferReady;
	std::condition_variable bufferReadyCv;
	std::mutex bufferReadyMutex;
	
	std::condition_variable bufferSentCv;
	std::mutex bufferSentMutex;
	bool bufferSent;

	bool running;

	std::shared_ptr<std::mutex> hotbufferMutex;
	


	//float frequency;

//	int startSample;

//	float sinIndex = 0; // ?? 
//	float sinIncriment = 0.01; // ?? 440 / 44100 
	//float ampIndex = 0;

	std::unique_ptr<SoundBuffer> hotBuffer;
	std::unique_ptr<SoundBuffer> backBuffer;

	sf::SoundBuffer buffer1;
	sf::SoundBuffer buffer2;

	


};

