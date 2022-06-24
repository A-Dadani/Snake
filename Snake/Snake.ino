//For arduino Mega

#include <LedControl.h>
#include <stdint.h>
#include "Snecc.h"

//Define pins used for 8x8 Matrix (SPI)
#define DIN 51
#define CS  53
#define CLK 52

//Define other useful stuff
#define BRD_ADDRESS 0
#define BRD_INTENSITY 5 //Can go from 0 to 15
#define BRD_DIMENSIONS 8
#define SNAKE_SPEED_dT_MS 500

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
	//sneck.Draw();
	//sneck.Advance();
}

void loop()
{
	Update();
	Draw();
}

void Update()
{
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