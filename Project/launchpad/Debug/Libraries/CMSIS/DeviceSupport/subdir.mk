################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/CMSIS/DeviceSupport/system_stm32f10x.c 

OBJS += \
./Libraries/CMSIS/DeviceSupport/system_stm32f10x.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/CMSIS/DeviceSupport/%.o: ../Libraries/CMSIS/DeviceSupport/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc -I"C:\Users\hw_9\Desktop\git_repository\Project\launchpad\Libraries" -I"C:\Users\hw_9\Desktop\git_repository\Project\launchpad\MPR121" -I"C:\Users\hw_9\Desktop\git_repository\Project\launchpad\Libraries\CMSIS\CoreSupport" -I"C:\Users\hw_9\Desktop\git_repository\Project\launchpad\Libraries\CMSIS\DeviceSupport" -I"C:\Users\hw_9\Desktop\git_repository\Project\launchpad\Libraries\CMSIS\DeviceSupport\Startup" -I"C:\Users\hw_9\Desktop\git_repository\Project\launchpad\Libraries\STM32F10x_StdPeriph_Driver_v3.5\inc" -I"C:\Users\hw_9\Desktop\git_repository\Project\launchpad\Libraries\STM32F10x_StdPeriph_Driver_v3.5\src" -O3 --cpu=cortex-m3 -g -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


