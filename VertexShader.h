#pragma once
#pragma comment(lib, "D3DCompiler.lib")
#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include "FrostyExceptions.h"

class VertexShader
{
public:
	VertexShader(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice, LPCWSTR shaderpath);
	VertexShader() = default;
	ID3D11VertexShader* getShader();
	ID3D10Blob* getBlob();
	ID3D11InputLayout* getInputLayout();
	ID3D11RasterizerState* getRasterizerState();

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pShader = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> pRasterizerState = nullptr;
};


