#include "VertexShader.h"

VertexShader::VertexShader(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice, LPCWSTR shaderpath)
{
	FrostyExceptions::Exception(D3DReadFileToBlob(shaderpath, pBlob.GetAddressOf()));
	
	FrostyExceptions::Exception(pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, pShader.GetAddressOf()));
	
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	FrostyExceptions::Exception(pDevice->CreateInputLayout(ied, (UINT)ARRAYSIZE(ied),
		pBlob->GetBufferPointer(), pBlob->GetBufferSize(), pInputLayout.GetAddressOf()));


	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));
	rd.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;

	FrostyExceptions::Exception(pDevice->CreateRasterizerState(&rd, pRasterizerState.GetAddressOf()));
}

ID3D11VertexShader* VertexShader::getShader()
{
	return pShader.Get();
}

ID3D10Blob* VertexShader::getBlob()
{
	return pBlob.Get();
}

ID3D11InputLayout* VertexShader::getInputLayout()
{
	return pInputLayout.Get();
}

ID3D11RasterizerState* VertexShader::getRasterizerState()
{
	return pRasterizerState.Get();
}
