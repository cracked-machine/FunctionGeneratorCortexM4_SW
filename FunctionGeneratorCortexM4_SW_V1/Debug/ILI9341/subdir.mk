################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341/ILI9341_GFX.c \
/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341/ILI9341_STM32_Driver.c \
/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341/ILI9341_TextManager.c 

OBJS += \
./ILI9341/ILI9341_GFX.o \
./ILI9341/ILI9341_STM32_Driver.o \
./ILI9341/ILI9341_TextManager.o 

C_DEPS += \
./ILI9341/ILI9341_GFX.d \
./ILI9341/ILI9341_STM32_Driver.d \
./ILI9341/ILI9341_TextManager.d 


# Each subdirectory must supply rules for building sources it contributes
ILI9341/ILI9341_GFX.o: /home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341/ILI9341_GFX.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_ILI9341_SPIDMA -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/EventManager" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/DisplayManager" -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/SIgnalManager" -I../Core/Inc -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/WaveTableGeneration" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/LogSequenceGeneration" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ILI9341/ILI9341_GFX.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ILI9341/ILI9341_STM32_Driver.o: /home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341/ILI9341_STM32_Driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_ILI9341_SPIDMA -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/EventManager" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/DisplayManager" -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/SIgnalManager" -I../Core/Inc -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/WaveTableGeneration" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/LogSequenceGeneration" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ILI9341/ILI9341_STM32_Driver.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ILI9341/ILI9341_TextManager.o: /home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341/ILI9341_TextManager.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_ILI9341_SPIDMA -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/EventManager" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/DisplayManager" -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/SIgnalManager" -I../Core/Inc -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/WaveTableGeneration" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/LogSequenceGeneration" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ILI9341/ILI9341_TextManager.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

