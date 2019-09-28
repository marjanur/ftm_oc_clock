/**
 * @file spi.cpp  (180.ARM_Peripherals/Sources/spi-MK.cpp)
 *
 * @version  V4.12.1.210
 * @date     13 April 2016
 */
#include <stddef.h>
#include <stdint.h>
#include "system.h"
#include "derivative.h"
#include "utilities.h"
#include "hardware.h"
#include "spi.h"
/*
 * *****************************
 * *** DO NOT EDIT THIS FILE ***
 * *****************************
 *
 * This file is generated automatically.
 * Any manual changes will be lost.
 */
namespace USBDM {

static const uint16_t pbrFactors[] {2,3,5,7};
static const uint16_t brFactors[] {2,4,6,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};

/**
 * Calculate communication speed factors for SPI
 *
 * @param[in]  clockFrequency => Clock frequency of SPI in Hz
 * @param[in]  frequency      => Communication frequency in Hz
 *
 * @return CTAR register value only including SPI_CTAR_BR, SPI_CTAR_PBR fields
 *
 * Note: Chooses the highest speed that is not greater than frequency.
 */
uint32_t Spi::calculateDividers(uint32_t clockFrequency, uint32_t frequency) {

   if (clockFrequency <= (2*frequency)) {
      // Use highest possible rate
      return SPI_CTAR_DBR_MASK;
   }
   int bestPBR = 3;
   int bestBR  = 7;
   int32_t bestDifference = 0x7FFFFFFF;
   for (int pbr = 3; pbr >= 0; pbr--) {
      for (int br = 15; br >= 0; br--) {
         uint32_t calculatedFrequency = clockFrequency/(pbrFactors[pbr]*brFactors[br]);
         int32_t difference = frequency-calculatedFrequency;
         if (difference < 0) {
            // Too high stop looking here
            break;
         }
         if (difference < bestDifference) {
            // New "best value"
            bestDifference = difference;
            bestBR  = br;
            bestPBR = pbr;
         }
      }
   }
   uint32_t clockFactors = SPI_CTAR_BR(bestBR)|SPI_CTAR_PBR(bestPBR);
   if ((clockFactors == 0) && (clockFrequency<=(2*frequency))) {
      // Use highest possible rate
      clockFactors = SPI_CTAR_DBR_MASK;
   }
   return clockFactors;
}

/**
 * Calculates speed from SPI clock frequency and SPI clock factors
 *
 * @param[in] clockFrequency   SPI input clock frequency
 * @param[in] clockFactors     SPI clock factors
 *
 * @return SPI frequency
 */
uint32_t Spi::calculateSpeed(uint32_t clockFrequency, uint32_t clockFactors) {
   int pbr = (clockFactors&SPI_CTAR_PBR_MASK)>>SPI_CTAR_PBR_SHIFT;
   int br  = (clockFactors&SPI_CTAR_BR_MASK)>>SPI_CTAR_BR_SHIFT;
   uint32_t frequency = clockFrequency/(pbrFactors[pbr]*brFactors[br]);
   if (clockFactors&SPI_CTAR_DBR_MASK) {
      frequency *= 2;
   }
   return frequency;
}

/**
 * Calculate Delay factors
 * Used for ASC, DT and CSSCK
 *
 * @param[in]  delay          => Desired delay in seconds
 * @param[in]  clockFrequency => Clock frequency of SPI in Hz
 * @param[out] bestPrescale   => Best prescaler value (0=>/1, 1=>/3, 2=/5, 3=>/7)
 * @param[out] bestDivider    => Best divider value (N=>/(2**(N+1)))
 *
 * Note: Determines bestPrescaler and bestDivider for the smallest delay that is not less than delay.
 */
void Spi::calculateDelay(float clockFrequency, float delay, int &bestPrescale, int &bestDivider) {
   const float clockPeriod = (1/clockFrequency);
   float bestDifference = MAXFLOAT;

   bestPrescale = 0;
   bestDivider  = 0;
   for (int prescale = 3; prescale >= 0; prescale--) {
      for (int divider = 15; divider >= 0; divider--) {
         float calculatedDelay = clockPeriod*((prescale<<1)+1)*(1UL<<(divider+1));
         float difference = calculatedDelay - delay;
         if (difference < 0) {
            // Too short - stop looking here
            break;
         }
         if (difference < bestDifference) {
            // New "best delay"
            bestDifference = difference;
            bestPrescale = prescale;
            bestDivider  = divider;
         }
      }
   }
}

/**
 * Transmit and receive a value over SPI
 *
 * @param[in] data - Data to send (4-16 bits) <br>
 *                   May include other control bits
 *
 * @return Data received
 */
uint32_t Spi::txRx(uint16_t data) {
   spi->PUSHR = data|pushrMask;
   while ((spi->SR & SPI_SR_TCF_MASK)==0) {
   }
   spi->SR = SPI_SR_TCF_MASK|SPI_SR_EOQF_MASK;
   return spi->POPR;  // Return read data
}

} // End namespace USBDM
