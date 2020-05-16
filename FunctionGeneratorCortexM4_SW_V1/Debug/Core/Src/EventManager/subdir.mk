################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/EventManager/BiasMenuStateHandler.c \
../Core/Src/EventManager/EventManager.c \
../Core/Src/EventManager/FreqMenuStateHandler.c \
../Core/Src/EventManager/FuncMenuStateHandler.c \
../Core/Src/EventManager/GainMenuStateHandler.c 

OBJS += \
./Core/Src/EventManager/BiasMenuStateHandler.o \
./Core/Src/EventManager/EventManager.o \
./Core/Src/EventManager/FreqMenuStateHandler.o \
./Core/Src/EventManager/FuncMenuStateHandler.o \
./Core/Src/EventManager/GainMenuStateHandler.o 

C_DEPS += \
./Core/Src/EventManager/BiasMenuStateHandler.d \
./Core/Src/EventManager/EventManager.d \
./Core/Src/EventManager/FreqMenuStateHandler.d \
./Core/Src/EventManager/FuncMenuStateHandler.d \
./Core/Src/EventManager/GainMenuStateHandler.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/EventManager/BiasMenuStateHandler.o: ../Core/Src/EventManager/BiasMenuStateHandler.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_ILI9341_SPIDMA -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/EventManager" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/LogSequenceGeneration" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/InterruptManager" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341" -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/DisplayManager" -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/SIgnalManager" -I../Core/Inc -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/WaveTableGeneration" -I../Drivers/STM32G4xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/EventManager/BiasMenuStateHandler.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/EventManager/EventManager.o: ../Core/Src/EventManager/EventManager.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_ILI9341_SPIDMA -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/EventManager" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/LogSequenceGeneration" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/InterruptManager" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341" -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/DisplayManager" -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/SIgnalManager" -I../Core/Inc -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/WaveTableGeneration" -I../Drivers/STM32G4xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/EventManager/EventManager.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/EventManager/FreqMenuStateHandler.o: ../Core/Src/EventManager/FreqMenuStateHandler.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_ILI9341_SPIDMA -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/EventManager" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/LogSequenceGeneration" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/InterruptManager" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341" -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/DisplayManager" -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/SIgnalManager" -I../Core/Inc -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/WaveTableGeneration" -I../Drivers/STM32G4xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/EventManager/FreqMenuStateHandler.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/EventManager/FuncMenuStateHandler.o: ../Core/Src/EventManager/FuncMenuStateHandler.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_ILI9341_SPIDMA -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/EventManager" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/LogSequenceGeneration" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/InterruptManager" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341" -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/DisplayManager" -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/SIgnalManager" -I../Core/Inc -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/WaveTableGeneration" -I../Drivers/STM32G4xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/EventManager/FuncMenuStateHandler.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/EventManager/GainMenuStateHandler.o: ../Core/Src/EventManager/GainMenuStateHandler.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_ILI9341_SPIDMA -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/EventManager" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/LogSequenceGeneration" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/InterruptManager" -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/ILI9341" -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/DisplayManager" -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/Core/Src/SIgnalManager" -I../Core/Inc -I"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/WaveTableGeneration" -I../Drivers/STM32G4xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/EventManager/GainMenuStateHandler.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

