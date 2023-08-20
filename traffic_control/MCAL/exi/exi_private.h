/*
 * exi_private.h
 *
 * Created: 29/5/2023 3:01:33 AM
 *  Author: hossam
 */ 


#ifndef EXI_PRIVATE_H_
#define EXI_PRIVATE_H_

/* PRIVATE UTILS */
#include "std.h"
#include "bit_math.h"
#include "interrupts.h"

/*------------------ External Interrupt Registers ------------------*/

/* MCUCR: MCU Control Register */

/* INT1 MSB control bit
 * 0: low level/anylogical change
 * 1: failling/rising edge
 * */
#define EXI_MCUCR_ISC11_BIT  3

/* INT1 LSB control bit
 * 0: low level/falling edge
 * 1: any logical/rising edge
 * */
#define EXI_MCUCR_ISC10_BIT  2


/* INT0 MSB control bit
 * 0: low level/anylogical change
 * 1: failling/rising edge
 * */
#define EXI_MCUCR_ISC01_BIT  1


/* INT0 LSB control bit
 * 0: low level/falling edge
 * 1: any logical/rising edge
 * */
#define EXI_MCUCR_ISC00_BIT  0
#define EXI_MCUCR_REG *((volatile uint8_t_* )0x55)  // 8-bit register

/* Interrupt Sense Control 2 (INT2)
 *
 * */
#define EXI_MCUCSR_ISC2_BIT  6
#define EXI_MCUCSR_REG *((volatile uint8_t_* )0x54)  // 8-bit register

/* General Interrupt Control Register */
#define EXI_GICR_INT0_BIT   6
#define EXI_GICR_INT1_BIT   7
#define EXI_GICR_INT2_BIT   5
#define EXI_GICR_REG *((volatile uint8_t_* )0x5B)  // 8-bit register

/* General Interrupt Flag Register */
/* INT0 Flag */
#define EXI_GIFR_INTF0_BIT  6

/* INT1 Flag */
#define EXI_GIFR_INTF1_BIT  7

/* INT2 Flag */
#define EXI_GIFR_INTF2_BIT  5
#define EXI_GIFR_REG *((volatile uint8_t_* )0x5A)  // 8-bit register

/* Global interrupt enable bit */
#define EXI_SREG_I_BIT 7
#define EXI_SREG_REG * ((volatile uint8_t_ *) 0x5F)

#endif /* EXI_PRIVATE_H_ */