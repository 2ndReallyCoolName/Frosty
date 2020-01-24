#pragma once
#include "VertexBuffer.h"
#include "ColorBuffer.h"
#include "IndexBuffer.h"

class Cube
{
public:
	Cube() = default;
	Cube(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice, float size);

	void bind(Microsoft::WRL::ComPtr <ID3D11DeviceContext>& pContext);

	IndexBuffer& getIndexBuffer();

private:
	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;
	ColorBuffer colorBuffer;
};

