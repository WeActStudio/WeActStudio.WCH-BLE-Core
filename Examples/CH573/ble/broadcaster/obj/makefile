################################################################################
# 自动生成的文件。不要编辑！
################################################################################

SRC_DIR := "$(PWD)/"
CFLAGS := -I"$(SRC_DIR)StdPeriphDriver/inc" -I"$(SRC_DIR)RVMSIS" -I"$(SRC_DIR)ble/lib" -I"$(SRC_DIR)ble/profile" -I"$(SRC_DIR)ble/hal" -I"$(SRC_DIR)ble/app"
LDFLAGS := -L"$(SRC_DIR)StdPeriphDriver" -L"$(SRC_DIR)ble/lib"

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include ble/profile/subdir.mk
-include ble/hal/subdir.mk
-include ble/app/subdir.mk
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
broadcaster.hex \

SECONDARY_LIST += \
broadcaster.lst \

SECONDARY_SIZE += \
broadcaster.siz \


# 所有目标
all: broadcaster.elf secondary-outputs

# 工具调用
broadcaster.elf: $(OBJS) $(USER_OBJS)
	@ echo CFLAGS: $(CFLAGS)
	@ echo LDFLAGS: $(LDFLAGS)
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused  -g -T "$(SRC_DIR)Ld/Link.ld" -nostartfiles -Xlinker --gc-sections $(LDFLAGS) -Xlinker --print-memory-usage -Wl,-Map,"broadcaster.map" --specs=nano.specs --specs=nosys.specs -o "broadcaster.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
broadcaster.hex: broadcaster.elf
	@	riscv-none-embed-objcopy -O ihex "broadcaster.elf"  "broadcaster.hex"
	@	@
broadcaster.lst: broadcaster.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "broadcaster.elf" > "broadcaster.lst"
	@	@
broadcaster.siz: broadcaster.elf
	@	riscv-none-embed-size --format=berkeley "broadcaster.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) broadcaster.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
