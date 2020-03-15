
#ifndef INTGLB_REGISTER_H
#define INTGLB_REGISTER_H

#define SREG       *((volatile u8*)0x5F) /* Status Register */
#define SREG_I     7                      /* Global Interrupt Enable Bit */

#endif
