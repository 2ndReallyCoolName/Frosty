#pragma once
#include "Frosty.h"
#include "FrostyExceptions.h"
#include <d3d11.h>
#include <wrl.h>
#include "VertexShader.h"
#include "PixelShader.h"
#include "VertexBuffer.h"

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

	VertexShader vertexShader;
	PixelShader pixelShader;

	VertexBuffer vertexBuffer;
};


