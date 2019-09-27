#include "hardware.h"
#include "header.h"
#ifndef SOURCES_GENERATOR_H_
#define SOURCES_GENERATOR_H_

using namespace USBDM;

static constexpr unsigned MIN_FREQUENCY = 100;
static constexpr unsigned MAX_FREQUENCY = 1000000;
/**
 * Initialise the generator before first use
 */
void generatorInitialise();
/**
 * Set generator Frequency
 *
 * @param frequency [MIN_FREQUENCY ... MAX_FREQUENCY]
 */
void generatorSetFrequency(unsigned frequency);
#endif /* SOURCES_GENERATOR_H_ */

int main(){
	for(;;)
	{
		int N = 0;      //table driven frequency control
		bool power = 0; //lcd on/off control
		main0();
		main1();
	}
return 0;
}