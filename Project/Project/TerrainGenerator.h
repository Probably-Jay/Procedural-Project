#pragma once

#include "PerlinNoise.h"
class TerrainGenerator 
{

public:
	const bool CubeSolid(float x, float y, float z) const;
	const float GetTerrainHeight(float x, float z) const;

	const float FractalPerlin(float x, float y, int itter = 8) const;

	const float Perlin(float x, float y, float amplitude, float frequency, float xOffset, float yOffset) const;




	float amplitude = 32;
	float frequency = 1.f / 128;
	float groundLevel = 48;

};

