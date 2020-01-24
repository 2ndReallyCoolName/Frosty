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

	vertexShader.bind(pContext);
	pixelShader.bind(pContext);

	pContext->PSSetShaderResources(0, 1, pTexture.GetAddressOf());

	pContext->IASetInputLayout(vertexShader.getInputLayout());
	pContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pContext->RSSetState(vertexShader.getRasterizerState());
	pContext->OMSetDepthStencilState(pDepthStencilState.Get(), 0u);

	initializeVertices();

	constantBuffer = ConstantBuffer(mtx);
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

	constantBuffer.update(pDevice);

	constantBuffer.bind(pContext);
	
	pContext->ClearRenderTargetView(pTarget.Get(), color);
	pContext->ClearDepthStencilView(pDepthStencilView.Get(), 
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	/*vertexBuffer.bind(pContext);
	indexBuffer.bind(pContext);*/
	cube.bind(pContext);
	pContext->DrawIndexed(cube.getIndexBuffer().getBufferSize(), 0u, 0u);

	pSwap->Present(1u, 0u);
}

void Graphics::initializeShaders()
{
	vertexShader = VertexShader(pDevice, L"TextureVS.cso");
	pixelShader = PixelShader(pDevice, L"textureShader.cso");

	FrostyExceptions::Exception(DirectX::CreateWICTextureFromFile(pDevice.Get(), L"..\\Textures\\hex_tile.jpg", nullptr, pTexture.GetAddressOf()));

}

void Graphics::initializeVertices()
{
	vertex v[] = {
		vertex(-0.5f, -0.5f, 1.0f,		0.0f, 1.0f),
		vertex(-0.5f, 0.5f,  1.0f,		0.0f, 0.0f),
		vertex(0.5f, -0.5f, 1.0f,		1.0f, 0.0f),
		vertex(0.5f, 0.5f,  1.0f,		1.0f, 1.0f),
	};

	unsigned short indices[] = {
		0, 1, 3,	0, 3, 2,
	};


	cube = Cube(pDevice, 0.5);

	/*vertexBuffer = VertexBuffer(pDevice, v, ARRAYSIZE(v));
	indexBuffer = IndexBuffer(pDevice, indices, ARRAYSIZE(indices));*/

}
