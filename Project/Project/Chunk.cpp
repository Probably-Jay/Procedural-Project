#include "Chunk.h"

Chunk::Chunk(size_t const id, XMFLOAT3 const chunkCords, TerrainGenerator const& gen)
	: chunkspaceCords(chunkCords)
	, worldspaceCords(XMFLOAT3{ chunkspaceCords.x * CHUNKWIDTH,0, chunkspaceCords.z * CHUNKWIDTH })
	, generator(gen)
	, chunkID(id)
{
	chunkData = std::make_unique<vector<XMFLOAT3>>();
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
	chunkInactiveCount++; // count calls to deactivate
	if (chunkLoaded && chunkInactiveCount > INACTIVITYUNLOADTHRESHOLD) { // if over threshhold, unload chunk data from memory
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

		float x = BLOCKSIZE * (i % CHUNKWIDTH);
		float z = BLOCKSIZE * ((i / (int)CHUNKWIDTH) % CHUNKWIDTH);

		float y = BLOCKSIZE * (i / (int)(CHUNKWIDTH * CHUNKWIDTH));

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
			chunkData->push_back(XMFLOAT3(worldspaceCords.x + x, worldspaceCords.y + y, worldspaceCords.z + z));
		}
	}
	chunkData->shrink_to_fit();
	chunkLoaded = true;

}