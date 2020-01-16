#pragma once
#include <Windows.h>
#include <queue>

class Mouse {
	friend class Window;
public:
	class Event {
	public:
		enum class Type {
			LPress, LRelease, RPress, RRelease, WheelUp, WheelDown, Move, Enter, Leave, Invalid
		};
	private:
		Type type;
		bool leftIsPressed, rightIsPressed;
		int x, y;
	public:
		Event() noexcept
			: type(Type::Invalid), leftIsPressed(false), rightIsPressed(false), x(0), y(0) {}
		Event(Type type, const Mouse& parent) noexcept
			: type(type), leftIsPressed(parent.LeftIsPressed()),
			rightIsPressed(parent.RightIsPressed()),
			x(parent.getPosX()), y(parent.getPosY()) {}

		bool isValid() const noexcept {
			return type != Type::Invalid;
		}
		Type getType() const noexcept {
			return type;
		}
		std::pair<int, int> getPos() const noexcept {
			return { x, y };
		}
		int getPosX() const noexcept {
			return x;
		}
		int getPosY() const noexcept {
			return y;
		}
		bool LeftIsPressed() const noexcept {
			return leftIsPressed;
		}
		bool RightIsPressed() const noexcept {
			return rightIsPressed;
		}

	};
public:
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;

	bool LeftIsPressed() const noexcept { return leftIsPressed; }
	bool RightIsPressed() const noexcept { return rightIsPressed; }
	int getPosX() const noexcept { return x; }
	int getPosY() const noexcept { return y; }
	std::pair<int, int> getPos() { return { x, y }; }
	bool isInWindow() const noexcept { return inWindow; }

	Event Read() noexcept;

	bool IsEmpty() const noexcept {
		return buffer.empty();
	}

	void Flush() noexcept;
private:
	void onMouseMove(int x, int y) noexcept;
	void onLeftPressed(int x, int y) noexcept;
	void onRightPressed(int x, int y) noexcept;
	void onRightReleased(int x, int y) noexcept;
	void onLeftReleased(int x, int y) noexcept;
	void onWheelUp(int x, int y) noexcept;
	void onWheelDown(int x, int y) noexcept;
	void onMouseLeave() noexcept;
	void onMouseEnter() noexcept;
	void TrimBuffer() noexcept;
	void onWheelDelta(int x, int y, int delta) noexcept;

private:
	static constexpr unsigned int bufferSize = 16u;
	int x = 0; int y = 0;
	int wheelDelta = 0;
	bool leftIsPressed = false; bool rightIsPressed = false;
	bool inWindow = true;
	std::queue<Event> buffer;
};
