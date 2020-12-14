#pragma once
#include "DXF.h"	// include dxframework
#include "Chunk.h"
#include <map>
class ChunkManager
{
public:
	ChunkManager();

	void UpdateChunksRendered(XMFLOAT3 const& atLocation, const int renderDistance);


private:

	struct ChunkHasher
	{
		std::size_t operator()(const XMFLOAT3& vec) const
		{
			return std::hash<float>()(
				vec.x + (std::hash<float>()(
					vec.y + std::hash<float>() (vec.z))
					)
				);
		}
	}chunkHasher;

	void LoadChunks(XMFLOAT3 const& location, const int renderDistance);
	
	XMFLOAT3 currentChunkCords;

	std::vector<Chunk> chunks;


	std::map<size_t, Chunk> chunksMap;

};

