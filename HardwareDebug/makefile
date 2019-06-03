################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include makefile.init

RM := rm -rf *.sni *.dbg *.lst *.lis *.lpp *.map *.x *.lbp *.h *.bls *.libelf *.rel *.lbk *.abs *.prn *.mi  *.obj *.jmp *.d *.i *.asm 1st/*.obj 1st/*.d 1st/*.asm 1st/*.abs 1st/*.i

# All of the sources participating in the build are defined here
-include sources.mk
-include generate/subdir.mk
-include src/subdir.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif 
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif 
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif 
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif 
ifneq ($(strip $(JMP_DEPS)),)
-include $(JMP_DEPS)
endif 
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif 
ifneq ($(strip $(PP_DEPS)),)
-include $(PP_DEPS)
endif 
ifneq ($(strip $(P_DEPS)),)
-include $(P_DEPS)
endif 
ifneq ($(strip $(FSY_DEPS)),)
-include $(FSY_DEPS)
endif 
endif

ifneq ($(strip $(SRC_UPPER_SRCS)),)
ALL_ASMS += $(SRC_UPPER_SRCS) 
endif
ifneq ($(strip $(SRC_SRCS)),)
ALL_ASMS += $(SRC_SRCS) 
endif
ifneq ($(strip $(S_UPPER_SRCS)),)
ALL_ASMS += $(S_UPPER_SRCS) 
endif
ifneq ($(strip $(S_SRCS)),)
ALL_ASMS += $(S_SRCS) 
endif


-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables
LINKER_OUTPUT_OUTPUTS += \
Static_Kit.abs

CONVERTOR_OUTPUT_OUTPUTS += \
Static_Kit.hex

OBJS := \
$(COMPILER_OBJS) \
$(INDIVIDUAL_COMPILER_OBJS) \
$(ASSEMBLER_OBJS) \
$(CUSTOM_OBJS)

# All Target
all: $(CONVERTOR_OUTPUT_OUTPUTS) Static_Kit.x
	@echo 'Build complete.'

Static_Kit.hex: $(LINKER_OUTPUT_OUTPUTS) 
	@echo 'Invoking: Converter'
	@echo 'Building target:'
	@echo ConverterStatic_Kit.tmp=
	@sed -e "s/^/    /" "ConverterStatic_Kit.tmp"
	rlink   "Static_Kit.abs" -subcommand="ConverterStatic_Kit.tmp"
	@echo 'Finished building target:'
	@echo.


Static_Kit.abs: $(OBJS)  $(ALL_ASMS)  \
C:\Users\500022\Documents\Intern\RL78\E2\ Studio\EEL\FDL\lib\fdl.lib  \
C:\Users\500022\Documents\Intern\RL78\E2\ Studio\EEL\EEL\lib\eel.lib
	@echo 'Invoking: Linker'
	@echo LinkerStatic_Kit.tmp=
	@sed -e "s/^/    /" "LinkerStatic_Kit.tmp"
	rlink -subcommand="LinkerStatic_Kit.tmp"
	@echo 'Finished building:'
	@echo.


Static_Kit.x: Static_Kit.abs
		-C:\Renesas\e2_studio\Utilities\\ccrl\renesas_cc_converter.exe Static_Kit.abs Static_Kit.x

# Other Targets
clean:
	-$(RM) $(LINKER_OUTPUT_OUTPUTS) $(CONVERTOR_OUTPUT_OUTPUTS)
	-rm -rf generate/*.obj generate/*.d generate/*.asm generate/*.p generate/*.src generate/*.jmp generate/*.lst generate/*.prn generate/*.i 
	-rm -rf src/*.obj src/*.d src/*.asm src/*.p src/*.src src/*.jmp src/*.lst src/*.prn src/*.i 
	@echo
	@echo 'Clean complete.'

.PHONY: all clean 
-include ../makefile.targets