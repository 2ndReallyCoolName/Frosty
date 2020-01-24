#pragma once
#include <wrl.h>
#include <d3d11.h>
#include "Vertex.h"
#include "FrostyExceptions.h"

class ColorBuffer
{
public:
	ColorBuffer(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice, const color* colors, int sz);
	ColorBuffer();
	Microsoft::WRL::ComPtr<ID3D11Buffer> getColorBuffer();
	int getColorBufferSize();
	void bind(Microsoft::WRL::ComPtr <ID3D11DeviceContext>& pContext);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pColorBuffer = nullptr;
	int colorBufferSize = 0;
};


