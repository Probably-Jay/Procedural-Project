#pragma once
#include <array>
#include <memory>
#include "DXF.h"	// include dxframework
#include "TerrainGenerator.h"

constexpr int BLOCKSIZE = 2;
constexpr int CHUNKWIDTH = 64;
constexpr int MAXCHNKCAPACITY = CHUNKWIDTH * CHUNKWIDTH * CHUNKWIDTH;
class Chunk
{
public:
	//static const int CHUNKWIDTH = { 64 };

	Chunk(size_t const id, XMFLOAT3 const chunkCords, TerrainGenerator const & gen);
	void UnloadChunk();
	void ReLoadChunk();
	
	inline bool IsLoaded() const { return chunkLoaded; };

	const std::size_t chunkID;



private:

	TerrainGenerator const & generator;

	const XMFLOAT3 chunkspaceCords;
	const XMFLOAT3 worldspaceCords;

	void GenerateChunk();

	bool chunkLoaded = false;
	
	std::unique_ptr<vector<XMFLOAT3>> chunkData;

};

