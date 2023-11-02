################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lpit/lpit.c 

OBJS += \
./lpit/lpit.o 

C_DEPS += \
./lpit/lpit.d 


# Each subdirectory must supply rules for building sources it contributes
lpit/%.o: ../lpit/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@lpit/lpit.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


