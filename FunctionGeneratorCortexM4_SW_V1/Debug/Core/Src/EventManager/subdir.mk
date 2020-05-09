################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/EventManager/EventManager.c 

OBJS += \
./Core/Src/EventManager/EventManager.o 

C_DEPS += \
./Core/Src/EventManager/EventManager.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/EventManager/EventManager.o: ../Core/Src/EventManager/EventManager.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_ILI9341_SPIDMA -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/SIgnalManager" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/DisplayManager" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/EventManager" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/WaveTableGeneration" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/LogSequenceGeneration" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/EventManager/EventManager.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

