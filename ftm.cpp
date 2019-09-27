#include "hardware.h"
#include "header.h"
#include "smc.h"

using namespace USBDM;

using Timer = Ftm0;

using TimerChannel = Timer::Channel<7>;

static volatile uint16_t timerHalfPeriodInTicks;

static constexpr float WAVEFORM_PERIOD = 100*ms;

/// Maximum OC interval - the OC interval should not exceed this value.
static constexpr float MAX_OC_INTERVAL = (1.1 * WAVEFORM_PERIOD)/2;

static void ftmCallback(uint8_t status) {

   // Check channel
   if (status & TimerChannel::CHANNEL_MASK) {
      // Note: The pin is toggled directly by hardware
      // Re-trigger at last interrupt time + timerHalfPeriodInTicks
      TimerChannel::setDeltaEventTime(timerHalfPeriodInTicks);
   }
}

void generatorInitialise()
{
   // Configure base FTM (affects all channels)
   Timer::configure(
         FtmMode_LeftAlign,       // Left-aligned is required for OC/IC
         FtmClockSource_System);  // Bus clock usually

   // Set IC/OC measurement interval to longest interval needed.
   // This adjusts the prescaler value but does not change the clock source
   Timer::setMaximumInterval(0.6/MIN_FREQUENCY);

   // Calculate half-period in timer ticks
   // Must be done after timer clock configuration (above)
  generatorSetFrequency(MIN_FREQUENCY)
   // Enable interrupts for entire timer
   Timer::enableNvicInterrupts(NvicPriority_Normal);

   // Configure pin associated with channel
   TimerChannel::setOutput(
         PinDriveStrength_High,
         PinDriveMode_PushPull,
         PinSlewRate_Slow);

   // Trigger 1st interrupt at now+100
   TimerChannel::setRelativeEventTime(100);

   // Set callback function (may be shared by multiple channels)
   TimerChannel::setChannelCallback(ftmCallback);

   // Configure the channel
   TimerChannel::configure(
         FtmChMode_OutputCompareToggle, //  Output Compare with pin toggle
         FtmChannelAction_Irq);         //  + interrupts on events

   // Check if configuration failed
   USBDM::checkError();
}
void generatorSetFrequency(unsigned frequency)
{
	timerHalfPeriodInTicks = Timer::convertSecondsToTicks(0.5/frequency);
}
