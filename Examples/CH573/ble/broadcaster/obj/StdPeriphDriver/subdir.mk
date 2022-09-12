################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../StdPeriphDriver/CH57x_adc.c \
../StdPeriphDriver/CH57x_clk.c \
../StdPeriphDriver/CH57x_flash.c \
../StdPeriphDriver/CH57x_gpio.c \
../StdPeriphDriver/CH57x_pwr.c \
../StdPeriphDriver/CH57x_sys.c \
../StdPeriphDriver/CH57x_uart0.c \
../StdPeriphDriver/CH57x_uart1.c 

OBJS += \
./StdPeriphDriver/CH57x_adc.o \
./StdPeriphDriver/CH57x_clk.o \
./StdPeriphDriver/CH57x_flash.o \
./StdPeriphDriver/CH57x_gpio.o \
./StdPeriphDriver/CH57x_pwr.o \
./StdPeriphDriver/CH57x_sys.o \
./StdPeriphDriver/CH57x_uart0.o \
./StdPeriphDriver/CH57x_uart1.o 

C_DEPS += \
./StdPeriphDriver/CH57x_adc.d \
./StdPeriphDriver/CH57x_clk.d \
./StdPeriphDriver/CH57x_flash.d \
./StdPeriphDriver/CH57x_gpio.d \
./StdPeriphDriver/CH57x_pwr.d \
./StdPeriphDriver/CH57x_sys.d \
./StdPeriphDriver/CH57x_uart0.d \
./StdPeriphDriver/CH57x_uart1.d 


# Each subdirectory must supply rules for building sources it contributes
StdPeriphDriver/%.o: ../StdPeriphDriver/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused  -g -DDEBUG=1 -DHAL_KEY=TRUE -DHAL_LED=TRUE -DHAL_SLEEP=TRUE -DCLK_OSC32K=0 -I"F:\WeActStudio1\Products\WeAct-CH57xCoreBoard\Software\CH573\ble\broadcaster\StdPeriphDriver\inc" -I"F:\WeActStudio1\Products\WeAct-CH57xCoreBoard\Software\CH573\ble\broadcaster\RVMSIS" -I"F:\WeActStudio1\Products\WeAct-CH57xCoreBoard\Software\CH573\ble\broadcaster\ble\lib" -I"F:\WeActStudio1\Products\WeAct-CH57xCoreBoard\Software\CH573\ble\broadcaster\ble\profile" -I"F:\WeActStudio1\Products\WeAct-CH57xCoreBoard\Software\CH573\ble\broadcaster\ble\hal" -I"F:\WeActStudio1\Products\WeAct-CH57xCoreBoard\Software\CH573\ble\broadcaster\ble\app" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

