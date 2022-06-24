#pragma once

#include <LedControl.h>
#include <stdint.h>
#include <stdlib.h>
#include "Vec2.h"

#define INITIAL_SIZE 3

class Snake
{
private:
	class Segment
	{
	public:
		Segment(LedControl& brd, int brdAddress);
		Vec2<uint8_t> GetPos() const { return pos; }
		void Draw() const;
	private:
		LedControl& brd;
		const int brdAddress;
		Vec2<uint8_t> pos;
	};
public:
	Snake(LedControl& brd, int brdAddress);
private:
	LedControl& brd;
	uint8_t size; //Max size is 64 don't need more than a byte
	Vec2<uint8_t> headPos;
	Segment* segStack = nullptr;
	const int brdAddress;
};