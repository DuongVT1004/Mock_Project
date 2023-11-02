################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../flash_processing/flash.c 

OBJS += \
./flash_processing/flash.o 

C_DEPS += \
./flash_processing/flash.d 


# Each subdirectory must supply rules for building sources it contributes
flash_processing/%.o: ../flash_processing/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@flash_processing/flash.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


