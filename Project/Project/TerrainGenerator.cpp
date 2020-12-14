#include "TerrainGenerator.h"

bool TerrainGenerator::CubeSolid(float x, float y, float z)
{
	return z < TerrainHeight(x, y);
}

float TerrainGenerator::TerrainHeight(float x, float y)
{
	return groundLevel + FractalPerlin(x,y,1);
}

float TerrainGenerator::FractalPerlin(float x, float y, int itter)
{
	float ampl = amplitude;
	float freq = frequency;
	float height = 0;
	for (int i = 0; i < itter; i++)
	{
		height += Perlin(x, y, ampl, freq, (24 + i) * 21.578 + 49, (-67 - i) * 13.68 + 50);
		ampl /= 4.f;
		freq *= 4;
	}
}


float TerrainGenerator::Perlin(float x, float y, float amplitude, float frequency, float xOffset, float yOffset)
{
	 PerlinNoise::Perlin(x * frequency + xOffset, y * frequency + yOffset) * amplitude;
}

//void TerrainGenerator::BuildPerlin(int itter)
//{
//	float ampl = amplitude;
//	float freq = frequency;
//	for (int i = 0; i < itter; i++)
//	{
//		Perlin(ampl, freq, (11 + i) * 12.561 + 56, (-58 - i) * 19.16 + 44);
//		ampl /= 4.f;
//		freq *= 4;
//	}
//}
//
//
//void TerrainGenerator::Perlin(float amplitude, float frequency, float xOffset, float yOffset)
//{
//
//	//Scale everything so that the look is consistent across terrain resolutions
//	const float scale = terrainSize / (float)resolution;
//
//	//TODO: Give some meaning to these magic numbers! What effect does changing them have on terrain?
//	for (int j = 0; j < (resolution); j++) {
//		for (int i = 0; i < (resolution); i++) {
//			heightMap[(j * resolution) + i] += (0.5 - PerlinNoise::Perlin(i * frequency + xOffset, j * frequency + yOffset)) * amplitude;
//		}
//	}
//}