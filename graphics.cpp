#include "graphics.h"

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

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

	D3D11_TEXTURE2D_DESC td;
	td.Width = 800;
	td.Height = 300;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	td.CPUAccessFlags = D3D11_BIND_DEPTH_STENCIL;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;

	FrostyExceptions::Exception(pDevice->CreateTexture2D(&td, NULL, pDepthStencilBuffer.GetAddressOf()));

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice = 0u;

	FrostyExceptions::Exception(pDevice->CreateDepthStencilView(pDepthStencilBuffer.Get(), NULL, pDepthStencilView.GetAddressOf()));

	pContext->OMSetRenderTargets(1, pTarget.GetAddressOf(), pDepthStencilView.Get());

	D3D11_DEPTH_STENCIL_DESC dd;
	ZeroMemory(&dd, sizeof(D3D11_DEPTH_STENCIL_DESC));

	dd.DepthEnable = true;
	dd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dd.DepthFunc = D3D11_COMPARISON_LESS;

	FrostyExceptions::Exception(pDevice->CreateDepthStencilState(&dd, pDepthStencilState.GetAddressOf()));


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
	const float color[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	mtx =
	{
		{
			dx::XMMatrixTranspose(
				dx::XMMatrixRotationZ(angle) *
				dx::XMMatrixRotationY(angle) *
				dx::XMMatrixScaling(3.0f / 4.0f, 1.0f, 1.0f) *
				dx::XMMatrixTranslation(x, y, 4.0f) *
				dx::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 10.0f)
			)
		}
	};

	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(mtx);
	cbd.StructureByteStride = 0u;

	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &mtx;

	FrostyExceptions::Exception(pDevice->CreateBuffer(&cbd, &csd, pConstantBuffer.GetAddressOf()));

	pContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
	pContext->PSSetConstantBuffers(0u, 1u, colorBuffer.getColorBuffer().GetAddressOf());

	pContext->ClearRenderTargetView(pTarget.Get(), color);
	pContext->ClearDepthStencilView(pDepthStencilView.Get(), 
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	pContext->IASetInputLayout(vertexShader.getInputLayout());
	pContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pContext->RSSetState(vertexShader.getRasterizerState());
	pContext->OMSetDepthStencilState(pDepthStencilState.Get(), 0u);

	pContext->VSSetShader(vertexShader.getShader(), NULL, 0);
	pContext->PSSetShader(pixelShader.getShader(), NULL, 0);

	UINT stride = sizeof(vertex);
	UINT offset = 0;
	
	pContext->IASetVertexBuffers(0, 1, vertexBuffer.getVertexBuffer().GetAddressOf(), &stride, &offset);
	pContext->IASetIndexBuffer(indexBuffer.getIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0u);
	

	//pContext->Draw(vertexBuffer.getBufferSize(), 0u);
	pContext->DrawIndexed(indexBuffer.getBufferSize(), 0u, 0u);

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
		vertex(-0.5f, -0.5f, -0.5f),
		vertex(0.5f, -0.5f, -0.5f),
		vertex(-0.5f, 0.5f, -0.5f),
		vertex(0.5f, 0.5f, -0.5f),
		vertex(-0.5f, -0.5f, 0.5f),
		vertex(0.5f, -0.5f, 0.5f),
		vertex(-0.5f, 0.5f, 0.5f),
		vertex(0.5f, 0.5f, 0.5f),
	};

	vertexBuffer = VertexBuffer(pDevice, v, ARRAYSIZE(v));

	color colors[]{
		color(1.0f, 0.0f, 1.0f),
		color(1.0f, 0.0f, 0.0f),
		color(1.0f, 1.0f, 0.0f),
		color(0.0f, 0.0f, 1.0f),
		color(0.0f, 1.0f, 1.0f),
		color(0.0f, 1.0f, 0.0f),
	};

	colorBuffer = ColorBuffer(pDevice, colors, ARRAYSIZE(colors));

	unsigned short indices[] = {
		0, 2, 1,	2, 3, 1,
		1, 3, 5,	3, 7, 5,
		2, 6, 3,	3, 6, 7,
		4, 5, 7,	4, 7, 6,
		0, 4, 2,	2, 4, 6,
		0, 1, 4,	1, 5, 4
	};

	indexBuffer = IndexBuffer(pDevice, indices, ARRAYSIZE(indices));

}
