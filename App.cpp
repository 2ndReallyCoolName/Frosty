#include "App.h"

App::App()
	:wnd(800, 300, L"Wynter") {}

int App::start() {
	WPARAM ecode;
	float ax = 0.0f, ay = 0.0f, az = 0.0f;
	float x = 0.0f, y = 0.0f, z = 0.0f;
	char c = 'a';
	while (true) {
		ecode = Window::ProcessMessage();
		if (ecode == -1) {
			break;
		}
		c = wnd.keyboard.ReadChar();
		if (c == 'w') {z += stride;}
		if (c == 's') { z -= stride; }
		if (c == 'd') { x += stride; }
		if (c == 'a') { x -= stride; }
		if (c == 'q') { ay += stride; }
		if (c == 'e') { ay -= stride; }
		if (c == 'r') { ax += stride; }
		if (c == 'f') { ax -= stride; }
		if (c == 'x') { y += stride; }
		if (c == 'z') { y -= stride; }
		if (c == 'c') { az += stride; }
		if (c == 'v') { az -= stride; }

		runFrame(x, y, z, ax, ay, az);
	}
	return 0;
}

void App::runFrame(float x, float y, float z, float ax, float ay, float az) {
	wnd.graphics().RenderFrame(az, ax, ay, x, y, z + 1.5f);
}