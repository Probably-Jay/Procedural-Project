#include "App1.h"
App1::App1()
{
	m_InstanceShader = nullptr;
}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in, bool VSYNC, bool FULL_SCREEN)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in, VSYNC, FULL_SCREEN);

	// Load textures
	textureMgr->loadTexture(L"grass", L"res/grass.png");
	textureMgr->loadTexture(L"sand", L"res/sand.png");
	textureMgr->loadTexture(L"rock", L"res/rock.png");

	// Create Mesh object and shader object
	m_InstancedCube = new InstancedCubeMesh(renderer->getDevice(), renderer->getDeviceContext(), 1);
	m_InstanceShader = new InstanceShader(renderer->getDevice(), hwnd);

	// Initialise light
	light = new Light();
	light->setDiffuseColour(0.8f, 0.8f, 0.8f, 1.0f);
	light->setAmbientColour(0.1f, 0.1f,0.1f, 1.0f);
	light->setDirection(0.578f, -0.578f, 0.578f);

	auto cPos = camera->getPosition();
	camera->setPosition(cPos.x, chunkManager.GetTerrainHeight(cPos)+5, cPos.y);

	//LoadChunk();
	UpdateChunks();

}


App1::~App1()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();

	if (m_InstanceShader) {
		delete m_InstanceShader;
		m_InstanceShader = 0;
	}
	if (m_InstancedCube) {
		delete m_InstancedCube;
		m_InstancedCube = 0;
	}
}


bool App1::frame()
{
	bool result;

	result = BaseApplication::frame();
	if (!result)
	{
		return false;
	}
	// Render the graphics.
	Update();
	result = render();
	if (!result)
	{
		return false;
	}

	return true;
}

void App1::Update()
{
	UpdateChunks();
}


//
//void App1::LoadChunk(XMFLOAT3 chunkCords) {
//
//	const int width = 64;
//	const int maxCubes = width * width * width;
//
//	//XMFLOAT3* pos = new XMFLOAT3[maxCubes];
//
//	//XMFLOAT3 origin = { -width / 2,-64,-width / 2 };
//	XMFLOAT3 origin = {0,0,0};
//
//	int instanceCount = 0;
//	//Create two crossing sine waves and only draw the cubes that are under the "height" value
//	for (int i = 0; i < maxCubes; i++) {
//
//		float x = 2* (i % width);
//		float z = 2 * ((i / (int)width) % width);
//
//		float y = 2*(i / (int)(width * width));
//
//		bool solid = (
//			gen.CubeSolid(x, y, z) // we should be solid
//			&& 
//			( // we are visible
//				!gen.CubeSolid(x, y + 2, z) || // above
//				!gen.CubeSolid(x - 2, y, z) || // left
//				!gen.CubeSolid(x + 2, y, z) || // right
//				!gen.CubeSolid(x, y, z + 2) || // behind
//				!gen.CubeSolid(x, y, z - 2)    // infront
//			)); // this is a lot of calls but this should short - circuit most of the time
//		
//		if (solid) {
//			pos[instanceCount] = XMFLOAT3(origin.x + x,origin.y +  y,origin.z + z);
//			instanceCount++;
//		}
//
//	}
//	//
//	////Create two crossing sine waves and only draw the cubes that are under the "height" value
//	//for (int i = 0; i < maxCubes; i++) {
//	//	float y1 = sin((float)(i % width) / 8.0f);
//	//	y1 += 1.0f;
//	//	y1 *= 16.f;
//
//	//	float y2 = sin((float)(i / (width * width)) / 4.0f);
//	//	y2 += 1.0f;
//	//	y2 *= 16.f;
//
//	//	if ((i / width) % width < y1 && (i / width) % width < y2) {
//	//		pos[instanceCount] = XMFLOAT3(2.0f * (i % width), 2.0f * ((i / width) % width), 2.0f * (i / (width * width)));
//	//		instanceCount++;
//	//	}
//	//}
//
//	//SendChunks(pos, instanceCount);
////}

void App1::UpdateChunks(bool forceUpdate)
{

	bool changedChunk = chunkManager.UpdateChunksRendered(camera->getPosition(), 12);
	bool update =  forceUpdate || chunkManager.ChunksAreLoading();

	if (changedChunk || update) {
		m_InstancedCube->initBuffers(renderer->getDevice(), chunkManager.GetActiveChunkData());
	}


}

bool App1::render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;

	// Clear the scene. (default blue colour)
	renderer->beginScene(0.39f, 0.58f, 0.92f, 1.0f);

	// Generate the view matrix based on the camera's position.
	camera->update();

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	worldMatrix = renderer->getWorldMatrix();
	viewMatrix = camera->getViewMatrix();
	projectionMatrix = renderer->getProjectionMatrix();

	// Send geometry data, set shader parameters, render object with shader
	m_InstanceShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"grass"),textureMgr->getTexture(L"sand"),textureMgr->getTexture(L"rock"), light, chunkManager.GetGroundLevel());
	m_InstancedCube->sendDataInstanced(renderer->getDeviceContext());
	m_InstanceShader->renderInstanced(renderer->getDeviceContext(), m_InstancedCube->getIndexCount(), m_InstancedCube->GetInstanceCount());

	// Render GUI
	gui();

	// Swap the buffers
	renderer->endScene();

	return true;
}

void App1::gui()
{
	// Force turn off unnecessary shader stages.
	renderer->getDeviceContext()->GSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->HSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->DSSetShader(NULL, NULL, 0);

	// Build UI
	ImGui::Text("FPS: %.2f", timer->getFPS());
	ImGui::Text("Camera Pos: (%.2f, %.2f, %.2f)", camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);
	ImGui::Text("Chunk Cord: (%i, %i)", chunkManager.GetCurrentChunkCords().x, chunkManager.GetCurrentChunkCords().y);
	ImGui::Checkbox("Wireframe mode", &wireframeToggle);

	// Render UI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

