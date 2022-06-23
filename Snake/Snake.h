#pragma once

#include <LedControl.h>

class Snake
{
public:
	Snake(LedControl& brd);
private:
	LedControl& brd;
};