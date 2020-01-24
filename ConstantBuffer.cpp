#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(Matrix& mtx)
{
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(Matrix);
	cbd.StructureByteStride = 0u;

	csd.pSysMem = &mtx;
}

Microsoft::WRL::ComPtr<ID3D11Buffer> ConstantBuffer::getConstantBuffer()
{
	return pConstantBuffer;
}

void ConstantBuffer::update(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice)
{
	FrostyExceptions::Exception(pDevice->CreateBuffer(&cbd, &csd, pConstantBuffer.GetAddressOf()));
}

void ConstantBuffer::bind(Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pContext)
{
	pContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
}

