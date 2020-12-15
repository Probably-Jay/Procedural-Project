#pragma once
#include "DXF.h"	// include dxframework
#include "Chunk.h"
#include <map>

constexpr int MAXCHUNKSINMEMORY = 250;

class ChunkManager
{
public:
	ChunkManager();

	bool UpdateChunksRendered(XMFLOAT3 const& worldCords, const int renderDistance);

	inline XMFLOAT3 GetCurrentChunkCords()const { return currentChunkCords; };

	const vector<XMFLOAT3> GetActiveChunkData()const;

	const float GetTerrainHeight(XMFLOAT3 const& pos)const { return generator.GetTerrainHeight(pos.x,pos.z); };

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

	const DirectX::XMFLOAT3 WorldCordsToChunkCords(const DirectX::XMFLOAT3& worldCords)const;

	bool InChunkLoaded(XMFLOAT3 const& atChunkLocation)const;

	void LoadChunks(const int renderDistance);

	void LoadChunkAt(DirectX::XMFLOAT3& cords);

	void CleanupChunks();
	
	XMFLOAT3 currentChunkCords;

	std::vector<Chunk> chunks;

	TerrainGenerator generator;



	std::map<size_t, Chunk> chunksMap;

};

