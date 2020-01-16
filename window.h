#pragma once
#include "Frosty.h"
#include "keyboard.h"
#include "mouse.h"
#include "graphics.h"
#include <string.h>
#include <sstream>
#include <memory>

class Window {
private:
	class WindowClass {
	public:
		static LPCWSTR GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr LPCWSTR wndClassName = L"Wynter";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	Window(int width, int height, LPCWSTR name) noexcept;
	~Window();
	Window(const Window&) = delete;
	Window& operator= (const Window&) = delete;
	void setTitle(const LPCWSTR title);

	static WPARAM ProcessMessage();

	Graphics& graphics();

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	Keyboard keyboard;
	Mouse mouse;

private:
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Graphics> pGraphics;
};

#define WYNT_EXCEPT(hr) Window::Exception(__LINE__, __FILE__, hr)
