#pragma once
#include <Windows.h>
#include <assert.h>

//	define
#define MSGASSERT(VALUE) std::string ErrorText = VALUE; MessageBoxA(nullptr, ErrorText.c_str(), "치명적 에러", MB_OK); assert(false);

namespace UEngineDebug
{
	void OutPutString(const std::string& Text);
}


