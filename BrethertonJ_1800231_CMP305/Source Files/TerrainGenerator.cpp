#include "TerrainGenerator.h"

const bool TerrainGenerator::CubeSolid(float x, float y, float z) const
{
	return y < GetTerrainHeight(x, z);
}

const float TerrainGenerator::GetTerrainHeight(float x, float z)const
{
	return groundLevel + FractalPerlin(x,z);
}

const float TerrainGenerator::FractalPerlin(float x, float z, int itter)const
{
	float ampl = amplitude;
	float freq = frequency;
	float height = 0;
	for (int i = 0; i < itter; i++)
	{
		height += Perlin(x, z, ampl, freq, (24 + i) * 21.578 + 49, (-67 - i) * 13.68 + 50);
		ampl /= 4.f;
		freq *= 4;
	}
	return height;
}


const float TerrainGenerator::Perlin(float x, float z, float amplitude, float frequency, float xOffset, float zOffset)const
{
	 return PerlinNoise::Perlin(x * frequency + xOffset, z * frequency + zOffset) * amplitude;
}
