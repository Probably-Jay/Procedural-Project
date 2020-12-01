#pragma once
#include "SFML/Audio.hpp"
#include <memory>
#include <mutex>
#include <array>
#include <condition_variable> 
#include "StandardAlgorithms.h"
constexpr auto PI = 3.1415f;
 
constexpr float SAMPLERATE = 44100.f;
//constexpr auto BPS = 0.0125;
constexpr float SAMPLESPERNOTE_s = SAMPLERATE ;
constexpr auto CHUNKSPERBUFFER = 4;
constexpr size_t BUFFERSIZE = CHUNKSPERBUFFER * SAMPLERATE;
constexpr size_t NOTESPERCHUNK =  BUFFERSIZE / SAMPLESPERNOTE_s ;


using namespace sf;
class AudioGenerator
{
public:
	AudioGenerator();

	//void GenerateAudio(sf::Int16* buffer, const int numberOfSamples);
	std::unique_ptr<sf::SoundBuffer> LoadFromHotBuffer();
	void FinishedWithHotBuffer(std::unique_ptr<sf::SoundBuffer>);

	void Begin();

	void FillBuffer();
	std::shared_ptr<std::mutex> GetBufferMutex() { return hotbufferMutex; };
	void MainGeneration();
	void SwapBuffers();
	void End();
private:
	void InitialGeneration();
	void Generate();

	void FillBackBuffer();
	void CleanSampleArray();
	void GenerateNote(float pitch, int startSampleIndex);

	//const float sampleRate;
	float bps;
	int samplesPerNote;
	//const int chunksPerBuffer;
	//const int bufferSize;


	//void setSampleRate(float val);
	void trigger(float pitch, int sample);

	bool bufferReady;
	std::condition_variable bufferReadyCv;
	std::mutex bufferReadyMutex;
	
	std::condition_variable bufferSentCv;
	std::mutex bufferSentMutex;
	bool bufferSent;

	bool began;
	std::condition_variable beginCv;
	std::mutex beginMutex;

	bool ended;

	std::shared_ptr<std::mutex> hotbufferMutex;
	
	std::array<float, BUFFERSIZE> sampleArray;
	std::array<sf::Int16, BUFFERSIZE> samplePreBuffer;

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

