/**
 ============================================================================
 * @file    ftm-oc-example.cpp (180.ARM_Peripherals/Snippets)
 * @brief   Demo using Ftm class to implement a basic Output Compare system
 *
 *  An FTM output generates a square wave with 100ms period
 *
 *  Created on: 3/7/2017
 *      Author: podonoghue
 ============================================================================
 */
#include "hardware.h"
#include "smc.h"
#include "Generator.h"

using namespace USBDM;



/**
 * This example uses FTM interrupts.
 *
 * It is necessary to enable these in Configure.usbdmProject
 * under the "Peripheral Parameters"->FTM tab.
 * Select irqHandlingMethod option (Class Method - Software ...)
 */

/**
 * Timer being used - change as required
 * Could also access as TimerChannel::Ftm
 */
using Timer = Ftm1;

/// Timer channel for output - change as required
using TimerChannel = Timer::Channel<1>;

/**
 * Half-period for timer in ticks.
 * This variable is shared with the interrupt routine
 */
static volatile uint16_t timerHalfPeriodInTicks;

/**
 * Interrupt handler for Timer interrupts
 * This sets the next interrupt/pin toggle for a half-period from the last event
 *
 * @param[in] status Flags indicating interrupt source channel(s)
 */
static void ftmCallback(uint8_t status) {

	// Check channel
	if (status & TimerChannel::CHANNEL_MASK) {
		// Note: The pin is toggled directly by hardware
		// Re-trigger at last interrupt time + timerHalfPeriodInTicks
		TimerChannel::setDeltaEventTime(timerHalfPeriodInTicks);
	}
}

/**
 * Demonstration main-line
 *
 * @return Not used.
 */
void outputOff(){
	TimerChannel::disable(); // turning off output by turning off the channel
}


void generatorInitialise() {
	/**
	 * FTM channel set as Output compare with pin Toggle mode and using a callback function
	 */
	// Configure base FTM (affects all channels)
	Timer::configure(
			FtmMode_LeftAlign,       // Left-aligned is required for OC/IC
			FtmClockSource_System);  // Bus clock usually

	// Set IC/OC measurement interval to longest interval needed.
	// This adjusts the prescaler value but does not change the clock source

	//	Timer::setMaximumInterval(1.1*0.5/MIN_FREQUENCY);
	// Calculate half-period in timer ticks
	// Must be done after timer clock configuration (above)
	generatorSetFrequency(MIN_FREQUENCY);

	// Enable interrupts for entire timer
	Timer::enableNvicInterrupts(NvicPriority_Normal);

	// Configure pin associated with channel
	TimerChannel::setOutput(
			PinDriveStrength_High,
			PinDriveMode_PushPull,
			PinSlewRate_Fast);

	// Trigger 1st interrupt at now+100
	TimerChannel::setRelativeEventTime(100);

	// Set callback function (may be shared by multiple channels)
	TimerChannel::setChannelCallback(ftmCallback);

	// Configure the channel
	TimerChannel::configure(
			FtmChMode_OutputCompareToggle, //  Output Compare with pin toggle
			FtmChannelAction_None);         //  + interrupts on events

	// Check if configuration failed
	USBDM::checkError();

}

/**
 * Set generator Frequency
 *
 * @param frequency [MIN_FREQUENCY ... MAX_FREQUENCY]
 */
void generatorSetFrequency(unsigned frequency) {
	if (frequency>4) {
		TimerChannel::configure(
				FtmChMode_OutputCompareToggle,
				FtmChannelAction_None);
		Timer::setPeriod(0.5/frequency, true);
	}
	//	else{

	//		TimerChannel::configure(
	//							FtmChMode_OutputCompareToggle,
	//						FtmChannelAction_Irq);
	//		timerHalfPeriodInTicks = Timer::convertSecondsToTicks(0.5/frequency);
	//	}


}
