/*
 * Button.h
 *
 *  Created on: Feb 3, 2023
 *      Author: A M
 */




#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "gpio.h"
#include "Button_Cfg.h"

typedef enum {
    BUTTON_NOT_PRESSED,
    BUTTON_PRESSED
} Button_StatusType;

void Button_Init(uint8_t_ port, uint8_t_ pin, en_btn_mode_t en_btn_mode);
Button_StatusType Button_GetStatus (uint8_t_ port, uint8_t_ pin);
void btn_setCallback(void (* callback) (void));
void btn_pressed_notification(void);
#endif /* INC_BUTTON_H_ */
