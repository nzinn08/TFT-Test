################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../rotary-encoder/generic-rotary-encoder.cpp \
../rotary-encoder/selection-encoder.cpp 

OBJS += \
./Src/rotary-encoder/generic-rotary-encoder.o \
./Src/rotary-encoder/selection-encoder.o 

CPP_DEPS += \
./Src/rotary-encoder/generic-rotary-encoder.d \
./Src/rotary-encoder/selection-encoder.d 


# Each subdirectory must supply rules for building sources it contributes
Src/rotary-encoder/generic-rotary-encoder.o: /home/nzinn/Documents/senior-mcu/TFT-Test/rotary-encoder/generic-rotary-encoder.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F072xB -DDEBUG -c -I../Inc -I../rotary-encoder -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../tft-display-code -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/rotary-encoder/generic-rotary-encoder.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/rotary-encoder/selection-encoder.o: /home/nzinn/Documents/senior-mcu/TFT-Test/rotary-encoder/selection-encoder.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F072xB -DDEBUG -c -I../Inc -I../rotary-encoder -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../tft-display-code -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/rotary-encoder/selection-encoder.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

