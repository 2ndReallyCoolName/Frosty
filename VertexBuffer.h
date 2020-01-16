#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "Vertex.h"
#include "FrostyExceptions.h"

class VertexBuffer
{
public:
	VertexBuffer() = default;
	VertexBuffer(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice, vertex* vertices, int size);
	Microsoft::WRL::ComPtr<ID3D11Buffer> getVertexBuffer();
	int getBufferSize();
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer = nullptr;
	int size = 0;
};

