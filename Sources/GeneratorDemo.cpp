
#include "hardware.h"
#include "Generator.h"
#include "jog_switch_debounce.h"
#include "display_module.h"

using namespace USBDM;
using Gnd = GpioC<10,ActiveLow>;

int main() {

	console.writeln("\nStarting\n");

	unsigned frequencyList[20] = {5,5,5,10,20,50,100,200,500,1000,2000,5000,10000,20000,50000,100000,200000,500000,1000000,2000000};
	int current_index=0;
	bool output_on=0;

	Gnd::setOutput();
	Gnd::set();
	initJogSwitch();
	generatorInitialise();
	displayOff();
	outputOff();

	for(;;) {

		int currentSwitch = getJogswitch();
		if (currentSwitch == 2){
			output_on = !output_on;
			console.writeln(output_on);
			if(output_on==0){
				displayOff();
				outputOff();
			}
			else{
				displayClockkInfo(current_index);
				console.writeln(frequencyList[current_index]);
				generatorSetFrequency(frequencyList[current_index]);
			}
		}

		if (currentSwitch == 1 || currentSwitch == 8 && output_on==1 ) {

			if (currentSwitch == 1 && current_index<19 ) {
				current_index++;
			}
			if ( currentSwitch == 8 && current_index>0){
				current_index--;
			}
			displayClockkInfo(current_index);
			console.writeln(frequencyList[current_index]);
			generatorSetFrequency(frequencyList[current_index]);
		}
		//      unsigned frequency;
		//      console.write("Frequency[")
		//            .write(MIN_FREQUENCY)
		//            .write("..")
		//            .write(MAX_FREQUENCY).write("]")
		//            .readln(frequency);
		//      if ((frequency<MIN_FREQUENCY) || (frequency>MAX_FREQUENCY)) {
		//         console.writeln("Frequency out of range");
		//         continue;
		//      }
		//      console.writeln("frq set");


	}

	return 0;
}



