/*
 *
 * Created: 6/4/2023 8:14:00 PM
 * Author: Hossam Elwahsh - https://github.com/HossamElwahsh
 */ 

/* Includes */
#include "exi_interface.h"
#include "exi_private.h"
#include "exi_config.h"


void(*callback_int0)(void)=NULL_PTR;
void(*callback_int1)(void)=NULL_PTR;
void(*callback_int2)(void)=NULL_PTR;


void EXI_init(void)
{
#if EXI_CONF_COUNT > ZERO
    /* disable global interrupt to avoid bugs during configuration */
    CLR_BIT(EXI_SREG_REG, EXI_SREG_I_BIT);

    for (int i = 0; i < EXI_CONF_COUNT; ++i)
    {
        EXI_enableInterrupt(st_gs_exi_config_arr[i].enu_exi_int, st_gs_exi_config_arr[i].enu_exi_sense_mode);
    }

    /* re-enable global interrupt flag */
    SET_BIT(EXI_SREG_REG, EXI_SREG_I_BIT);

#else

    /* disable global interrupt */
    CLR_BIT(EXI_SREG_REG, EXI_SREG_I_BIT);

#endif
}

/**
 * @brief                               :   Sets and enables an external interrupt pin with given mode
 *
 * @param[in]   enu_exi_interrupt       :   Interrupt number (EXI_INT0, EXI_INT1, EXI_INT2)
 * @param[in]   enu_exi_sense_mode      :   sense mode enum
 *
 * @return  EXI_SUCCESS                 :   In case of Successful Operation
 *          EXI_ERROR                   :   In case of Failed Operation
 */
enu_exi_error_t_ EXI_enableInterrupt(enu_exi_int_t_ enu_exi_interrupt, enu_exi_sense_mode_t_ enu_exi_sense_mode)
{
    // enable required interrupt
    if(enu_exi_interrupt == EXI_INT0)
    {
        switch (enu_exi_sense_mode) {
            case EXI_SENSE_LOW_LEVEL:
                EXI_MCUCR_REG &= EXI_SENSE_LOW_LEVEL;
                break;
            case EXI_SENSE_ANY_LEVEL:
            case EXI_SENSE_FALLING_EDGE:
            case EXI_SENSE_RISING_EDGE:
                EXI_MCUCR_REG &= 0xFC; // clear INT0 bits
                EXI_MCUCR_REG |= enu_exi_sense_mode; // sets INT0 sense mode
                break;
            default:
                return EXI_ERROR;
        }

        // 3. enable INT0
        CLR_BIT(EXI_GICR_REG, EXI_GICR_INT0_BIT);

    }
    else if(enu_exi_interrupt == EXI_INT1)
    {
        switch (enu_exi_sense_mode) {
            case EXI_SENSE_LOW_LEVEL:
                EXI_MCUCR_REG &= ((EXI_SENSE_LOW_LEVEL<<2) | 0x3);
                break;
            case EXI_SENSE_ANY_LEVEL:
            case EXI_SENSE_FALLING_EDGE:
            case EXI_SENSE_RISING_EDGE:
                EXI_MCUCR_REG &= 0xF3; // clear INT1 bits

                EXI_MCUCR_REG |= ((enu_exi_sense_mode << 2) | 0x3); // sets INT1 sense mode
                break;
            default:
                return EXI_ERROR;
        }

        // 3. enable INT1
        SET_BIT(EXI_GICR_REG, EXI_GICR_INT1_BIT);
    }
    else if(enu_exi_interrupt == EXI_INT2)
    {
        switch (enu_exi_sense_mode)
        {
            case EXI_SENSE_FALLING_EDGE:
            {
                CLR_BIT(EXI_MCUCSR_REG, EXI_MCUCSR_ISC2_BIT);
                break;
            }
            case EXI_SENSE_RISING_EDGE:
            {
                SET_BIT(EXI_MCUCSR_REG, EXI_MCUCSR_ISC2_BIT);
                break;
            }
            default:
            {
                return EXI_ERROR;
            }
        }

        // 3. enable INT2
        SET_BIT(EXI_GICR_REG, EXI_GICR_INT2_BIT);
    }
    else
    {
        return EXI_ERROR;
    }

    return EXI_SUCCESS;
}

/**
 * @brief                               :   Disables a given interrupt pin
 *
 * @param[in]   enu_exi_interrupt       :   Interrupt number (EXI_INT0, EXI_INT1, EXI_INT2)
 *
 * @return  EXI_SUCCESS                 :   In case of Successful Operation
 *          EXI_ERROR                   :   In case of Failed Operation
 */
enu_exi_error_t_ EXI_disableInterrupt(enu_exi_int_t_ enu_exi_interrupt)
{
    switch (enu_exi_interrupt) {
        case EXI_INT0:
            CLR_BIT(EXI_GICR_REG, EXI_GICR_INT0_BIT);
            break;
        case EXI_INT1:
            CLR_BIT(EXI_GICR_REG, EXI_GICR_INT1_BIT);
            break;
        case EXI_INT2:
            CLR_BIT(EXI_GICR_REG, EXI_GICR_INT2_BIT);
            break;
        default:
            /* Do Nothing */
            return EXI_ERROR;
    }
    return EXI_SUCCESS;
}


/**
 * @brief                               :   Disables all external interrupts
 */
void EXI_disableAll(void)
{
    CLR_BIT(EXI_SREG_REG, EXI_SREG_I_BIT);  // disable Global Interrupt Flag
    CLR_BIT(EXI_GICR_REG, 6);               // disable INT0
    CLR_BIT(EXI_GICR_REG, 7);               // disable INT1
    CLR_BIT(EXI_GICR_REG, 5);               // disable INT2
}

enu_exi_error_t_    EXI_setCallback         (enu_exi_int_t_ enu_exi_interrupt, void (* callback_fun_ptr) (void) )
{
    enu_exi_error_t_ enu_exi_error_retval = EXI_SUCCESS;
    switch (enu_exi_interrupt)
    {
        case EXI_INT0:
        {
            if(NULL_PTR != callback_fun_ptr)
            {
                callback_int0 = callback_fun_ptr;
            }
            break;
        }
        case EXI_INT1:
        {
            if(NULL_PTR != callback_fun_ptr)
            {
                callback_int1 = callback_fun_ptr;
            }
            break;
        }
        case EXI_INT2:
        {
            if(NULL_PTR != callback_fun_ptr)
            {
                callback_int2 = callback_fun_ptr;
            }
            break;
        }
        case EXI_INT_TOTAL:
            enu_exi_error_retval = EXI_ERROR;
            break;
    }

    return EXI_SUCCESS;
}


ISR(EXT_INT_0){
    if(NULL_PTR != callback_int0)
    {
        callback_int0();
    }
}
ISR(EXT_INT_1)
{
    if(NULL_PTR != callback_int1)
    {
        callback_int1();
    }
}
ISR(EXT_INT_2)
{
    if(NULL_PTR != callback_int2)
    {
        callback_int2();
    }
}
