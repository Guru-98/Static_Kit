################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../generate/cstart.asm \
../generate/stkinit.asm 

OBJS += \
./generate/cstart.o \
./generate/stkinit.o 

ASM_DEPS += \
./generate/cstart.d \
./generate/stkinit.d 


# Each subdirectory must supply rules for building sources it contributes
generate/%.o: ../generate/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking Assembler'
	$(file > $@.in,-O0 -fdata-sections -g2 -x assembler-with-cpp -Wa,--gdwarf2 -I"C:/Users/500022/Documents/Intern/RL78/workspace/Static_Kit/src" -Wa,-adlhn="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c "$<" -o "$@")
	rl78-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '


