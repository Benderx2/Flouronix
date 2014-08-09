/** 8259 PIT **/
#include <stdint.h>
#include <arch/x86/x86.h>
#include <arch/x86/irq.h>
uint32_t ticks = 0;
void pit0_irq(registers_t regs);
void initialise_timer(uint32_t frequency)
{
   CPU_x86.SetIRQHandler(PIT_IRQ, &pit0_irq);
   uint32_t divisor = 1193180 / frequency;
   CPU_x86.outportb(0x43, 0x36);
   uint8_t l = (uint8_t)(divisor & 0xFF);
   uint8_t h = (uint8_t)((divisor>>8) & 0xFF );
   CPU_x86.outportb(0x40, l);
   CPU_x86.outportb(0x40, h);
} 
void pit0_irq(registers_t regs)
{
	ticks++;
}
