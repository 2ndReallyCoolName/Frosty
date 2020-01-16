#include "FrostyExceptions.h"
#include <comdef.h>

void FrostyExceptions::Exception(std::string& message)
{
	std::string error_message = "Exception: " + message;
	MessageBoxA(NULL, message.c_str(), "Error", MB_ICONERROR);
}

void FrostyExceptions::Exception(HRESULT hr, std::string& message)
{
	_com_error error(hr);
	std::wstring error_message = L"Exception: " + stringConverter::castWideString(message)
		+ L"\n" + error.ErrorMessage();
	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
}

void FrostyExceptions::Exception(HRESULT hr)
{
	if (FAILED(hr)) {
		_com_error error(hr);
		std::wstring error_message = error.ErrorMessage();
		MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
	}
}
