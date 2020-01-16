#include "ColorBuffer.h"


ColorBuffer::ColorBuffer(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice, const color* colors, int sz)
	:colorBufferSize(sz)
{
	D3D11_BUFFER_DESC bd = {};
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));

	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(color) * sz;

	D3D11_SUBRESOURCE_DATA sd = {};
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = colors;

	FrostyExceptions::Exception(pDevice->CreateBuffer(&bd, &sd, &pColorBuffer));
}

ColorBuffer::ColorBuffer()
	: colorBufferSize(0)
{
}

Microsoft::WRL::ComPtr<ID3D11Buffer> ColorBuffer::getColorBuffer()
{
	return pColorBuffer;
}

int ColorBuffer::getColorBufferSize()
{
	return colorBufferSize;
}
