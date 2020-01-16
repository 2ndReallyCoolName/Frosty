#pragma once
#include "stringConverter.h"
#include <Windows.h>

class FrostyExceptions
{
public:
	static void Exception(std::string& message);
	static void Exception(HRESULT hr, std::string& message);
	static void Exception(HRESULT hr);
};

