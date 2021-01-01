#pragma once
#include <math.h>


// adapted from ken perlin's original, sourced https://en.wikipedia.org/wiki/Perlin_noise
class PerlinNoise
{
public:

	static float Perlin(float x, float y);

private:

	struct Vector2
	{
		float x, y;

		Vector2& operator-=(const Vector2& rhs) {
			this->x -= rhs.x;
			this->y -= rhs.y;
			return *this;
		}
		friend Vector2 operator-(Vector2 lhs, const Vector2& rhs) {
			lhs -= rhs;
			return lhs;
		}
		float Dot(const Vector2& rhs) {
			return (this->x * rhs.x + this->y + rhs.y);
		}
	};

	struct GridVertex {
		Vector2 Position;
		Vector2 RandomVector;
		inline void SetRandomVector() {
			RandomVector = RandomGradient(Position);
		}
		
	};

	static float Interpolate(float a0, float a1, float w);

	static float Smoothstep(float edge0, float edge1, float x);

	static inline float const Clamp(float x, float lower, float upper) { return (x < lower) ? lower : ((x > upper) ? upper : x); };

	static Vector2 RandomGradient(Vector2 position);

};

