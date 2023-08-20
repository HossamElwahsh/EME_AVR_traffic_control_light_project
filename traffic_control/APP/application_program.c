/*
 * application_program.c
 *
 * Created: 8/20/2023 9:38:29 AM
 *  Author: Team GUCALEX
 */
#include "Button.h"
#include "application_interface.h"
#include "Led.h"
#include "lcd_interface.h"

/* private functions prototypes */
static void delay_check();
static void yellow_led_blink(void);
static void update_traffic_lcd(char * str);

/* App flags */
boolean ped_request = FALSE;
boolean ped_passing = FALSE;

void application_init()
{
    /* init button */
    Button_Init(BUTTON_INT1, BTN_MODE_INTERRUPT);

    /* init lights */
    Led_Init(LED_YELLOW_ARGS);
    Led_Init(LED_BLUE_ARGS);
    Led_Init(LED_RED_ARGS);
    Led_Init(LED_GREEN_ARGS);

    /* set callback for button event */
    btn_setCallback(pedestrian_btn_event);

    /* init LCD */
    LCD_init();

    /* clear LCD */
    LCD_clear();

    /* Show team name */
    LCD_setCursor(LCD_LINE0, LCD_COL3);
    LCD_sendString("Team GUCALEX");

}

void application_start()
{
    /* Super loop */
    while(TRUE)
    {
        /* update LCD to CAR MODE */
        update_traffic_lcd(LCD_STR_CAR);

        /* GREEN LIGHT ON */
        Led_TurnOn(LED_GREEN_ARGS);

        /* GREEN LIGHT delay */
        delay_check();

        /* turn off GREEN LIGHT */
        Led_TurnOff(LED_GREEN_ARGS);

        /* YELLOW LIGHT BLINK FOR (DUR) */
        yellow_led_blink();

        /* RED LIGHT ON */
        Led_TurnOn(LED_RED_ARGS);

        /* delay red light */
        delay_check();

        /* check for pedestrian mode */
        if(TRUE == ped_request)
        {
            /* Raise ped passing */
            ped_passing = TRUE;

            /* Reset ped flag */
            ped_request = FALSE;

            /* Turn on PED LIGHT */
            update_traffic_lcd(LCD_STR_PED);
            Led_TurnOn(LED_BLUE_ARGS);

            _delay_ms(TRAFFIC_LIGHT_DELAY_TOTAL);

            Led_TurnOff(LED_BLUE_ARGS);

            /* Reset ped passing */
            ped_passing = FALSE;
        }

        /* Turn off RED LIGHT */
        Led_TurnOff(LED_RED_ARGS);
    }
}

static void update_traffic_lcd(char * str)
{
    LCD_setCursor(LCD_LINE2, LCD_COL5);
    LCD_sendString(str);
}

static void yellow_led_blink(void)
{
    /* Blink LED for DELAY_TOTAL duration */
    for (int i = 0; i < TRAFFIC_LIGHT_DELAY_TOTAL/YELLOW_BLINK_DURATION; ++i)
    {
        Led_Flip(LED_YELLOW_ARGS);
        _delay_ms(YELLOW_BLINK_DURATION);
    }

    /* Turn off Yellow LED */
    Led_TurnOff(LED_YELLOW_ARGS);
}

static void delay_check()
{
    /* delay */
    for (int i = 0; i < (TRAFFIC_LIGHT_DELAY_TOTAL / TRAFFIC_LIGHT_DELAY_SENSE); ++i)
    {
        /* minor delay amount */
        _delay_ms(TRAFFIC_LIGHT_DELAY_SENSE);

        /* break condition */
        if(ped_request == TRUE)
        {
            /* break delay */
            break;
        }
    }
}

void pedestrian_btn_event(void)
{
    /* requirement */
    if(FALSE == ped_passing)
    {
        ped_request = TRUE;
    }
}