#include "hardware.h"
#include "header.h"
#include "pit.h"

using namespace USBDM;

// Jog switch on LCD board
using EastSwitch   = USBDM::GpioC<0,ActiveLow>;
using SouthSwitch  = USBDM::GpioC<1,ActiveLow>;
using WestSwitch   = USBDM::GpioD<6,ActiveLow>;
using CentreSwitch = USBDM::GpioD<5,ActiveLow>;
using NorthSwitch  = USBDM::GpioB<1,ActiveLow>;

enum SwitchValue {
	noSwitch,    //!< No Switch or multiple switches pressed
	eastSwitch,  //!< East Switch
	southSwitch, //!< South Switch
	westSwitch,  //!< West Switch
	centreSwitch,//!< Centre Switch
	northSwitch, //!< North Switch
};

static const char *getSwitchName(SwitchValue switchValue) {
	static const char *switchNames[] = {
			"noSwitch",
			"eastSwitch",
			"southSwitch",
			"westSwitch",
			"centreSwitch",
			"northSwitch",
	};
	if (switchValue>=(sizeof(switchNames)/sizeof(switchNames[0]))) {
		return "Illegal switch value";
	}
	return switchNames[switchValue];
}

FormattedIO &operator<<(FormattedIO &io, SwitchValue &switchValue) {
	return io.write(getSwitchName(switchValue));
}

// Time between samples of the input
static constexpr float DEBOUNCE_SAMPLE_TIME = 5*ms;

// Number of debug samples for a stable input
static constexpr unsigned DEBOUNCE_SAMPLES = 5;

// Debounced switch value
static volatile SwitchValue switchValue = noSwitch;

using Timer        = Pit;
using TimerChannel = Pit::Channel<1>;

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

	//	console.writeln(currentSwitch);
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
			switchValue=noSwitch;
			break;
		case 16:
			console.writeln("eastSwitch");
			switchValue=eastSwitch;
			break;
		case 8:
			console.writeln("southSwitch");
			switchValue=southSwitch;
			N--;
			break;
		case 4:
			console.writeln("westSwitch");
			switchValue=westSwitch;
			break;
		case 2:
			console.writeln("cetreSwitch");
			switchValue=centreSwitch;
			power ~= power;
			break;
		case 1:
			console.writeln("northSwitch");
			switchValue=northSwitch;
			N++;
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

SwitchValue getJogswitch() {
	// Get safe copy of switch value and clear it
	TimerChannel::disableNvicInterrupts();

	SwitchValue saveSwitch = switchValue;
	switchValue = noSwitch;

	TimerChannel::enableNvicInterrupts();
	return saveSwitch;
}

int main0() {
	initJogSwitch();

	for(;;) {
		// Report switch presses
		SwitchValue currentSwitch = getJogswitch();
		if (currentSwitch != noSwitch) {
			console.write("Changed #").writeln(getSwitchName(currentSwitch));
		}
	}
}
