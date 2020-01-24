#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "FrostyExceptions.h"

class Sampler
{
public:
	Sampler(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice);
	Sampler() = default;
	void bind(Microsoft::WRL::ComPtr <ID3D11DeviceContext>& pContext);
protected:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;
};

