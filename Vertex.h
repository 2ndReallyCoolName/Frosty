#pragma once
#include <DirectXMath.h>

struct vertex {
	vertex()
		:pos(0.0f, 0.0f) {}

	vertex(float x, float y)
		:pos(x, y) {}

	DirectX::XMFLOAT2 pos;
};