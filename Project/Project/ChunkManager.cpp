#include "ChunkManager.h"

ChunkManager::ChunkManager() 
	: currentChunkCords({0,0,0}) 
{

}

void ChunkManager::UpdateChunksRendered(XMFLOAT3 const& atChunkLocation, const int renderDistance)
{
	LoadChunks(atChunkLocation, renderDistance);
}

const vector<XMFLOAT3> ChunkManager::GetActiveChunkData()const
{
	int size = 0;
	for (auto& chunkPair : chunksMap) {
		size += chunkPair.second.GetChunkData().size();
	} // calculate size for reserving

	vector<XMFLOAT3> data;
	data.reserve(size);

	for (auto& chunkPair : chunksMap) {
		auto tempChunk = chunkPair.second.GetChunkData();
		data.insert(data.end(), tempChunk.begin(), tempChunk.end());
	} //concatenate data


	return data;
}

void ChunkManager::LoadChunks(XMFLOAT3 const& chunkLocation, const int renderDistance)
{
	const int loadedChunks = renderDistance * renderDistance;
	//nst int positionOffset = render;


	for (auto  & chunkPair : chunksMap ) // deactiveate all chunks, unload old chunks
	{
		chunkPair.second.Deactivate();
	}

	if(renderDistance > 1){
		// for all chunks visible
		for (int xChunkOffset = -renderDistance / (int)2; xChunkOffset < renderDistance / (int)2; xChunkOffset++) {
			for (int zChunkOffset = -renderDistance / (int)2; zChunkOffset < renderDistance / (int)2; zChunkOffset++) {

				XMFLOAT3 cords = { xChunkOffset + currentChunkCords.x, currentChunkCords.y,zChunkOffset + currentChunkCords.z };

				LoadChunkAt(cords);
			}
		}
	}
	else {
		XMFLOAT3 cords = {currentChunkCords.x, currentChunkCords.y,currentChunkCords.z };

		LoadChunkAt(cords);

	}

	if (chunksMap.size() > MAXCHUNKSINMEMORY) { // if too many chunks exist, delete some
		CleanupChunks();
	}

}

void ChunkManager::LoadChunkAt(DirectX::XMFLOAT3& cords)
{
	auto id = chunkHasher(cords);

	if (chunksMap.count(id) == 0) { // does not exist, add it
		chunksMap.emplace(std::pair<std::size_t, Chunk>(id, Chunk(id, cords, generator)));
	}

	chunksMap.at(id).Activate(); // activate chunk
}

void ChunkManager::CleanupChunks()
{
	/*chunksMap.erase(
		std::remove_if(
			chunksMap.begin(),
			chunksMap.end(),
			[](std::pair<std::size_t, Chunk>& pair) {return !pair.second.IsActive(); }),
		chunksMap.end()
	);*/
}
