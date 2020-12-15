#include <iostream>

using namespace std;
int main() {


	struct FLOAT3
	{
		float x;
		float y;
		float z;
	};
	
	FLOAT3 a{ 0,0,0 };
	FLOAT3 b{-1,0,0 };

	float c = 0;
	float d = -1;

	struct ChunkHasher
	{
		std::size_t operator()(FLOAT3 const& vec) const
		{
			return std::hash<float>()	
				(
					vec.x + std::hash<float>()
						(
							vec.y + std::hash<float>() 
							(
								vec.z
							)
						)
				);
		}
	}chunkHasher;
	
	struct FloatHasher
	{
		std::size_t operator()(float const& f) const
		{
			return std::hash<float>()(f);
		}
	}floatHasher;



	auto one1 = floatHasher(0);
	auto two1 = floatHasher(one1);
	auto three1 = floatHasher(two1);
	
	//auto one2 = floatHasher(-1);
	//auto two2 = floatHasher(one2);
	//auto three2 = floatHasher(two2);

	auto one3 = floatHasher(0);
	auto two3 = -1 + floatHasher(one3);
	auto three3 = floatHasher(two3);

	cout << chunkHasher(a) <<", " << chunkHasher(b) << ", " << chunkHasher(a) - chunkHasher(b) << endl;
	cout << floatHasher(c) << ", " << floatHasher(d) << ", " << floatHasher(c) - floatHasher(d) << endl << endl;
	cout << one1 <<", " << two1 << ", "<<  three1 <<  endl;
	cout << one3 <<", " << two3 << ", "<<  three3 <<  endl << endl;
	int p = 5487452145;
	for (size_t i = 0; i < 10; i++)
	{
		cout << p << "-> " << floatHasher(p++) << endl;
	}
	cout << endl << std::numeric_limits<std::size_t>::max() <<endl;
	cout << endl << 1.0 / std::numeric_limits<std::size_t>::max() * 100.0 << "%"<<endl;

	return 0;
}