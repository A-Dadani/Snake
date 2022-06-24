#include "Food.h"

Food::Food(LedControl& brd, int brdAddress, uint8_t randomPin, uint8_t brdDim)
	:
	brd(brd),
	brdAddress(brdAddress),
	randomPin(randomPin),
	brdDim(brdDim)
{
	randomSeed(analogRead(randomPin));
	pos.SetX(random(brdDim));
	pos.SetY(random(brdDim));
}

void Food::Randomize()
{
	pos.SetX(random(brdDim));
	pos.SetY(random(brdDim));
}

void Food::Draw() const
{
	brd.setLed(brdAddress, pos.GetY(), pos.GetX(), true);
}