#pragma once
// standard algorithm
inline constexpr const float& Clamp(const float& v, const float& lo, const float& hi)
{
	return (v < lo) ? lo : (hi < v) ? hi : v;
}

// standard algorithm
inline constexpr const float Lerp(const float& a, const float& b, const float& f)
{
	return a + f * (b - a);
}

// standard algorithm
inline constexpr const float InvLerp(const float& a, const float& b, const float& f)
{
	return (f - a) / (b - a);
}