#pragma once
#include <DirectXMath.h>

struct vertex {
	vertex()
		:pos(0.0f, 0.0f, 0.0f), tex(0.0f, 0.0f) {}

	vertex(float x, float y, float z, float tx, float ty)
		:pos(x, y, z), tex(tx, ty) {}

	vertex(float x, float y, float tx, float ty)
		:pos(x, y, 0.0f), tex(tx, ty) {}

	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 tex;
};


struct color {
	color()
		: clr(0.0f, 0.0f, 0.0f, 1.0f) {}

	color(float r, float g, float b)
		: clr(r, g, b, 1.0f) {}

	color(float r, float g, float b, float a)
		: clr(r, g, b, a) {}

	DirectX::XMFLOAT4 clr;
};
