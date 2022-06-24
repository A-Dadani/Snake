//For arduino Mega

#include <LedControl.h>
#include "Snecc.h"

//Define pins used for 8x8 Matrix (SPI)
#define DIN 51
#define CS  53
#define CLK 52

//Define other useful stuff
#define BRD_ADDRESS 0
#define BRD_INTENSITY 5 //Can go from 0 to 15
#define BRD_DIMENSIONS 8

LedControl brd(DIN, CLK, CS);
Snake sneck(brd, BRD_ADDRESS);

void Update();
void Draw();

void setup()
{
	brd.shutdown(BRD_ADDRESS, false);
	brd.setIntensity(BRD_ADDRESS, BRD_INTENSITY);
	brd.clearDisplay(BRD_ADDRESS);
}

void loop()
{
}

void Update()
{
}

void Draw()
{
}