/*
 * FtmDemo.cpp
 *
 *  Created on: 20 Sep 2019
 *      Author: podonoghue
 */
#include "hardware.h"
#include "Generator.h"

using namespace USBDM;
using Gnd = GpioC<10,ActiveLow>;

int main() {
   console.writeln("\nStarting\n");
   Gnd::setOutput();
   Gnd::set();
   generatorInitialise();


   for(;;) {
      unsigned frequency;
      console.write("Frequency[")
            .write(MIN_FREQUENCY)
            .write("..")
            .write(MAX_FREQUENCY).write("]")
            .readln(frequency);
      if ((frequency<MIN_FREQUENCY) || (frequency>MAX_FREQUENCY)) {
         console.writeln("Frequency out of range");
         continue;
      }
      console.writeln("frq set");
      generatorSetFrequency(frequency);
   }

   return 0;
}



