################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include StdPeriphDriver/subdir.mk
-include Startup/subdir.mk
-include RVMSIS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
flash_test.hex \

SECONDARY_LIST += \
flash_test.lst \

SECONDARY_SIZE += \
flash_test.siz \


# All Target
all: flash_test.elf secondary-outputs

# Tool invocations
flash_test.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused  -g -T "F:\WeActStudio1\Products\WeAct-CH57xCoreBoard\Software\flash_test\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -L"F:\WeActStudio1\Products\WeAct-CH57xCoreBoard\Software\flash_test\StdPeriphDriver" -Xlinker --print-memory-usage -Wl,-Map,"flash_test.map" --specs=nano.specs --specs=nosys.specs -o "flash_test.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
flash_test.hex: flash_test.elf
	@	riscv-none-embed-objcopy -O ihex "flash_test.elf"  "flash_test.hex"
	@	@
flash_test.lst: flash_test.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "flash_test.elf" > "flash_test.lst"
	@	@
flash_test.siz: flash_test.elf
	@	riscv-none-embed-size --format=berkeley "flash_test.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) flash_test.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
