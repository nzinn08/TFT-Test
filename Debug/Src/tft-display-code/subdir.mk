################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tft-display-code/hspi.c \
../tft-display-code/tft-board-specific.c 

CPP_SRCS += \
../tft-display-code/gfx.cpp 

OBJS += \
./Src/tft-display-code/gfx.o \
./Src/tft-display-code/hspi.o \
./Src/tft-display-code/tft-board-specific.o 

C_DEPS += \
./Src/tft-display-code/hspi.d \
./Src/tft-display-code/tft-board-specific.d 

CPP_DEPS += \
./Src/tft-display-code/gfx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/tft-display-code/gfx.o: /home/nzinn/STM32CubeIDE/workspace_1.0.1/TFT_Test/tft-display-code/gfx.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F072xB -DDEBUG -c -I../Inc -I../tft-display-code -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/tft-display-code/gfx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/tft-display-code/hspi.o: /home/nzinn/STM32CubeIDE/workspace_1.0.1/TFT_Test/tft-display-code/hspi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F072xB -DDEBUG -c -I../Inc -I../tft-display-code -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/tft-display-code/hspi.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/tft-display-code/tft-board-specific.o: /home/nzinn/STM32CubeIDE/workspace_1.0.1/TFT_Test/tft-display-code/tft-board-specific.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F072xB -DDEBUG -c -I../Inc -I../tft-display-code -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/tft-display-code/tft-board-specific.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

