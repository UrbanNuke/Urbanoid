#pragma once

#define ASSERT(x) if (!(x)) __debugbreak();
#define glCall(x) glClearError();\
	x;\
	ASSERT(glLogCall(#x, __FILE__, __LINE__));\

void glClearError();
bool glLogCall(const char* fn, const char* file, const int line);
