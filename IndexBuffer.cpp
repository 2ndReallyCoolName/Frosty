#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice, unsigned short* indices, int size)
	: size(size)
{
	D3D11_BUFFER_DESC bd = {};
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));

	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(short) * size;
	
	D3D11_SUBRESOURCE_DATA sd = {};
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = indices;

	FrostyExceptions::Exception(pDevice->CreateBuffer(&bd, &sd, pIndexBuffer.GetAddressOf()));
}

Microsoft::WRL::ComPtr<ID3D11Buffer> IndexBuffer::getIndexBuffer()
{
	return pIndexBuffer;
}

int IndexBuffer::getBufferSize()
{
	return size;
}

void IndexBuffer::bind(Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pContext)
{
	pContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
}
