#include "ChunkManager.h"

ChunkManager::ChunkManager()
{

}

void ChunkManager::UpdateChunksRendered(XMFLOAT3 const& atChunkLocation, const int renderDistance)
{
	LoadChunks(atChunkLocation, renderDistance);
}

void ChunkManager::LoadChunks(XMFLOAT3 const& chunkLocation, const int renderDistance)
{
	const int loadedChunks = renderDistance * renderDistance;
	//nst int positionOffset = render;

	for (int xChunkOffset = -renderDistance / 2; xChunkOffset < renderDistance / 2; xChunkOffset++) {
		for (int zChunkOffset = -renderDistance / 2; zChunkOffset < renderDistance / 2; zChunkOffset++) {
			XMFLOAT3 cords = { xChunkOffset + currentChunkCords.x, currentChunkCords.y,zChunkOffset + currentChunkCords.z };
			auto id = chunkHasher(cords);

			auto matches = chunksMap.count(id);

			if (matches == 0) {

			}
			else if (matches == 1) {

			}
			else {
				// hash colllision, idk
			}
			
		}
	}
}
