################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../KiwiDriverV2/KiwiAccel.cpp 

OBJS += \
./KiwiDriverV2/KiwiAccel.o 

CPP_DEPS += \
./KiwiDriverV2/KiwiAccel.d 


# Each subdirectory must supply rules for building sources it contributes
KiwiDriverV2/%.o: ../KiwiDriverV2/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


