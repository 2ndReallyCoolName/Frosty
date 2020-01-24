#include "Sampler.h"

Sampler::Sampler(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice)
{
	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sd.MinLOD = 0;
	sd.MaxLOD = D3D11_FLOAT32_MAX;

	FrostyExceptions::Exception(pDevice->CreateSamplerState(&sd, pSampler.GetAddressOf()));
}

void Sampler::bind(Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pContext)
{
	pContext->PSSetSamplers(0, 1, pSampler.GetAddressOf());
}
