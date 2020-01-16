#pragma once
#include "window.h"

class App
{
public:
	App();
	int start();
private:
	void runFrame(float angle);
private:
	Window wnd;
};

