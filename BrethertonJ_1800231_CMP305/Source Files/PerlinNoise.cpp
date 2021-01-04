#include "PerlinNoise.h"



float PerlinNoise::Perlin(float x, float y)
{
	

	PerlinNoise::Vector2 globalPosition{ x,y };
	PerlinNoise::Vector2 positionInSquare{ x,y };
	
	PerlinNoise::Vector2 distanceVectors[4];
	PerlinNoise::GridVertex vertices[4];
	
	float dots[4];

	// grid cords
	int x0 = floorf(x);
	int x1 = x0 + 1;
	int y0 = floorf(y);
	int y1 = y0 + 1;


	vertices[0].Position = { (float)x0,(float)y0 };
	vertices[1].Position = { (float)x1,(float)y0 };
	vertices[2].Position = { (float)x0,(float)y1 };
	vertices[3].Position = { (float)x1,(float)y1 };

	positionInSquare = globalPosition - vertices[0].Position;
	
	for (size_t i = 0; i < 4; i++)
	{
		vertices[i].SetRandomVector();
		distanceVectors[i] = globalPosition - vertices[i].Position;
		dots[i] = distanceVectors[i].Dot(vertices[i].RandomVector);
	}

	
	

	float xVal1, xVal2 , value;

	xVal1 = Interpolate(dots[0], dots[1], positionInSquare.x);
	xVal2 = Interpolate(dots[2], dots[3], positionInSquare.x);

	value = Interpolate(xVal1, xVal2, positionInSquare.y);

	return value;

	
}

float PerlinNoise::Smoothstep(float edge0, float edge1, float x)
{
	x = PerlinNoise::Clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
	
	return x * x * (3 - 2 * x);
}

PerlinNoise::Vector2 PerlinNoise::RandomGradient(PerlinNoise::Vector2 position)
{
	float ix = position.x;
	float iy = position.y;
	float random = 2920.f * sinf(ix * 21942.f + iy * 171324.f + 8912.f) * cosf(ix * 23157.f * iy * 217832.f + 9758.f); // https://xkcd.com/221/
	return Vector2 { cosf(random),  sinf(random) };
}

float PerlinNoise::Interpolate(float a0, float a1, float w)
{
	return pow(w, 2.0) * (3.0 - 2.0 * w) * ((double)a1 - a0) + a0;
}
