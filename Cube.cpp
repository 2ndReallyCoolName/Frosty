#include "Cube.h"
namespace dx = DirectX;

Cube::Cube(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice, float size)
{
	vertex v[] = {
		vertex(-size, size, size,		0.0f / 4.0f, 1.0f / 3.0f), //0
		vertex(-size, -size, size,		0.0f / 4.0f, 2.0f / 3.0f), //1
		vertex(-size, size, size,		1.0f / 4.0f, 0.0f / 3.0f), //2
		vertex(-size, size, -size,		1.0f / 4.0f, 1.0f / 3.0f), //3
		vertex(-size, -size, -size,		1.0f / 4.0f, 2.0f / 3.0f), //4
		vertex(-size, -size, size,		1.0f / 4.0f, 3.0f / 3.0f),
		vertex(size, size, size,		2.0f / 4.0f, 0.0f / 3.0f),
		vertex(size, size, -size,		2.0f / 4.0f, 1.0f / 3.0f),
		vertex(size, -size, -size,		2.0f / 4.0f, 2.0f / 3.0f),
		vertex(size, -size, size,		2.0f / 4.0f, 3.0f / 3.0f),
		vertex(size, size, size,		3.0f / 4.0f, 1.0f / 3.0f),
		vertex(size, -size, size,		3.0f / 4.0f, 2.0f / 3.0f),
		vertex(-size, size, size,		4.0f / 4.0f, 1.0f / 3.0f),
		vertex(-size, -size, size,		4.0f / 4.0f, 2.0f / 3.0f),
	};

	vertexBuffer = VertexBuffer(pDevice, v, ARRAYSIZE(v));

	unsigned short indices[] = {
			0, 3, 1,	3, 4, 1,
			3, 2, 6,	6, 7, 3,
			4, 3, 7,	7, 8, 4,
			5, 4, 8,	8, 9, 5,
			8, 7, 10,	10, 11, 8,
			11, 10, 12, 12, 13, 11
	};

	indexBuffer = IndexBuffer(pDevice, indices, ARRAYSIZE(indices));
	
	constantBuffer = ConstantBuffer(mtx);
}


void Cube::bind(Microsoft::WRL::ComPtr <ID3D11DeviceContext>& pContext)
{
	vertexBuffer.bind(pContext);
	indexBuffer.bind(pContext);
	//colorBuffer.bind(pContext);
}

void Cube::update(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pContext, float angle)
{
	mtx =
	{
		{
			dx::XMMatrixTranspose(
				dx::XMMatrixRotationZ(angle)
			)
		}
	};

	bind(pContext);
	constantBuffer.update(pDevice);
	constantBuffer.bind(pContext);
}

IndexBuffer& Cube::getIndexBuffer()
{
	return indexBuffer;
}
