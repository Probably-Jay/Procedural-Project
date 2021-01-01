#pragma once
#include "DXF.h"	// include dxframework
#include "Chunk.h"
#include <map>

constexpr int MAXCHUNKSINMEMORY = 100;

class ChunkManager
{
public:
	ChunkManager();

	bool UpdateChunksRendered(XMFLOAT3 const& worldCords, const int renderDistance);

	inline XMINT2 GetCurrentChunkCords()const { return currentChunkCords; };

	bool ChunksAreLoading()const;

	const vector<XMFLOAT3> GetActiveChunkData()const;

	const float GetTerrainHeight(XMFLOAT3 const& pos)const { return generator->GetTerrainHeight(pos.x,pos.z); };

	inline float GetGroundLevel()const { return generator->groundLevel; };

private:

	struct ChunkHasher
	{
		std::size_t operator()(XMINT2 const& vec) const
		{
			
			//https://stackoverflow.com/a/65313449/7711148
			std::hash<int> h;

			return h(h(vec.x) + h(h(vec.y)));
		}
	}chunkHasher;

	const XMINT2 WorldCordsToChunkCords(const XMFLOAT3& worldCords)const;

	bool InChunkLoaded(XMINT2 const& atChunkLocation)const;

	void LoadChunks(const int renderDistance);

	void LoadChunkAt(DirectX::XMINT2& cords);

	void LoadChunkAtAsync(XMINT2& cords);

	void CleanupChunks();
	
	XMINT2 currentChunkCords;

	//std::vector<Chunk> chunks;

	std::shared_ptr<TerrainGenerator> generator;



	std::map<size_t, Chunk> chunksMap;
	//std::map<size_t, Chunk&> activeChunks;

};

