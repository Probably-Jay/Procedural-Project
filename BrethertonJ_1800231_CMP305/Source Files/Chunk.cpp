#include "Chunk.h"

Chunk::Chunk(size_t const id, XMINT2 const& chunkCords, std::shared_ptr<TerrainGenerator>& gen)
	: chunkspaceCords(chunkCords)
	, worldspaceCords(XMFLOAT3{ (float)chunkspaceCords.x * CHUNKWIDTH * BLOCKSIZE,0.f, (float)chunkspaceCords.y * CHUNKWIDTH * BLOCKSIZE })
	, generator(gen)
	, chunkID(id)
	
{
	chunkData = std::make_shared<vector<XMFLOAT3>>();
	chunkMutex = std::make_shared<std::mutex>();
}

Chunk::~Chunk()
{
	Lock();
}

void Chunk::Lock()
{
	if (!lock) {
		lock = std::make_shared<std::lock_guard<mutex>>(*chunkMutex);
	}
}

bool Chunk::IsActive() const
{
	if (currentlyLoading) return false;
	else return chunkActive;
}


void Chunk::UnloadChunk()
{
	if (chunkLoaded) {
		chunkData->clear();
		chunkLoaded = false;
	}
}

void Chunk::LoadChunk()
{
	if (!chunkLoaded) {
		thread t(&Chunk::GenerateChunk,this);
		t.detach();
	}
}

void Chunk::Activate()
{
	chunkActive = true;
	LoadChunk(); // load chunk if not already loaded
}

void Chunk::Deactivate()
{
	chunkActive = false;
}
void Chunk::UnloadIfInactive()
{
	if (chunkLoaded && !chunkActive) {
		UnloadChunk();
	}
}


void Chunk::GenerateChunk()
{
	currentlyLoading = true;
	
	std::lock_guard<mutex>(*chunkMutex); // RAII
	chunkData->clear();
	chunkData->reserve(MAXCHNKCAPACITY);

	FillChunkData();

	chunkData->shrink_to_fit();
	chunkLoaded = true; 
	currentlyLoading = false;
	 
}// end raii
void Chunk::FillChunkData()
{
	for (size_t X = 0; X < CHUNKWIDTH; X++)
	{
		for (size_t Z = 0; Z < CHUNKWIDTH; Z++)
		{
			for (size_t Y = 0; Y < CHUNKHEIGHT; Y++)
			{

				float x = worldspaceCords.x + BLOCKSIZE * X;
				float z = worldspaceCords.z + BLOCKSIZE * Z;

				float y = worldspaceCords.y + BLOCKSIZE * Y;


				if (generator->CubeSolid(x, y, z)) { // cube is below ground (or on surface level)
					if (( // we are visible
						!generator->CubeSolid(x, y + BLOCKSIZE, z) || // above
						!generator->CubeSolid(x - BLOCKSIZE, y, z) || // left
						!generator->CubeSolid(x + BLOCKSIZE, y, z) || // right
						!generator->CubeSolid(x, y, z + BLOCKSIZE) || // behind
						!generator->CubeSolid(x, y, z - BLOCKSIZE)    // infront
						)) {
						chunkData->push_back(XMFLOAT3(x, y, z));
					}
					// else we are invisible below ground and there is no point drawing us
				}
				else { // above ground, we can exit this column now
					break;
				}

			}
		}
	}
}

