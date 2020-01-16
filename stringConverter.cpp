#include "stringConverter.h"

std::wstring stringConverter::castWideString(std::string str)
{
	return std::wstring(str.begin(), str.end());
}
