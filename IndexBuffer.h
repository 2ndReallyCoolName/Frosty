#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "Vertex.h"
#include "FrostyExceptions.h"

class IndexBuffer
{
public:
	IndexBuffer() = default;
	IndexBuffer(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice, unsigned short* indices, int size);
	Microsoft::WRL::ComPtr<ID3D11Buffer> getIndexBuffer();
	int getBufferSize();
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer = nullptr;
	int size = 0;
};

