#pragma once
#include <array>
#include <memory>
#include "DXF.h"	// include dxframework
#include "TerrainGenerator.h"

#include <mutex>


constexpr int BLOCKSIZE = 2;
constexpr int CHUNKWIDTH = 16;
constexpr int CHUNKHEIGHT = 64;

constexpr int MAXCHNKCAPACITY = CHUNKWIDTH * CHUNKWIDTH * CHUNKHEIGHT;
constexpr int INACTIVITYUNLOADTHRESHOLD = 25;

class Chunk
{
public:
	//static const int CHUNKWIDTH = { 64 };

	Chunk(size_t const id, XMINT2 const& chunkCords, TerrainGenerator const & gen);
	~Chunk();

	bool IsActive() const;
	inline bool IsLoading() const{ return currentlyLoading; };

	
	//inline bool MarkedForCleanUp() { return chunkInactiveCount > INACTIVITYDESTRUCTIONTHRESHOLD; };

	void Activate();
	void Deactivate();

	void UnloadIfInactive();
	
	//inline bool IsLoaded() const { return chunkLoaded; };

	const std::size_t chunkID;


	struct LockedData
	{
		LockedData(std::vector<XMFLOAT3> const& d, std::mutex& mtx) : data(d), lk(mtx) {};
		std::vector<XMFLOAT3> const& data;
	private:
		std::lock_guard<mutex>lk;
	};

	inline LockedData const&& RequestChunkData()const { return LockedData(GetChunkData(),*chunkMutex); };


private:
	inline std::vector<XMFLOAT3> const& GetChunkData()const { return *chunkData; };

	void UnloadChunk();
	void LoadChunk();

	mutable std::shared_ptr<std::mutex> chunkMutex;
	//mutable std::unique_lock<std::mutex> lock{ chunkMutex };

	TerrainGenerator const & generator;

	const XMINT2 chunkspaceCords;
	const XMFLOAT3 worldspaceCords;

	//void OldGenerateChunk();

	void GenerateChunk();

	bool currentlyLoading = false;

	bool chunkLoaded = false;
	
	bool chunkActive = false;
	int chunkInactiveCount = 0;
	
	std::shared_ptr<vector<XMFLOAT3>> chunkData;
	//vector<XMFLOAT3> * chunkData;

};

