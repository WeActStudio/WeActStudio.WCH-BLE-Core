################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ble/app/broadcaster.c 

OBJS += \
./ble/app/broadcaster.o 

C_DEPS += \
./ble/app/broadcaster.d 


# Each subdirectory must supply rules for building sources it contributes
ble/app/%.o: ../ble/app/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused  -g -DDEBUG=1 -DHAL_KEY=TRUE -DHAL_LED=TRUE -DHAL_SLEEP=TRUE -DCLK_OSC32K=0 -I"F:\WeActStudio1\Products\WeAct-CH57xCoreBoard\Software\CH573\ble\broadcaster\StdPeriphDriver\inc" -I"F:\WeActStudio1\Products\WeAct-CH57xCoreBoard\Software\CH573\ble\broadcaster\RVMSIS" -I"F:\WeActStudio1\Products\WeAct-CH57xCoreBoard\Software\CH573\ble\broadcaster\ble\lib" -I"F:\WeActStudio1\Products\WeAct-CH57xCoreBoard\Software\CH573\ble\broadcaster\ble\profile" -I"F:\WeActStudio1\Products\WeAct-CH57xCoreBoard\Software\CH573\ble\broadcaster\ble\hal" -I"F:\WeActStudio1\Products\WeAct-CH57xCoreBoard\Software\CH573\ble\broadcaster\ble\app" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

