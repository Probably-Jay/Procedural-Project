#pragma once
#include "DXF.h"	// include dxframework
#include "Chunk.h"
#include <map>

constexpr int MAXCHUNKSINMEMORY = 250;

class ChunkManager
{
public:
	ChunkManager();

	void UpdateChunksRendered(XMFLOAT3 const& atLocation, const int renderDistance);



private:

	struct ChunkHasher
	{
		std::size_t operator()(XMFLOAT3 const& vec) const
		{
			return std::hash<float>()(
				vec.x + (std::hash<float>()(
					vec.y + std::hash<float>() (vec.z))
					)
				);
		}
	}chunkHasher;

	void LoadChunks(XMFLOAT3 const& location, const int renderDistance);
	void GetActiveChunkData();

	void CleanupChunks();
	
	XMFLOAT3 currentChunkCords;

	std::vector<Chunk> chunks;

	TerrainGenerator generator;



	std::map<size_t, Chunk> chunksMap;

};

