#include "Logger.h"
#include <windows.h>

namespace Logger
{
	void Log(const std::string& message)
	{
		OutputDebugStringA(message.c_str());
	}
}
