#ifndef __X86IRQ_H
#define __X86IRQ_H
#define PS2_IRQ 33
#define PIT_IRQ 32
#include <arch/x86/x86.h>
extern void irq0 ();
extern void irq1 ();
extern void irq2 ();
extern void irq3 ();
extern void irq4 ();
extern void irq5 ();
extern void irq6 ();
extern void irq7 ();
extern void irq8 ();
extern void irq9 ();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();
void irq_handler(registers_t regs);
void register_irq_handler(uint8_t n, isr_t handler); 
#endif
