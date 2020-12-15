#include <iostream>

using namespace std;
int main() {


	struct INT2
	{
		int x;
		int y;
	};
	
	INT2 a{ -3,1};
	INT2 b{-4,1 };

	float c = 0;
	float d = -1;

	struct ChunkHasher
	{
		std::size_t operator()(INT2 const& vec) const
		{
			/*return std::hash<float>()	
				(
					vec.x + std::hash<float>()
						(
							vec.y + std::hash<float>() 
							(
								vec.z
							)
						)
				);*/

		https://stackoverflow.com/a/65313449/7711148
			std::hash<int> h;

			return h(h(vec.x) + h(h(vec.y)));


		}
	}chunkHasher;
	
	struct IntHasher
	{
		std::size_t operator()(int const& f) const
		{
			return std::hash<int>()(f);
		}
	}intHasher;



	//auto one1 = intHasher(0);
	//auto two1 = intHasher(one1);
	//auto three1 = intHasher(two1);
	//
	////auto one2 = intHasher(-1);
	////auto two2 = intHasher(one2);
	////auto three2 = intHasher(two2);

	//auto one3 = intHasher(0);
	//auto two3 = -1 + intHasher(one3);
	//auto three3 = intHasher(two3);

	cout << chunkHasher(a) <<", " << chunkHasher(b) << ", " << chunkHasher(a) - chunkHasher(b) << endl;
	cout << intHasher(c) << ", " << intHasher(d) << ", " << intHasher(c) - intHasher(d) << endl << endl;
	//cout << one1 <<", " << two1 << ", "<<  three1 <<  endl;
	//cout << one3 <<", " << two3 << ", "<<  three3 <<  endl << endl;
	int p = 5487452145;
	for (size_t i = 0; i < 10; i++)
	{
		cout << p << "-> " << intHasher(p++) << endl;
	}
	cout << endl << std::numeric_limits<std::size_t>::max() <<endl;
	cout << endl << 1.0 / std::numeric_limits<std::size_t>::max() * 100.0 << "%"<<endl;

	return 0;
}