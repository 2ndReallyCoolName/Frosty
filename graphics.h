#pragma once
#include "Frosty.h"
#include "FrostyExceptions.h"
#include <d3d11.h>
#include <wrl.h>
#include "VertexShader.h"
#include "PixelShader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ColorBuffer.h"
#include "Matrix.h"
#include "ConstantBuffer.h"

#include <WICTextureLoader.h>

#include "Cube.h"

#include <math.h>



class Graphics
{
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics() = default;
	void RenderFrame(float angle, float x, float y) noexcept;

private:
	void initializeShaders();
	void initializeVertices();

private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr <IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr <ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr <ID3D11RenderTargetView> pTarget;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDepthStencilState;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepthStencilView;
	Microsoft::WRL::ComPtr <ID3D11Texture2D> pDepthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTexture;

	VertexShader vertexShader;
	PixelShader pixelShader;
	
	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;
	ColorBuffer colorBuffer;
	ConstantBuffer constantBuffer;

	Matrix mtx;
	Cube cube;
};


