################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ble/Profile/devinfoservice.c 

OBJS += \
./ble/Profile/devinfoservice.o 

C_DEPS += \
./ble/Profile/devinfoservice.d 


# Each subdirectory must supply rules for building sources it contributes
ble/Profile/%.o: ../ble/Profile/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DDEBUG=1 -DHAL_KEY=TRUE -DHAL_LED=TRUE -DHAL_SLEEP=TRUE -DCLK_OSC32K=0 -I"../StdPeriphDriver/inc" -I"../RVMSIS" -I../ble/LIB -I../ble/HAL/include -I../ble/Profile/include -I../ble/APP/include -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

