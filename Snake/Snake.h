#pragma once

#include <LedControl.h>
#include <cstdint>

#define INITIAL_SIZE 3

class Snake
{
public:
	Snake(LedControl& brd);
private:
	LedControl& brd;
	uint8_t size; //Max size is 64 don't need more than a byte
};