cmake_minimum_required(VERSION 3.26)
project(traffic_control C)

set(CMAKE_C_STANDARD 11)

include_directories(traffic_control/APP)
include_directories(traffic_control/COMMON)
include_directories(traffic_control/HAL/btn)
include_directories(traffic_control/HAL/lcd)
include_directories(traffic_control/HAL/led)
include_directories(traffic_control/MCAL/exi)
include_directories(traffic_control/MCAL/gpio)
include_directories("C:/Program Files (x86)/Atmel/Studio/7.0/packs/atmel/ATmega_DFP/1.7.374/include/avr")
include_directories("C:/Program Files (x86)/Atmel/Studio/7.0/toolchain/avr8/avr8-gnu-toolchain/avr/include")

add_executable(traffic_control
        traffic_control/APP/application_interface.h
        traffic_control/APP/application_program.c
        traffic_control/COMMON/bit_math.h
        traffic_control/COMMON/interrupts.h
        traffic_control/COMMON/std.h
        traffic_control/HAL/btn/Button.c
        traffic_control/HAL/btn/Button.h
        traffic_control/HAL/btn/Button_Cfg.h
        traffic_control/HAL/lcd/lcd_config.h
        traffic_control/HAL/lcd/lcd_interface.h
        traffic_control/HAL/lcd/lcd_private.h
        traffic_control/HAL/lcd/lcd_program.c
        traffic_control/HAL/led/Led.c
        traffic_control/HAL/led/Led.h
        traffic_control/MCAL/exi/exi_config.h
        traffic_control/MCAL/exi/exi_interface.h
        traffic_control/MCAL/exi/exi_lconfig.c
        traffic_control/MCAL/exi/exi_private.h
        traffic_control/MCAL/exi/exi_program.c
        traffic_control/MCAL/gpio/gpio.c
        traffic_control/MCAL/gpio/gpio.h
        traffic_control/MCAL/gpio/gpio_private.h
        "C:/Program Files (x86)/Atmel/Studio/7.0/toolchain/avr8/avr8-gnu-toolchain/avr/include/util/delay.h"
        traffic_control/main.c)
