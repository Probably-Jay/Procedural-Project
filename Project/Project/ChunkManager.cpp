#include "ChunkManager.h"

ChunkManager::ChunkManager() 
	: currentChunkCords({-1,-1}) 
{

}

bool ChunkManager::UpdateChunksRendered(XMFLOAT3 const& worldCords, const int renderDistance)
{
	const XMINT2 chunkCords = WorldCordsToChunkCords(worldCords);
	if (InChunkLoaded(chunkCords)) {
		return false; // not changed chunk
	}
	else {
		currentChunkCords = chunkCords;
		LoadChunks(renderDistance);
		return true;
	}
}

const XMINT2 ChunkManager::WorldCordsToChunkCords(const XMFLOAT3& worldCords)const
{

	XMINT2 chunkCords{ 0,0 };
	chunkCords.x = floorf( worldCords.x / (float)(BLOCKSIZE * CHUNKWIDTH));
	chunkCords.y = floorf(worldCords.z / (float)(BLOCKSIZE * CHUNKWIDTH));

	return chunkCords;
}

bool ChunkManager::InChunkLoaded(XMINT2 const& atChunkLocation)const
{
	return currentChunkCords.x == atChunkLocation.x && currentChunkCords.y == atChunkLocation.y;
	
}

const vector<XMFLOAT3> ChunkManager::GetActiveChunkData()const
{
	int size = 0;
	for (auto& chunkPair : chunksMap) {
		if (chunkPair.second.IsActive()) {
			size += chunkPair.second.GetChunkData().size();
		}
	} // calculate size for reserving

	vector<XMFLOAT3> data;
	data.reserve(size);

	for (auto& chunkPair : chunksMap) {
		if (chunkPair.second.IsActive()) {
			auto tempChunk = chunkPair.second.GetChunkData();
			data.insert(data.end(), tempChunk.begin(), tempChunk.end());
		}
	} //concatenate data


	return data;
}

void ChunkManager::LoadChunks(const int renderDistance)
{
	//const int loadedChunks = renderDistance * renderDistance;
	//nst int positionOffset = render;


	for (auto  & chunkPair : chunksMap ) // deactiveate all chunks, unload old chunks
	{
		chunkPair.second.Deactivate();
	}
	if(renderDistance > 0){
		// for all chunks visible
		for (int xChunkOffset = -renderDistance; xChunkOffset < renderDistance+1; xChunkOffset++) {
			for (int zChunkOffset = -renderDistance; zChunkOffset < renderDistance+1 ; zChunkOffset++) {

				XMINT2 cords = { xChunkOffset + currentChunkCords.x,zChunkOffset + currentChunkCords.y };

				LoadChunkAt(cords);
			}
		}
	}
	else {
		XMINT2 cords = {currentChunkCords.x,currentChunkCords.y };

		LoadChunkAt(cords);

	}

	//for (auto& chunkPair : chunksMap) // deactiveate all chunks, unload old chunks
	//{
	//	chunkPair.second.UnloadIfInactive();
	//}

	if (chunksMap.size() > MAXCHUNKSINMEMORY) { // if too many chunks exist, delete some
		CleanupChunks();
	}

}

void ChunkManager::LoadChunkAt(XMINT2& cords)
{
	auto id = chunkHasher(cords);

	if (chunksMap.count(id) == 0) { // does not exist, add it
		chunksMap.emplace(std::pair<std::size_t, Chunk>(id, Chunk(id, cords, generator)));
	}

	chunksMap.at(id).Activate(); // activate chunk
}

void ChunkManager::CleanupChunks()
{
	//chunksMap.erase(
	//	std::remove_if(
	//		chunksMap.begin(),
	//		chunksMap.end(),
	//		[](std::pair<std::size_t, Chunk>& pair) {return !pair.second.IsActive(); }),
	//	chunksMap.end()
	//);
	//https://www.fluentcpp.com/2018/09/21/remove-elements-associative-container-cpp/
	for (auto ittr = chunksMap.begin(); ittr != chunksMap.end();)
	{
		if (!ittr->second.IsActive())
		{
			ittr = chunksMap.erase(ittr);
		}
		else
		{
			++ittr;
		}
	}
}

