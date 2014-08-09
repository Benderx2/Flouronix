#ifndef __PS2_H
#define __PS2_H	
#include <arch/x86/x86.h>
void ps2_irq(registers_t regs);
int ps2_readc(void);
#endif
