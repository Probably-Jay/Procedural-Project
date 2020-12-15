// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"	// include dxframework
#include "InstanceShader.h"
#include "InstancedCubeMesh.h"
//#include "TerrainGenerator.h"
#include <map>
#include <unordered_map>
#include "ChunkManager.h"

class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN);

	bool frame();

protected:
	bool render();
	void gui();

private:
//	void LoadChunk(XMFLOAT3 chunkCords);

	void UpdateChunks();

	InstanceShader* m_InstanceShader;
	InstancedCubeMesh* m_InstancedCube;

	Light* light;

	//TerrainGenerator gen;
	ChunkManager chunkManager;

	static const int chunkWidth = { 64 };



	//std::unordered_map<XMFLOAT3, array<XMFLOAT3, chunkWidth * chunkWidth * chunkWidth>,> chunks;
	std::map<size_t, array<XMFLOAT3, chunkWidth * chunkWidth * chunkWidth>> chunks;
};

#endif