################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../init/config_exti.c \
../init/config_nvic.c \
../init/config_system.c 

OBJS += \
./init/config_exti.o \
./init/config_nvic.o \
./init/config_system.o 


# Each subdirectory must supply rules for building sources it contributes
init/%.o: ../init/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc -I"C:\Users\hw_5\Desktop\git_repository\Project\launchpad\Libraries" -I"C:\Users\hw_5\Desktop\git_repository\Project\launchpad\MPR121" -I"C:\Users\hw_5\Desktop\git_repository\Project\launchpad\Libraries\CMSIS\CoreSupport" -I"C:\Users\hw_5\Desktop\git_repository\Project\launchpad\Libraries\CMSIS\DeviceSupport" -I"C:\Users\hw_5\Desktop\git_repository\Project\launchpad\Libraries\CMSIS\DeviceSupport\Startup" -I"C:\Users\hw_5\Desktop\git_repository\Project\launchpad\Libraries\STM32F10x_StdPeriph_Driver_v3.5\inc" -I"C:\Users\hw_5\Desktop\git_repository\Project\launchpad\Libraries\STM32F10x_StdPeriph_Driver_v3.5\src" -O3 --cpu=cortex-m3 -g -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


