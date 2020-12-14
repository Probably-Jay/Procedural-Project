#include "TerrainGenerator.h"

bool TerrainGenerator::CubeSolid(float x, float y, float z)
{
	return y < TerrainHeight(x, z);
}

float TerrainGenerator::TerrainHeight(float x, float z)
{
	return groundLevel + FractalPerlin(x,z,1);
}

float TerrainGenerator::FractalPerlin(float x, float z, int itter)
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


float TerrainGenerator::Perlin(float x, float z, float amplitude, float frequency, float xOffset, float zOffset)
{
	 return PerlinNoise::Perlin(x * frequency + xOffset, z * frequency + zOffset) * amplitude;
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