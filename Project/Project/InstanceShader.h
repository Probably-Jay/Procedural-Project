#pragma once

#include "DXF.h"

using namespace std;
using namespace DirectX;

class InstanceShader : public BaseShader {
private:
	struct LightBufferType {
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
		XMFLOAT3 direction;
		float padding;
	};
	
	struct PositionBufferType {
		float border;
		float grass;
		float sand;
		float rock;

	};

public:
	InstanceShader( ID3D11Device* device, HWND hwnd );
	~InstanceShader();

	void setShaderParameters( ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, ID3D11ShaderResourceView* texture0,ID3D11ShaderResourceView* texture1,ID3D11ShaderResourceView* texture2, Light* light, float groundLevel);
	void renderInstanced( ID3D11DeviceContext* deviceContext, int indexCount, int instanceCount );
private:
	void initShader( const wchar_t* cs, const wchar_t* ps );

private:
	ID3D11Buffer *			matrixBuffer;
	ID3D11SamplerState*		sampleState;
	ID3D11Buffer*			lightBuffer;
	ID3D11Buffer*			positionBuffer;

protected:
	void loadVertexShader( const wchar_t* filename );		///< Load Vertex shader, for stand position, tex, normal geomtry
};

