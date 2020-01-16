#include "PixelShader.h"

PixelShader::PixelShader(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice, LPCWSTR shaderpath)
{
	FrostyExceptions::Exception(D3DReadFileToBlob(shaderpath, pBlob.GetAddressOf()));

	FrostyExceptions::Exception(pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, pShader.GetAddressOf()));
}

ID3D11PixelShader* PixelShader::getShader()
{
	return pShader.Get();
}

ID3D10Blob* PixelShader::getBlob()
{
	return pBlob.Get();
}
