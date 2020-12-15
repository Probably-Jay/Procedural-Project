#include "ChunkManager.h"

ChunkManager::ChunkManager() 
	: currentChunkCords({0,0,0}) 
{

}

void ChunkManager::UpdateChunksRendered(XMFLOAT3 const& atChunkLocation, const int renderDistance)
{
	LoadChunks(atChunkLocation, renderDistance);
}

void ChunkManager::GetActiveChunkData()
{
	;
}

void ChunkManager::LoadChunks(XMFLOAT3 const& chunkLocation, const int renderDistance)
{
	const int loadedChunks = renderDistance * renderDistance;
	//nst int positionOffset = render;


	for (auto  & chunkPair : chunksMap ) // deactiveate all chunks, unload old chunks
	{
		chunkPair.second.Deactivate();
	}

	// for all chunks visible
	for (int xChunkOffset = -renderDistance / 2; xChunkOffset < renderDistance / 2; xChunkOffset++) {
		for (int zChunkOffset = -renderDistance / 2; zChunkOffset < renderDistance / 2; zChunkOffset++) {
			XMFLOAT3 cords = { xChunkOffset + currentChunkCords.x, currentChunkCords.y,zChunkOffset + currentChunkCords.z };
			auto id = chunkHasher(cords);

			if (chunksMap.count(id) == 0) { // does not exist, add it
				chunksMap.emplace(std::pair<std::size_t,Chunk>(id, Chunk(id, cords, generator)));
			}
			
			chunksMap.at(id).Activate(); // activate chunk
		}
	}

	if (chunksMap.size() > MAXCHUNKSINMEMORY) { // if too many chunks exist, delete some
		CleanupChunks();
	}

}

void ChunkManager::CleanupChunks()
{
	chunksMap.erase(
		std::remove_if(
			chunksMap.begin(),
			chunksMap.end(),
			[](std::pair<std::size_t, Chunk>& pair) {return !pair.second.IsActive(); }),
		chunksMap.end()
	);
}
