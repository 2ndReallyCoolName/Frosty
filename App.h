#pragma once
#include "window.h"

class App
{
public:
	App();
	int start();
private:
	void runFrame(float x, float y, float z, float ax, float ay, float az);
private:
	Window wnd;
	float stride = 0.2f;
};

