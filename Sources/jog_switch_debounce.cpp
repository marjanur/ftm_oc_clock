
#include "jog_switch_debounce.h"
#include "hardware.h"
#include "pit.h"

using namespace USBDM;

// Jog switch on LCD board
using EastSwitch   = USBDM::GpioC<0,ActiveLow>;
using SouthSwitch  = USBDM::GpioC<1,ActiveLow>;
using WestSwitch   = USBDM::GpioD<6,ActiveLow>;
using CentreSwitch = USBDM::GpioD<5,ActiveLow>;
using NorthSwitch  = USBDM::GpioB<1,ActiveLow>;

// Time between samples of the input
static constexpr float DEBOUNCE_SAMPLE_TIME = 5*ms;

// Number of debug samples for a stable input
static constexpr unsigned DEBOUNCE_SAMPLES = 5;

int switchValue=0;
using Timer        = Pit;
using TimerChannel = Pit::Channel<1>;

/*
 * This callback is set programmatically
 *
 * It polls the switch and provides a debounced result in switchValue
 */
void deBouncer() {
	static int switchCounter = 0;
	static int lastSwitch    = false;

	// Encode all switch values as a single binary number
	int currentSwitch =
			(EastSwitch::read()<<4)|
			(SouthSwitch::read()<<3)|
			(WestSwitch::read()<<2)|
			(CentreSwitch::read()<<1)|
			(NorthSwitch::read()<<0);


	if(lastSwitch == currentSwitch){
		switchCounter++;
	}

	else{
		switchCounter = 0;
	}

	if(switchCounter == DEBOUNCE_SAMPLES){
		switch(currentSwitch){
		case 0:
			console.writeln("noSwitch");
			switchValue=0;
			break;
		case 16:
			console.writeln("eastSwitch");
			switchValue=16;
			break;
		case 8:
			console.writeln("southSwitch");
			switchValue=8;
			break;
		case 4:
			console.writeln("westSwitch");
			switchValue=4;
			break;
		case 2:
			console.writeln("cetreSwitch");
			switchValue=2;
			break;
		case 1:
			console.writeln("northSwitch");
			switchValue=1;
			break;

		}
	}
	lastSwitch = currentSwitch;

}

void initJogSwitch() {
	EastSwitch::setInput(PinPull_Up, PinAction_None, PinFilter_Passive);
	SouthSwitch::setInput(PinPull_Up, PinAction_None, PinFilter_Passive);
	WestSwitch::setInput(PinPull_Up, PinAction_None, PinFilter_Passive);
	CentreSwitch::setInput(PinPull_Up, PinAction_None, PinFilter_Passive);
	NorthSwitch::setInput(PinPull_Up, PinAction_None, PinFilter_Passive);

	// Do default configure
	Pit::configure();

	// Set handler for channel 1 programmatically
	TimerChannel::setCallback(deBouncer);

	// Setup debouncer to execute every 5 ms (200 Hz)
	TimerChannel::configure(DEBOUNCE_SAMPLE_TIME, PitChannelIrq_Enabled);

	// Enable interrupts on the channel
	TimerChannel::enableNvicInterrupts();

	// Check for errors so far
	checkError();
}


int getJogswitch() {

	TimerChannel::disableNvicInterrupts();

	int saveSwitch = switchValue;
	switchValue = 0;

	TimerChannel::enableNvicInterrupts();

	return saveSwitch;
}


