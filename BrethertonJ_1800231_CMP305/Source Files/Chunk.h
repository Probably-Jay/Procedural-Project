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
	Chunk(size_t const id, XMINT2 const& chunkCords, std::shared_ptr<TerrainGenerator>& gen);
	~Chunk();

	void Lock(); // lock chunk for deletion

	bool IsActive() const;
	inline bool IsLoading() const{ return currentlyLoading; };

	
	void Activate(); // turn on the chunk (possibly generate or re-generate it)
	void Deactivate(); // turn off the chunk

	void UnloadIfInactive();
	
	const std::size_t chunkID;


	struct LockedData // allows access to data in RAII way
	{
		LockedData(std::vector<XMFLOAT3> const& d, std::mutex& mtx) : data(d), lk(mtx) {};
		std::vector<XMFLOAT3> const& data;
	private:
		std::lock_guard<mutex>lk;
	};

	// interface to data
	inline LockedData const&& RequestChunkData()const { return LockedData(GetChunkData(),*chunkMutex); };


private:
	inline std::vector<XMFLOAT3> const& GetChunkData()const { return *chunkData; };

	void UnloadChunk();
	void LoadChunk();

	void GenerateChunk();

	void FillChunkData();


	mutable std::shared_ptr<std::mutex> chunkMutex;
	std::shared_ptr<std::lock_guard<std::mutex>> lock;

	std::shared_ptr<TerrainGenerator> generator;

	const XMINT2 chunkspaceCords;
	const XMFLOAT3 worldspaceCords;

	bool currentlyLoading = false; // a thread is in `Generate`
	bool chunkLoaded = false; // chunk exists in memory
	bool chunkActive = false; // chunk is in render buffer
	
	std::shared_ptr<vector<XMFLOAT3>> chunkData;

};
