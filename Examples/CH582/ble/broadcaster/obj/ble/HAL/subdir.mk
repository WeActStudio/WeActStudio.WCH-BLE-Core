################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ble/HAL/KEY.c \
../ble/HAL/LED.c \
../ble/HAL/MCU.c \
../ble/HAL/RTC.c \
../ble/HAL/SLEEP.c 

OBJS += \
./ble/HAL/KEY.o \
./ble/HAL/LED.o \
./ble/HAL/MCU.o \
./ble/HAL/RTC.o \
./ble/HAL/SLEEP.o 

C_DEPS += \
./ble/HAL/KEY.d \
./ble/HAL/LED.d \
./ble/HAL/MCU.d \
./ble/HAL/RTC.d \
./ble/HAL/SLEEP.d 


# Each subdirectory must supply rules for building sources it contributes
ble/HAL/%.o: ../ble/HAL/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DDEBUG=1 -DHAL_KEY=TRUE -DHAL_LED=TRUE -DHAL_SLEEP=TRUE -DCLK_OSC32K=0 -I"../StdPeriphDriver/inc" -I"../RVMSIS" -I../ble/LIB -I../ble/HAL/include -I../ble/Profile/include -I../ble/APP/include -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

