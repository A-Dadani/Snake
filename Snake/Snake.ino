//For arduino Mega

#include <LedControl.h>
#include <stdint.h>
#include "Snecc.h"
#include "Food.h"

//!!DO NOT USE PIN 2 IT IS USED FOR RANDOM NUMBER GENERATION!!

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
#define RANDOM_PIN 2

LedControl brd(DIN, CLK, CS);
Snake sneck(brd, BRD_ADDRESS);
Food food(brd, BRD_ADDRESS, RANDOM_PIN, BRD_DIMENSIONS);

void Update();
void Draw();

//For update/draw cooldown
uint16_t lastUpdateT = 0;
uint16_t lastDrawT = 0;

bool isLost = false;

void setup()
{
	Serial.begin(9600);
	brd.shutdown(BRD_ADDRESS, false);
	brd.setIntensity(BRD_ADDRESS, BRD_INTENSITY);
	brd.clearDisplay(BRD_ADDRESS);
	randomSeed(analogRead(RANDOM_PIN));
	pinMode(CNTRL_UP, INPUT);
	pinMode(CNTRL_RIGHT, INPUT);
	pinMode(CNTRL_DOWN, INPUT);
	pinMode(CNTRL_LEFT, INPUT);
}

void loop()
{
	if (!isLost) Update();
	if (!isLost) Draw();
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
		if (sneck.GetHeadPos().GetX() >= BRD_DIMENSIONS ||
			sneck.GetHeadPos().GetY() >= BRD_DIMENSIONS ||
			sneck.IsCollidingWithSelf())
		{
			isLost = true;
		}
		if (sneck.GetHeadPos() == food.GetPosition())
		{
			sneck.Grow();
			food.Randomize();
		}
		lastUpdateT = millis();
	}
}

void Draw()
{
	if (millis() - lastDrawT > SNAKE_SPEED_dT_MS)
	{
		brd.clearDisplay(BRD_ADDRESS);
		sneck.Draw();
		food.Draw();
		lastDrawT = millis();
	}
}