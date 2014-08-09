#include <arch/x86/x86.h>
#include <arch/x86/interrupts.h>
#include <arch/x86/irq.h>
#include <arch/x86/pit0.h>
#include <kernel/console/PS2.h>
#include <kernel/console/console.h>
isr_t interrupt_handlers[256];
void timer_irq(registers_t regs);
void initialise_hardware_interrupts(void)
{
	CPU_x86.SetIRQHandler = &register_irq_handler;
	CPU_x86.outportb(0x20, 0x11);
  	CPU_x86.outportb(0xA0, 0x11);
 	CPU_x86.outportb(0x21, 0x20);
  	CPU_x86.outportb(0xA1, 0x28);
  	CPU_x86.outportb(0x21, 0x04);
  	CPU_x86.outportb(0xA1, 0x02);
  	CPU_x86.outportb(0x21, 0x01);
  	CPU_x86.outportb(0xA1, 0x01);
  	CPU_x86.outportb(0x21, 0x00);
  	CPU_x86.outportb(0xA1, 0x00);
	//CPU_x86.outportb(0x21, 0xFC);
	/** IRQ for PS/2 Keyboard **/
	initialise_timer(1); // 1hz
	CPU_x86.SetIRQHandler(PS2_IRQ, &ps2_irq);
	CPU_x86.EnableInterrupts();
}
void irq_handler(registers_t regs)
{
   if (regs.int_no >= 40)
   {
       CPU_x86.outportb(0xA0, 0x20);
   }
   CPU_x86.outportb(0x20, 0x20);
   if (interrupt_handlers[regs.int_no] != 0)
   {
       isr_t handler = interrupt_handlers[regs.int_no];
       handler(regs);
   }
} 
void register_irq_handler(uint8_t n, isr_t handler)
{
  interrupt_handlers[n] = handler;
} 
