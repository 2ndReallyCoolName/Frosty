#include "App.h"

App::App()
	:wnd(800, 300, L"Wynter") {}

int App::start() {
	WPARAM ecode;
	float angle = 0.0f;
	while (true) {
		ecode = Window::ProcessMessage();
		if (ecode == -1) {
			break;
		}
		runFrame(angle);
		angle += 0.01f;
	}
	return 0;
}

void App::runFrame(float angle) {
	wnd.graphics().RenderFrame(angle, wnd.mouse.getPosX() / 400.0f - 1.0f, -wnd.mouse.getPosY() / 150.0f + 1.0f);
}