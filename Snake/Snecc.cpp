#include "Snecc.h"

Snake::Snake(LedControl& brd, int brdAddress)
	:
	brd(brd),
	size(INITIAL_SIZE),
	brdAddress(brdAddress)
{
	segStack = (Snake::Segment*)calloc(INITIAL_SIZE, sizeof(Snake::Segment));
}

Snake::Segment::Segment(LedControl& brd, int brdAddress)
	:
	brd(brd),
	brdAddress(brdAddress)
{	}

void Snake::Segment::Draw() const
{
	brd.setLed(brdAddress, pos.GetX(), pos.GetY(), true);
}

