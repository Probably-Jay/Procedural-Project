#pragma once
#include "DXF.h"	// include dxframework
#include "Chunk.h"
#include <map>

constexpr int MAXCHUNKSINMEMORY = 1024;

class ChunkManager
{
public:
	ChunkManager();

	bool UpdateChunksRendered(XMFLOAT3 const& worldCords, const int renderDistance); // manage which chunks should be loaded

	const vector<XMFLOAT3> GetActiveChunkData()const; // get active chunks' data to the render queue

	const float GetTerrainHeight(XMFLOAT3 const& pos)const { return generator->GetTerrainHeight(pos.x,pos.z); }; // terrain hieght at given position, used for initialisng the camera

	bool ChunksAreLoading()const; // if some chunks are still loading

	inline XMINT2 GetCurrentChunkCords()const { return currentChunkCords; }; // position of player in chunkspace

	inline float GetGroundLevel()const { return generator->groundLevel; }; // information used for texture blending

private:

	struct ChunkHasher // hashes a chunks cords into its ID
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

	void CleanupChunks();
	
	XMINT2 currentChunkCords;


	std::shared_ptr<TerrainGenerator> generator;



	std::map<size_t, Chunk> chunksMap;

};

