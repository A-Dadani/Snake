//For arduino Mega

#include <LedControl.h>

//Define pins used for 8x8 Matrix (SPI)
#define DIN 51
#define CS  53
#define CLK 52

//Define other useful stuff
#define BRD_ADRESS 0
#define BRD_INTENSITY 5 //Can go from 0 to 15
#define BRD_DIMENSIONS 8

LedControl brd(DIN, CLK, CS);

void Update();
void Draw();

void setup()
{
	brd.shutdown(BRD_ADRESS, false);
	brd.setIntensity(BRD_ADRESS, BRD_INTENSITY);
	brd.clearDisplay(BRD_ADRESS);
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