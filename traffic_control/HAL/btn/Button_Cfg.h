/*
 * Button_Cfg.h
 *
 *  Created on: Feb 3, 2023
 *      Author: A M
 */






#ifndef INC_BUTTON_CFG_H_
#define INC_BUTTON_CFG_H_

#define BUTTON_CONNECTION_PULLUP    1

typedef enum
{
    BTN_MODE_NORMAL      = 0    ,
    BTN_MODE_INTERRUPT
}en_btn_mode_t;

/************************* USER CONFIGURATIONS *************************/
#define BUTTON_CONNECTION           BUTTON_CONNECTION_PULLUP
#define BUTTON_INT1                   PORTD_ID,PIN3_ID
//#define BUTTON_PIN                  PORTA_ID,PIN1_ID
//#define BUTTON2_PIN                 PORTB_ID,PIN1_ID
/********************** END OF USER CONFIGURATIONS **********************/
#define Buzzer						PORTC_ID,PIN6_ID
//#define Relay1						PORTC_ID,PIN7_ID
//#define Relay2						PORTA_ID,PIN7_ID
#define RedLed						PORTB_ID,PIN7_ID
#define GreenLed					PORTA_ID,PIN4_ID
#define BlueLed						PORTA_ID,PIN5_ID
#define YellowLed					PORTA_ID,PIN6_ID


#endif /* INC_BUTTON_CFG_H_ */
