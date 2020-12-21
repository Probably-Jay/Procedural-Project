#pragma once
#include "SFML/Audio.hpp"
#include <memory>
#include <mutex>
#include <array>
#include <condition_variable> 
#include "StandardAlgorithms.h"
#include <vector>
#include "MarkovChain.h"
#include "Chord.h"
#include <iostream>

constexpr auto PI = 3.1415f;
 
constexpr float SAMPLERATE = 44100.f;
constexpr float SAMPLESPERNOTE_s = SAMPLERATE *1.f;
constexpr auto CHUNKSPERBUFFER = 16;
constexpr size_t BUFFERSIZE = CHUNKSPERBUFFER * SAMPLERATE;
constexpr size_t NOTESPERCHUNK =  BUFFERSIZE / SAMPLESPERNOTE_s ;


using namespace sf;
class AudioGenerator
{
public:
	AudioGenerator();

	void SetUpMarkov();

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

	void GenerateChord(const size_t& i);

	void FillBackBuffer();
	void FillOverflow();
	void GenerateNote(float pitch, int startSampleIndex, const int samplesPerNote);

	void GenerateSamples(int startSampleIndex, const int samplesPerNote, const int attack, const int& decay, const float  incrimentValue, const float envelopeFactor);
	float SinWave(float& index, const float incrimentValue);
	float SawWave(float& index, const float incrimentValue);
	float SquareWave(float& index, const float incrimentValue);
	float TriangleWave(float& index, const float incrimentValue);


	//void GenerateSawSamples(int startSampleIndex, const int samplesPerNote, const int attack, const int& decay, const float  incrimentValue, const float envelopeFactor);

	void FillSamples(const size_t i, const int attack, const int decay, float audio, const float envelopeFactor);

	//const float sampleRate;
	float bps;
	int samplesPerNote;
	//const int chunksPerBuffer;
	//const int bufferSize;
	//float sinIndex;

	//void setSampleRate(float val);
	//void trigger(float pitch, int sample);

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
	
	std::array<float, 2*BUFFERSIZE> sampleArray;
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

	
	MarkovChain<Chord::Function> mark;

};

