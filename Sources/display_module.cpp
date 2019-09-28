#include <stdlib.h>
#include "lcd.h"
#include "spi.h"
#include <display_module.h>

// Access to USBDM name-space
using namespace USBDM;

// SPI interface
Spi0 spi;

// LCD interface using SPI
Lcd lcd(spi);

// Colour for LCD background
static constexpr int BACKGROUND_COLOUR = (BLACK);

void display7Segment(int digit,int x,int y, int smallLength, int longLength);

void displayOff(){
	lcd.clear(BACKGROUND_COLOUR);
	lcd.setFont(fontLarge).setForeground(RED).setBackground(BLACK);
	lcd.putStr("Output is off!", 14, LCD_Y_MIN + 7);

}

void displayClockkInfo(int index)
{
lcd.clear(BACKGROUND_COLOUR);
lcd.setFont(fontLarge).setForeground(GREEN).setBackground(BLACK);

	switch(index)
	{
	case 0:
		display7Segment(1,80,50,2,15);
		lcd.putStr("Hz", 103, 50);
		lcd.putStr("Min Frequency", 14, LCD_Y_MIN + 7);
		break;
	case 1:
		display7Segment(2,80,50,2,15);
		lcd.putStr("Hz", 103, 50);
		break;
	case 2:
		display7Segment(5,80,50,2,15);
		lcd.putStr("Hz", 103, 50);
		break;
	case 3:
		display7Segment(1,50,50,2,15);
		display7Segment(0,80,50,2,15);

		lcd.putStr("Hz", 103, 50);
		break;
	case 4:
		display7Segment(2,50,50,2,15);
		display7Segment(0,80,50,2,15);
		lcd.putStr("Hz", 103, 50);
		break;
	case 5:
		display7Segment(5,50,50,2,15);
		display7Segment(0,80,50,2,15);
		lcd.putStr("Hz", 103, 50);
		break;
	case 6:
		display7Segment(1,20,50,2,15);
		display7Segment(0,50,50,2,15);
		display7Segment(0,80,50,2,15);
		lcd.putStr("Hz", 103, 50);
		break;
	case 7:
		display7Segment(2,20,50,2,15);
		display7Segment(0,50,50,2,15);
		display7Segment(0,80,50,2,15);
		lcd.putStr("Hz", 103, 50);
		break;
	case 8:
		display7Segment(5,20,50,2,15);
		display7Segment(0,50,50,2,15);
		display7Segment(0,80,50,2,15);
		lcd.putStr("Hz", 103, 50);
		break;
	case 9:
		display7Segment(1,80,50,2,15);
		lcd.putStr("KHz", 103, 50);
		break;
	case 10:
		display7Segment(2,80,50,2,15);
		lcd.putStr("KHz", 103, 50);
		break;
	case 11:
		display7Segment(5,80,50,2,15);
		lcd.putStr("KHz", 103, 50);
		break;
	case 12:
		display7Segment(1,50,50,2,15);
		display7Segment(0,80,50,2,15);
		lcd.putStr("KHz", 103, 50);
		break;
	case 13:
		display7Segment(2,50,50,2,15);
		display7Segment(0,80,50,2,15);
		lcd.putStr("KHz", 103, 50);
		break;
	case 14:
		display7Segment(5,50,50,2,15);
		display7Segment(0,80,50,2,15);
		lcd.putStr("KHz", 103, 50);
		break;
	case 15:
		display7Segment(1,20,50,2,15);
		display7Segment(0,50,50,2,15);
		display7Segment(0,80,50,2,15);
		lcd.putStr("KHz", 103, 50);
		break;
	case 16:
		display7Segment(2,20,50,2,15);
		display7Segment(0,50,50,2,15);
		display7Segment(0,80,50,2,15);
		lcd.putStr("KHz", 103, 50);
		break;
	case 17:
		display7Segment(5,20,50,2,15);
		display7Segment(0,50,50,2,15);
		display7Segment(0,80,50,2,15);
		lcd.putStr("KHz", 103, 50);
		break;
	case 18:
		display7Segment(1,80,50,2,15);
		lcd.putStr("MHz", 103, 50);
		break;
	case 19:
		display7Segment(2,80,50,2,15);
		lcd.putStr("MHz", 103, 50);
		lcd.putStr("Max Frequency", 14, LCD_Y_MIN + 7);
		break;
	default:
		break;
	}


}



void display7Segment(int digit,int x,int y, int smallLength, int longLength) {


	switch(digit){
	case 0:
		lcd.drawRect(x,y,x+longLength,y+smallLength,1,GREEN); // segment d
		lcd.drawRect(x+longLength+2,y+smallLength+1,x+longLength+2+smallLength,y+smallLength+longLength,1,GREEN); // segment c
		lcd.drawRect(x-2,y+smallLength+1,x-2-smallLength,y+longLength+smallLength,1,GREEN); // segment e

		// doing the top half by shifting y and using same drawing codes
		y+=longLength+1;

		lcd.drawRect(x+longLength+2,y+smallLength+1,x+longLength+2+smallLength,y+smallLength+longLength,1,GREEN); // segment b
		lcd.drawRect(x-2,y+smallLength+1,x-2-smallLength,y+longLength+smallLength,1,GREEN); // segment f
		lcd.drawRect(x,y+longLength+3,x+longLength,y+longLength+smallLength+3,1,GREEN);// segment a
		break;

	case 1:

		lcd.drawRect(x+longLength+2,y+smallLength+1,x+longLength+2+smallLength,y+smallLength+longLength,1,GREEN); // segment c

		// doing the top half by shifting y and using same drawing codes
		y+=longLength+1;

		lcd.drawRect(x+longLength+2,y+smallLength+1,x+longLength+2+smallLength,y+smallLength+longLength,1,GREEN); // segment b
		break;

	case 2:
		lcd.drawRect(x,y,x+longLength,y+smallLength,1,GREEN); // segment d

		lcd.drawRect(x-2,y+smallLength+1,x-2-smallLength,y+longLength+smallLength,1,GREEN); // segment e

		// doing the top half by shifting y and using same drawing codes
		y+=longLength+1;
		lcd.drawRect(x,y,x+longLength,y+smallLength,1,GREEN); // segment g
		lcd.drawRect(x+longLength+2,y+smallLength+1,x+longLength+2+smallLength,y+smallLength+longLength,1,GREEN); // segment b

		lcd.drawRect(x,y+longLength+3,x+longLength,y+longLength+smallLength+3,1,GREEN);// segment a
		break;

	case 3:
		lcd.drawRect(x,y,x+longLength,y+smallLength,1,GREEN); // segment d
		lcd.drawRect(x+longLength+2,y+smallLength+1,x+longLength+2+smallLength,y+smallLength+longLength,1,GREEN); // segment c

		// doing the top half by shifting y and using same drawing codes
		y+=longLength+1;
		lcd.drawRect(x,y,x+longLength,y+smallLength,1,GREEN); // segment g
		lcd.drawRect(x+longLength+2,y+smallLength+1,x+longLength+2+smallLength,y+smallLength+longLength,1,GREEN); // segment b

		lcd.drawRect(x,y+longLength+3,x+longLength,y+longLength+smallLength+3,1,GREEN);// segment a
		break;

	case 4:

		lcd.drawRect(x+longLength+2,y+smallLength+1,x+longLength+2+smallLength,y+smallLength+longLength,1,GREEN); // segment c


		// doing the top half by shifting y and using same drawing codes
		y+=longLength+1;
		lcd.drawRect(x,y,x+longLength,y+smallLength,1,GREEN); // segment g
		lcd.drawRect(x+longLength+2,y+smallLength+1,x+longLength+2+smallLength,y+smallLength+longLength,1,GREEN); // segment f
		lcd.drawRect(x-2,y+smallLength+1,x-2-smallLength,y+longLength+smallLength,1,GREEN); // segment b

		break;
	case 5:

		lcd.drawRect(x,y,x+longLength,y+smallLength,1,GREEN); // segment d
		lcd.drawRect(x+longLength+2,y+smallLength+1,x+longLength+2+smallLength,y+smallLength+longLength,1,GREEN); // segment c


		// doing the top half by shifting y and using same drawing codes
		y+=longLength+1;
		lcd.drawRect(x,y,x+longLength,y+smallLength,1,GREEN); // segment g

		lcd.drawRect(x-2,y+smallLength+1,x-2-smallLength,y+longLength+smallLength,1,GREEN); // segment f
		lcd.drawRect(x,y+longLength+3,x+longLength,y+longLength+smallLength+3,1,GREEN);// segment a

		break;
	case 6:

		lcd.drawRect(x,y,x+longLength,y+smallLength,1,GREEN); // segment d
		lcd.drawRect(x+longLength+2,y+smallLength+1,x+longLength+2+smallLength,y+smallLength+longLength,1,GREEN); // segment c
		lcd.drawRect(x-2,y+smallLength+1,x-2-smallLength,y+longLength+smallLength,1,GREEN); // segment e

		// doing the top half by shifting y and using same drawing codes
		y+=longLength+1;
		lcd.drawRect(x,y,x+longLength,y+smallLength,1,GREEN); // segment g

		lcd.drawRect(x-2,y+smallLength+1,x-2-smallLength,y+longLength+smallLength,1,GREEN); // segment f
		lcd.drawRect(x,y+longLength+3,x+longLength,y+longLength+smallLength+3,1,GREEN);// segment a

		break;

	case 7:


		lcd.drawRect(x+longLength+2,y+smallLength+1,x+longLength+2+smallLength,y+smallLength+longLength,1,GREEN); // segment c


		// doing the top half by shifting y and using same drawing codes
		y+=longLength+1;

		lcd.drawRect(x+longLength+2,y+smallLength+1,x+longLength+2+smallLength,y+smallLength+longLength,1,GREEN); // segment b

		lcd.drawRect(x,y+longLength+3,x+longLength,y+longLength+smallLength+3,1,GREEN);// segment a

		break;

	case 8:

		lcd.drawRect(x,y,x+longLength,y+smallLength,1,GREEN); // segment d
		lcd.drawRect(x+longLength+2,y+smallLength+1,x+longLength+2+smallLength,y+smallLength+longLength,1,GREEN); // segment c
		lcd.drawRect(x-2,y+smallLength+1,x-2-smallLength,y+longLength+smallLength,1,GREEN); // segment e

		// doing the top half by shifting y and using same drawing codes
		y+=longLength+1;
		lcd.drawRect(x,y,x+longLength,y+smallLength,1,GREEN); // segment g
		lcd.drawRect(x+longLength+2,y+smallLength+1,x+longLength+2+smallLength,y+smallLength+longLength,1,GREEN); // segment b
		lcd.drawRect(x-2,y+smallLength+1,x-2-smallLength,y+longLength+smallLength,1,GREEN); // segment f
		lcd.drawRect(x,y+longLength+3,x+longLength,y+longLength+smallLength+3,1,GREEN);// segment a

		break;
	case 9:

		lcd.drawRect(x,y,x+longLength,y+smallLength,1,GREEN); // segment d
		lcd.drawRect(x+longLength+2,y+smallLength+1,x+longLength+2+smallLength,y+smallLength+longLength,1,GREEN); // segment c

		// doing the top half by shifting y and using same drawing codes
		y+=longLength+1;
		lcd.drawRect(x,y,x+longLength,y+smallLength,1,GREEN); // segment g
		lcd.drawRect(x+longLength+2,y+smallLength+1,x+longLength+2+smallLength,y+smallLength+longLength,1,GREEN); // segment b
		lcd.drawRect(x-2,y+smallLength+1,x-2-smallLength,y+longLength+smallLength,1,GREEN); // segment f
		lcd.drawRect(x,y+longLength+3,x+longLength,y+longLength+smallLength+3,1,GREEN);// segment a

		break;


	}

}
