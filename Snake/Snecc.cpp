#include "Snecc.h"

//////////////////SEGMENT//////////////////

Snake::Segment::Segment(LedControl& brd, int brdAddress, Vec2<uint8_t> pos)
	:
	pbrd(&brd),
	brdAddress(brdAddress),
	pos(pos)
{}

void Snake::Segment::Draw() const
{
	pbrd->setLed(brdAddress, pos.GetX(), pos.GetY(), true);
}

//////////////////SNAAAKE//////////////////

Snake::Snake(LedControl& brd, int brdAddress)
	:
	brd(brd),
	size(INITIAL_SIZE),
	brdAddress(brdAddress)
{
	segStack = (Snake::Segment*)calloc(INITIAL_SIZE, sizeof(Snake::Segment));
	for (uint8_t i = 0; i < INITIAL_SIZE; ++i)
	{
		segStack[i] = Segment(brd, brdAddress, Vec2<uint8_t>(STARTING_POS_X, STARTING_POS_Y - i));
	}
}

void Snake::Draw() const
{
	for (uint8_t i = 0; i < INITIAL_SIZE; ++i)
	{
		segStack[i].Draw();
	}
}