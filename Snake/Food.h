#pragma once

#include <LedControl.h>
#include <stdint.h>
#include "Vec2.h"

class Food
{
public:
	Food(LedControl& brd, int brdAddress, uint8_t randomPin, uint8_t brdDim);
	void Randomize();
	void Draw() const;
private:
	LedControl& brd;
	Vec2<uint8_t> pos;
	const int brdAddress;
	const uint8_t randomPin;
	const uint8_t brdDim;
};