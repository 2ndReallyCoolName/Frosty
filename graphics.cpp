#include "graphics.h"

namespace wrl = Microsoft::WRL;

Graphics::Graphics(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));

	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	FrostyExceptions::Exception(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
		nullptr, 0, nullptr, 0, D3D11_SDK_VERSION,
		&sd, pSwap.GetAddressOf(), pDevice.GetAddressOf(), nullptr,
		pContext.GetAddressOf()));

	wrl::ComPtr<ID3D11Resource> pBackBuffer;

	FrostyExceptions::Exception(pSwap->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(pBackBuffer.GetAddressOf())));

	FrostyExceptions::Exception(pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, pTarget.GetAddressOf()));

	pContext->OMSetRenderTargets(1, pTarget.GetAddressOf(), nullptr);

	D3D11_VIEWPORT vp;
	ZeroMemory(&vp, sizeof(D3D11_VIEWPORT));
	vp.Width = 800;
	vp.Height = 300;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	pContext->RSSetViewports(1u, &vp);

	initializeShaders();
	initializeVertices();
}

void Graphics::RenderFrame(float angle, float x, float y) noexcept
{
	const float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	pContext->ClearRenderTargetView(pTarget.Get(), color);

	pContext->IASetInputLayout(vertexShader.getInputLayout());
	pContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINELIST);

	pContext->VSSetShader(vertexShader.getShader(), NULL, 0);
	pContext->PSSetShader(pixelShader.getShader(), NULL, 0);

	UINT stride = sizeof(vertex);
	UINT offset = 0;
	pContext->IASetVertexBuffers(0, 1, vertexBuffer.getVertexBuffer().GetAddressOf(), &stride, &offset);

	pContext->Draw(4u, 0u);

	pSwap->Present(1u, 0u);
}

void Graphics::initializeShaders()
{
	vertexShader = VertexShader(pDevice, L"vertexShader.cso");
	pixelShader = PixelShader(pDevice, L"pixelShader.cso");
}

void Graphics::initializeVertices()
{
	vertex v[] = {
		vertex(-0.5f, 0.5f),
		vertex(0.0f, -0.5f),
		vertex(0.5f, 0.5f),
		vertex(0.5f, 0.0f),
	};

	vertexBuffer = VertexBuffer(pDevice, v, ARRAYSIZE(v));
}
