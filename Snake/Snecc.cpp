#include "Snecc.h"

//////////////////SEGMENT//////////////////

Snake::Segment::Segment(LedControl& brd, int brdAddress, Vec2<uint8_t> pos)
	:
	pbrd(&brd),
	brdAddress(brdAddress),
	pos(pos)
{}

void Snake::Segment::SetPos(const Vec2<uint8_t>& newPos)
{
	pos = newPos;
}

void Snake::Segment::Draw() const
{
	pbrd->setLed(brdAddress, pos.GetY(), pos.GetX(), true);
}

//////////////////SNAAAKE//////////////////

Snake::Snake(LedControl& brd, int brdAddress)
	:
	brd(brd),
	size(INITIAL_SIZE),
	brdAddress(brdAddress),
	snakeDirection(Snake::Direction::down),
	nextSegmentRotation(size - 1),
	snakeHead(segStack[0]),
	indexOfHeadInStack(0)
{
	segStack = (Snake::Segment*)calloc(INITIAL_SIZE, sizeof(Snake::Segment));
	for (uint8_t i = 0; i < INITIAL_SIZE; ++i)
	{
		segStack[i] = Segment(brd, brdAddress, Vec2<uint8_t>(STARTING_POS_X, STARTING_POS_Y - i));
	}
	snakeHead = segStack[0];
}

void Snake::SetDirection(Snake::Direction dir)
{
	if ((dir == Snake::Direction::down && snakeDirection == Snake::Direction::up) ||
		(dir == Snake::Direction::up && snakeDirection == Snake::Direction::down) ||
		(dir == Snake::Direction::left && snakeDirection == Snake::Direction::right) ||
		(dir == Snake::Direction::right && snakeDirection == Snake::Direction::left))
	{
		return;
	}

	snakeDirection = dir;
}

bool Snake::IsCollidingWithSelf() const
{
	for (uint8_t i = 0; i < size; ++i)
	{
		if (i != indexOfHeadInStack &&
			snakeHead.GetPos() == segStack[i].GetPos())
		{
			return true;
		}
	}
	return false;
}

void Snake::Advance()
{
	switch (snakeDirection)
	{
	case Snake::Direction::left:
		segStack[nextSegmentRotation].SetPos(snakeHead.GetPos() - Vec2<uint8_t>(1, 0));
		break;
	case Snake::Direction::right:
		segStack[nextSegmentRotation].SetPos(snakeHead.GetPos() + Vec2<uint8_t>(1, 0));
		break;
	case Snake::Direction::up:
		segStack[nextSegmentRotation].SetPos(snakeHead.GetPos() - Vec2<uint8_t>(0, 1));
		break;
	case Snake::Direction::down:
		segStack[nextSegmentRotation].SetPos(snakeHead.GetPos() + Vec2<uint8_t>(0, 1));
		break;
	}
	snakeHead = segStack[nextSegmentRotation];
	indexOfHeadInStack = nextSegmentRotation;
	nextSegmentRotation = (nextSegmentRotation ? nextSegmentRotation - 1 : size - 1);
}

void Snake::Draw() const
{
	for (uint8_t i = 0; i < size; ++i)
	{
		segStack[i].Draw();
	}
}