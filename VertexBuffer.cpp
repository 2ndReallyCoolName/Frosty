#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice, vertex* vertices, int size)
 : size(size)
{
	D3D11_BUFFER_DESC bd = {};
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));

	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(vertex) * size;
	//bd.StructureByteStride = sizeof(vertex);

	D3D11_SUBRESOURCE_DATA sd = {};
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = vertices;

	FrostyExceptions::Exception(pDevice->CreateBuffer(&bd, &sd, pVertexBuffer.GetAddressOf()));
}

Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer::getVertexBuffer()
{
	return pVertexBuffer;
}

int VertexBuffer::getBufferSize()
{
	return size;
}

void VertexBuffer::bind(Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pContext)
{
	UINT stride = sizeof(vertex);
	UINT offset = 0;
	pContext->IASetVertexBuffers(0, 1, pVertexBuffer.GetAddressOf(), &stride, &offset);
}
