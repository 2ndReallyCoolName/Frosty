#pragma once
#pragma comment(lib, "D3DCompiler.lib")
#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include "FrostyExceptions.h"

class PixelShader
{
public:
	PixelShader(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice, LPCWSTR shaderpath);
	PixelShader() = default;
	ID3D11PixelShader* getShader();
	ID3D10Blob* getBlob();

private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pShader = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob = nullptr;
};
