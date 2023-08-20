/*
 * Button.c
 *
 *  Created on: Feb 3, 2023
 *      Author: Sakr
 */




#include "std.h"
#include "gpio.h"
#include "Button_Cfg.h"
#include "Button.h"
#include "exi_interface.h"

void(*callback_btn_event)(void) = NULL_PTR;

void Button_Init(uint8_t_ port, uint8_t_ pin, en_btn_mode_t en_btn_mode)
{
    if(en_btn_mode == BTN_MODE_NORMAL)
    {
        GPIO_setupPinDirection(port, pin, PIN_INPUT);
    }
    else if(en_btn_mode == BTN_MODE_INTERRUPT)
    {
        /* init EXI Module */
        EXI_init();

        EXI_setCallback(EXI_INT1, btn_pressed_notification);
    }
}

Button_StatusType Button_GetStatus (uint8_t_ port, uint8_t_ pin)
{
	Button_StatusType state = BUTTON_NOT_PRESSED;

    if (GPIO_readPin(port, pin) == LOGIC_LOW)
    {
        state = BUTTON_PRESSED;
    }

    return state;
}

void btn_setCallback(void (* callback) (void))
{
    if(NULL_PTR != callback)
    {
        callback_btn_event = callback;
    }
}

void btn_pressed_notification(void)
{
    if(NULL_PTR != callback_btn_event)
    {
        callback_btn_event();
    }
}
