#pragma once
#include <conio.h>
struct KeyboardEventListener
{
	virtual void handleKey(char k) = 0;
	virtual const char* getKbChars() = 0;
};