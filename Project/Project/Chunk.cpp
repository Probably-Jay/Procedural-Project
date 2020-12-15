#include "Chunk.h"

Chunk::Chunk(size_t const id, XMINT2 const& chunkCords, TerrainGenerator const& gen)
	: chunkspaceCords(chunkCords)
	, worldspaceCords(XMFLOAT3{ (float)chunkspaceCords.x * CHUNKWIDTH * BLOCKSIZE,0.f, (float)chunkspaceCords.y * CHUNKWIDTH * BLOCKSIZE })
	, generator(gen)
	, chunkID(id)
{
	chunkData = std::make_shared<vector<XMFLOAT3>>();
	//chunkData = std::unique_ptr<vector<XMFLOAT3>>(new vector<XMFLOAT3>());
	//chunkData = new vector<XMFLOAT3>();
}

std::vector<XMFLOAT3> const & Chunk::GetChunkData()const
{
	return *chunkData;
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
		GenerateChunk();
	}
}

void Chunk::Activate()
{
	chunkActive = true;
	chunkInactiveCount = 0; // reset chunk inactive count
	LoadChunk(); // load chunk if not already loaded
	
}

void Chunk::Deactivate()
{
	chunkActive = false;
	//chunkInactiveCount++; // count calls to deactivate
	//if (chunkLoaded && chunkInactiveCount > INACTIVITYUNLOADTHRESHOLD) { // if over threshhold, unload chunk data from memory
	//	UnloadChunk();
	//}
}
void Chunk::UnloadIfInactive()
{
	if (chunkLoaded && !chunkActive) {
		UnloadChunk();
	}
}
//
//void Chunk::SetActive(bool active)
//{
//	chunkActive = active;
//
//	if (chunkActive) {
//		chunkLoadsSinceActive = 0;
//	}
//	else {
//		chunkLoadsSinceActive++;
//	}
//}




void Chunk::GenerateChunk() {

	chunkData->clear();
	chunkData->reserve(MAXCHNKCAPACITY);
	

	for (int i = 0; i < MAXCHNKCAPACITY; i++) {

		float x = worldspaceCords.x + BLOCKSIZE * (i % CHUNKWIDTH);
		float z = worldspaceCords.z + BLOCKSIZE * ((i / (int)CHUNKWIDTH) % CHUNKWIDTH);

		float y = worldspaceCords.y + BLOCKSIZE * (i / (int)(CHUNKWIDTH * CHUNKWIDTH));

		bool solid = (
			generator.CubeSolid(x, y, z) // we should be solid
			&&
			( // we are visible
				!generator.CubeSolid(x, y + BLOCKSIZE, z) || // above
				!generator.CubeSolid(x - BLOCKSIZE, y, z) || // left
				!generator.CubeSolid(x + BLOCKSIZE, y, z) || // right
				!generator.CubeSolid(x, y, z + BLOCKSIZE) || // behind
				!generator.CubeSolid(x, y, z - BLOCKSIZE)    // infront
				)); // this is a lot of noise calls but this should short-circuit most of the time

		if (solid) {
			chunkData->push_back(XMFLOAT3( x,  y, z));
		}
	}
	chunkData->shrink_to_fit();
	chunkLoaded = true;

}