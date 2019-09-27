#include <stdlib.h>
#include "lcd.h"
#include "hardware.h"
#include "header.h"
#include "spi.h"

// Access to USBDM name-space
using namespace USBDM;

// SPI interface
Spi0 spi;

// LCD interface using SPI
Lcd lcd(spi);

// Colour for LCD background
static constexpr int BACKGROUND_COLOUR = (BLACK);

using CentreSwitch = USBDM::GpioD<5,ActiveLow>;

int main1()
{
	// Set LCD defaults
	lcd.setFont(fontLarge).setForeground(RED).setBackground(BLACK);

	int y = 30;
	int x = 10;
	string Freq [19] = {"1 Hz", "2 Hz", "5 Hz", 
						"10 Hz", "20 Hz", "50 Hz", 
						" 100 Hz", "200 Hz", "500 Hz", 
						"1 kHz", "2 kHz", "5 kHz", 
						"10 kHz", "20 kHz", "50 kHz", 
						"100 kHz", "200 kHz", "500 kHz",
						"1 MHz", "2 MHz", "5 MHz" };

		lcd.putStr(Freq[N], x, y);
			if (N == 0)
			{
				lcd.putStr("Min Frequency", x, LCD_Y_MIN + 1);
			}
			if (N == 19)
			{
				lcd.putStr("Max Frequency", x, LCD_Y_MIN + 1);
			}
	}

	return 0;
}
