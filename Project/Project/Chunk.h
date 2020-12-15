#pragma once
#include <array>
#include <memory>
#include "DXF.h"	// include dxframework
#include "TerrainGenerator.h"

constexpr int BLOCKSIZE = 2;
constexpr int CHUNKWIDTH = 64;
constexpr int MAXCHNKCAPACITY = CHUNKWIDTH * CHUNKWIDTH * CHUNKWIDTH;
constexpr int INACTIVITYUNLOADTHRESHOLD = 25;

class Chunk
{
public:
	//static const int CHUNKWIDTH = { 64 };

	Chunk(size_t const id, XMFLOAT3 const& chunkCords, TerrainGenerator const & gen);

	inline bool IsActive() const { return chunkActive; };
	
	//inline bool MarkedForCleanUp() { return chunkInactiveCount > INACTIVITYDESTRUCTIONTHRESHOLD; };

	void Activate();
	void Deactivate();
	
	//inline bool IsLoaded() const { return chunkLoaded; };

	const std::size_t chunkID;

	std::vector<XMFLOAT3> const& GetChunkData()const;

private:
	void UnloadChunk();
	void LoadChunk();

	TerrainGenerator const & generator;

	const XMFLOAT3 chunkspaceCords;
	const XMFLOAT3 worldspaceCords;

	void GenerateChunk();

	bool chunkLoaded = false;
	
	bool chunkActive = false;
	int chunkInactiveCount = 0;
	
	std::unique_ptr<vector<XMFLOAT3>> chunkData;
	//vector<XMFLOAT3> * chunkData;

};

