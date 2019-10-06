################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sources/Generator.cpp \
../Sources/GeneratorDemo.cpp \
../Sources/delay.cpp \
../Sources/display_module.cpp \
../Sources/fonts.cpp \
../Sources/ftfl.cpp \
../Sources/hardware.cpp \
../Sources/i2c.cpp \
../Sources/jog_switch_debounce.cpp \
../Sources/lcd.cpp \
../Sources/spi.cpp \
../Sources/usbdmError.cpp 

OBJS += \
./Sources/Generator.o \
./Sources/GeneratorDemo.o \
./Sources/delay.o \
./Sources/display_module.o \
./Sources/fonts.o \
./Sources/ftfl.o \
./Sources/hardware.o \
./Sources/i2c.o \
./Sources/jog_switch_debounce.o \
./Sources/lcd.o \
./Sources/spi.o \
./Sources/usbdmError.o 

CPP_DEPS += \
./Sources/Generator.d \
./Sources/GeneratorDemo.d \
./Sources/delay.d \
./Sources/display_module.d \
./Sources/fonts.d \
./Sources/ftfl.d \
./Sources/hardware.d \
./Sources/i2c.d \
./Sources/jog_switch_debounce.d \
./Sources/lcd.d \
./Sources/spi.d \
./Sources/usbdmError.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -g3 -O0 -ffunction-sections -fdata-sections -fno-rtti -Wall -Wextra -DDEBUG_BUILD -DLCD_AVAILABLE -I"C:/Users/Marjanur Rahman/Documents/workspace/tute_5_q3/Sources" -I"C:/Users/Marjanur Rahman/Documents/workspace/tute_5_q3/Project_Headers" -fno-exceptions -std=gnu++17 -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)"  -o "$@" $<
	@echo 'Finished building: $<'
	@echo ' '


