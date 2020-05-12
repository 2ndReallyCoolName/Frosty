#pragma once
#include "VertexBuffer.h"
#include "ColorBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Matrix.h"

class Cube
{
public:
	Cube() = default;

	Cube(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice, float size);

	void bind(Microsoft::WRL::ComPtr <ID3D11DeviceContext>& pContext);

	void update(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice, Microsoft::WRL::ComPtr <ID3D11DeviceContext>& pContext, float angle);

	IndexBuffer& getIndexBuffer();

private:
	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;
	ColorBuffer colorBuffer;
	ConstantBuffer constantBuffer;
	Matrix mtx;
};

