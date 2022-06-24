//For arduino Mega

#include <LedControl.h>
#include <stdint.h>
#include "Snecc.h"

//Define pins used for buttons
#define CNTRL_UP 22
#define CNTRL_RIGHT 23
#define CNTRL_DOWN 24
#define CNTRL_LEFT 25

//Define pins used for 8x8 Matrix (SPI)
#define DIN 51
#define CS  53
#define CLK 52

//Define other useful stuff
#define BRD_ADDRESS 0
#define BRD_INTENSITY 5 //Can go from 0 to 15
#define BRD_DIMENSIONS 8
#define SNAKE_SPEED_dT_MS 300

LedControl brd(DIN, CLK, CS);
Snake sneck(brd, BRD_ADDRESS);

void Update();
void Draw();

//For update cooldown
uint16_t lastUpdateT = 0;
uint16_t lastDrawT = 0;

void setup()
{
	brd.shutdown(BRD_ADDRESS, false);
	brd.setIntensity(BRD_ADDRESS, BRD_INTENSITY);
	brd.clearDisplay(BRD_ADDRESS);
	pinMode(CNTRL_UP, INPUT);
	pinMode(CNTRL_RIGHT, INPUT);
	pinMode(CNTRL_DOWN, INPUT);
	pinMode(CNTRL_LEFT, INPUT);
}

void loop()
{
	Update();
	Draw();
}

void Update()
{
	if (digitalRead(CNTRL_UP)) sneck.SetDirection(Snake::Direction::up);
	else if (digitalRead(CNTRL_RIGHT)) sneck.SetDirection(Snake::Direction::right);
	else if (digitalRead(CNTRL_DOWN)) sneck.SetDirection(Snake::Direction::down);
	else if (digitalRead(CNTRL_LEFT)) sneck.SetDirection(Snake::Direction::left);
	if (millis() - lastUpdateT > SNAKE_SPEED_dT_MS)
	{
		sneck.Advance();
		lastUpdateT = millis();
	}
}

void Draw()
{
	if (millis() - lastDrawT > SNAKE_SPEED_dT_MS)
	{
		brd.clearDisplay(BRD_ADDRESS);
		sneck.Draw();
		lastDrawT = millis();
	}
}