#include "mouse.h"

void Mouse::onMouseMove(int x, int y) noexcept {
	this->x = x; this->y = y;
	buffer.push(Mouse::Event(Mouse::Event::Type::Move, *this));
	TrimBuffer();
}

void Mouse::onLeftPressed(int x, int y) noexcept {
	this->x = x; this->y = y;
	buffer.push(Mouse::Event(Mouse::Event::Type::LPress, *this));
	TrimBuffer();
}

void Mouse::onRightPressed(int x, int y) noexcept {
	this->x = x; this->y = y;
	buffer.push(Mouse::Event(Mouse::Event::Type::RPress, *this));
	TrimBuffer();
}

void Mouse::onRightReleased(int x, int y) noexcept {
	this->x = x; this->y = y;
	buffer.push(Mouse::Event(Mouse::Event::Type::RRelease, *this));
	TrimBuffer();
}

void Mouse::onLeftReleased(int x, int y) noexcept {
	this->x = x; this->y = y;
	buffer.push(Mouse::Event(Mouse::Event::Type::LRelease, *this));
	TrimBuffer();
}

void Mouse::onWheelUp(int x, int y) noexcept {
	this->x = x; this->y = y;
	buffer.push(Mouse::Event(Mouse::Event::Type::WheelUp, *this));
	TrimBuffer();
}

void Mouse::onWheelDown(int x, int y) noexcept {
	this->x = x; this->y = y;
	buffer.push(Mouse::Event(Mouse::Event::Type::WheelDown, *this));
	TrimBuffer();
}

void Mouse::onWheelDelta(int x, int y, int delta) noexcept {
	wheelDelta += delta;
	while (wheelDelta >= WHEEL_DELTA) {
		wheelDelta -= WHEEL_DELTA;
		onWheelUp(x, y);
	}
	while (wheelDelta <= -WHEEL_DELTA) {
		wheelDelta += WHEEL_DELTA;
		onWheelDown(x, y);
	}
}

void Mouse::onMouseLeave() noexcept {
	this->inWindow = false;
	buffer.push(Mouse::Event(Mouse::Event::Type::Leave, *this));
	TrimBuffer();
}

void Mouse::onMouseEnter() noexcept {
	this->inWindow = true;
	buffer.push(Mouse::Event(Mouse::Event::Type::Enter, *this));
	TrimBuffer();
}

void Mouse::TrimBuffer() noexcept {
	while (buffer.size() > bufferSize) {
		buffer.pop();
	}
}

void Mouse::Flush() noexcept {
	buffer = std::queue<Event>();
}

Mouse::Event Mouse::Read() noexcept {
	if (buffer.size() > 0u) {
		Mouse::Event e = buffer.front();
		buffer.pop();
		return e;
	}
	else {
		return Mouse::Event();
	}
}

