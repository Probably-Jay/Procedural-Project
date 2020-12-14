#pragma once

#include "PerlinNoise.h"
class TerrainGenerator
{

public:
	bool CubeSolid(float x, float y, float z);
	float TerrainHeight(float x, float y);

	float FractalPerlin(float x, float y, int itter);

	float Perlin(float x, float y, float amplitude, float frequency, float xOffset, float yOffset);




	float amplitude = 32;
	float frequency = 1.f / 128;
	float groundLevel = 64;

};

