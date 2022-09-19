################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ble/hal/KEY.c \
../ble/hal/LED.c \
../ble/hal/MCU.c \
../ble/hal/RTC.c \
../ble/hal/SLEEP.c 

OBJS += \
./ble/hal/KEY.o \
./ble/hal/LED.o \
./ble/hal/MCU.o \
./ble/hal/RTC.o \
./ble/hal/SLEEP.o 

C_DEPS += \
./ble/hal/KEY.d \
./ble/hal/LED.d \
./ble/hal/MCU.d \
./ble/hal/RTC.d \
./ble/hal/SLEEP.d 


# Each subdirectory must supply rules for building sources it contributes
ble/hal/%.o: ../ble/hal/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused  -g -DDEBUG=1 -DHAL_KEY=TRUE -DHAL_LED=TRUE -DHAL_SLEEP=TRUE -DCLK_OSC32K=0 -I"F:\WeActStudio1\Products\WeAct-CH57xCoreBoard\Datalink\Examples\CH573\ble\broadcaster\StdPeriphDriver\inc" -I"F:\WeActStudio1\Products\WeAct-CH57xCoreBoard\Datalink\Examples\CH573\ble\broadcaster\RVMSIS" -I"F:\WeActStudio1\Products\WeAct-CH57xCoreBoard\Datalink\Examples\CH573\ble\broadcaster\ble\lib" -I"F:\WeActStudio1\Products\WeAct-CH57xCoreBoard\Datalink\Examples\CH573\ble\broadcaster\ble\profile" -I"F:\WeActStudio1\Products\WeAct-CH57xCoreBoard\Datalink\Examples\CH573\ble\broadcaster\ble\hal" -I"F:\WeActStudio1\Products\WeAct-CH57xCoreBoard\Datalink\Examples\CH573\ble\broadcaster\ble\app" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

