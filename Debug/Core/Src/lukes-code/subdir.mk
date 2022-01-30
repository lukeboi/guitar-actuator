################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/lukes-code/config.c \
../Core/Src/lukes-code/led.c \
../Core/Src/lukes-code/midi.c \
../Core/Src/lukes-code/strummer.c 

OBJS += \
./Core/Src/lukes-code/config.o \
./Core/Src/lukes-code/led.o \
./Core/Src/lukes-code/midi.o \
./Core/Src/lukes-code/strummer.o 

C_DEPS += \
./Core/Src/lukes-code/config.d \
./Core/Src/lukes-code/led.d \
./Core/Src/lukes-code/midi.d \
./Core/Src/lukes-code/strummer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/lukes-code/config.o: ../Core/Src/lukes-code/config.c Core/Src/lukes-code/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x6 -DDEBUG -c -I"C:/Users/Luke Farritor/Documents/GitHub/guitar-actuator/Drivers/STM32F0xx_HAL_Driver/Inc" -I"C:/Users/Luke Farritor/Documents/GitHub/guitar-actuator/Drivers/CMSIS/Include" -I"C:/Users/Luke Farritor/Documents/GitHub/guitar-actuator/Core/Inc" -I"C:/Users/Luke Farritor/Documents/GitHub/guitar-actuator/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Luke Farritor/Documents/GitHub/guitar-actuator/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -Wextra -pedantic -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wconversion -fstack-usage -MMD -MP -MF"Core/Src/lukes-code/config.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/lukes-code/led.o: ../Core/Src/lukes-code/led.c Core/Src/lukes-code/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x6 -DDEBUG -c -I"C:/Users/Luke Farritor/Documents/GitHub/guitar-actuator/Drivers/STM32F0xx_HAL_Driver/Inc" -I"C:/Users/Luke Farritor/Documents/GitHub/guitar-actuator/Drivers/CMSIS/Include" -I"C:/Users/Luke Farritor/Documents/GitHub/guitar-actuator/Core/Inc" -I"C:/Users/Luke Farritor/Documents/GitHub/guitar-actuator/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Luke Farritor/Documents/GitHub/guitar-actuator/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -Wextra -pedantic -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wconversion -fstack-usage -MMD -MP -MF"Core/Src/lukes-code/led.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/lukes-code/midi.o: ../Core/Src/lukes-code/midi.c Core/Src/lukes-code/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x6 -DDEBUG -c -I"C:/Users/Luke Farritor/Documents/GitHub/guitar-actuator/Drivers/STM32F0xx_HAL_Driver/Inc" -I"C:/Users/Luke Farritor/Documents/GitHub/guitar-actuator/Drivers/CMSIS/Include" -I"C:/Users/Luke Farritor/Documents/GitHub/guitar-actuator/Core/Inc" -I"C:/Users/Luke Farritor/Documents/GitHub/guitar-actuator/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Luke Farritor/Documents/GitHub/guitar-actuator/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -Wextra -pedantic -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wconversion -fstack-usage -MMD -MP -MF"Core/Src/lukes-code/midi.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/lukes-code/strummer.o: ../Core/Src/lukes-code/strummer.c Core/Src/lukes-code/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x6 -DDEBUG -c -I"C:/Users/Luke Farritor/Documents/GitHub/guitar-actuator/Drivers/STM32F0xx_HAL_Driver/Inc" -I"C:/Users/Luke Farritor/Documents/GitHub/guitar-actuator/Drivers/CMSIS/Include" -I"C:/Users/Luke Farritor/Documents/GitHub/guitar-actuator/Core/Inc" -I"C:/Users/Luke Farritor/Documents/GitHub/guitar-actuator/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Luke Farritor/Documents/GitHub/guitar-actuator/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -Wextra -pedantic -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wconversion -fstack-usage -MMD -MP -MF"Core/Src/lukes-code/strummer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

