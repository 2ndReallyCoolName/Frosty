#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "Matrix.h"
#include "FrostyExceptions.h"

class ConstantBuffer
{
public:
	ConstantBuffer() = default;
	ConstantBuffer(Matrix& mtx);
	Microsoft::WRL::ComPtr<ID3D11Buffer> getConstantBuffer();

	void update(Microsoft::WRL::ComPtr<ID3D11Device>&);
	void bind(Microsoft::WRL::ComPtr <ID3D11DeviceContext>& pContext);
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer  = nullptr;
	D3D11_BUFFER_DESC cbd;
	D3D11_SUBRESOURCE_DATA csd = {};
};