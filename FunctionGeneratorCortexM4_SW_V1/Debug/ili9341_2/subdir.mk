################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/stm32-ili9341-master/Lib/ili9341_2/fonts.c \
/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/stm32-ili9341-master/Lib/ili9341_2/ili9341.c \
/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/stm32-ili9341-master/Lib/ili9341_2/ili9341_touch.c 

OBJS += \
./ili9341_2/fonts.o \
./ili9341_2/ili9341.o \
./ili9341_2/ili9341_touch.o 

C_DEPS += \
./ili9341_2/fonts.d \
./ili9341_2/ili9341.d \
./ili9341_2/ili9341_touch.d 


# Each subdirectory must supply rules for building sources it contributes
ili9341_2/fonts.o: /home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/stm32-ili9341-master/Lib/ili9341_2/fonts.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_ILI9341_SPIDMA -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/DisplayManager" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/stm32-ili9341-master/Lib/ili9341_2" -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Core/Inc -I"/home/chris/Projects/Python/WaveTableGeneration" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ili9341_2/fonts.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ili9341_2/ili9341.o: /home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/stm32-ili9341-master/Lib/ili9341_2/ili9341.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_ILI9341_SPIDMA -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/DisplayManager" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/stm32-ili9341-master/Lib/ili9341_2" -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Core/Inc -I"/home/chris/Projects/Python/WaveTableGeneration" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ili9341_2/ili9341.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ili9341_2/ili9341_touch.o: /home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/stm32-ili9341-master/Lib/ili9341_2/ili9341_touch.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_ILI9341_SPIDMA -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/DisplayManager" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/stm32-ili9341-master/Lib/ili9341_2" -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Core/Inc -I"/home/chris/Projects/Python/WaveTableGeneration" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ili9341_2/ili9341_touch.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

