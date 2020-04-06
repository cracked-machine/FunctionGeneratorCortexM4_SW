################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341/ILI9341_GFX.c \
/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341/ILI9341_STM32_Driver.c 

OBJS += \
./ILI9341/ILI9341_GFX.o \
./ILI9341/ILI9341_STM32_Driver.o 

C_DEPS += \
./ILI9341/ILI9341_GFX.d \
./ILI9341/ILI9341_STM32_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
ILI9341/ILI9341_GFX.o: /home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341/ILI9341_GFX.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DDEBUG -c -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Core/Inc -I"/home/chris/Projects/Python/WaveTableGeneration" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ILI9341/ILI9341_GFX.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ILI9341/ILI9341_STM32_Driver.o: /home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341/ILI9341_STM32_Driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DDEBUG -c -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Core/Inc -I"/home/chris/Projects/Python/WaveTableGeneration" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ILI9341/ILI9341_STM32_Driver.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

