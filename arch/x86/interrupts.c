/* Interrupts - Contains Code for x86 interrupt handling */
#include <klib/string.h>
#include <kernel/console/console.h>
#include <arch/x86/x86.h>
#include <arch/x86/interrupts.h>
#include <arch/x86/irq.h>
#include <arch/x86/exceptions.h>
static void idt_set_gate(uint8_t,uint32_t,uint16_t,uint8_t);
idt_entry_t idt_entries[256]; /** An x86 interrupt descriptor table has maximum of 256 entries **/
idt_ptr_t idt_ptr;
void initialise_interrupts()
{
	CPU_x86.FlushInterruptTable = &idt_flush;
	CPU_x86.SetInterruptDescriptorEntry = &idt_set_gate;
	idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
	idt_ptr.base = (uint32_t)&idt_entries;
	memset(&idt_entries, 0, sizeof(idt_entry_t)*256);
	CPU_x86.SetInterruptDescriptorEntry(0, (uint32_t)isr0 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(1, (uint32_t)isr1 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(2, (uint32_t)isr2 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(3, (uint32_t)isr3 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(4, (uint32_t)isr4 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(5, (uint32_t)isr5 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(6, (uint32_t)isr6 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(7, (uint32_t)isr7 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(8, (uint32_t)isr8 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(9, (uint32_t)isr9 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(10, (uint32_t)isr10 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(11, (uint32_t)isr11 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(12, (uint32_t)isr12 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(13, (uint32_t)isr13 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(14, (uint32_t)isr14 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(15, (uint32_t)isr15 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(16, (uint32_t)isr16 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(17, (uint32_t)isr17 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(18, (uint32_t)isr18 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(19, (uint32_t)isr19 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(20, (uint32_t)isr20 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(21, (uint32_t)isr21 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(22, (uint32_t)isr22 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(23, (uint32_t)isr23 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(24, (uint32_t)isr24 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(25, (uint32_t)isr25 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(26, (uint32_t)isr26 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(27, (uint32_t)isr27 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(28, (uint32_t)isr28 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(29, (uint32_t)isr29 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);	
	CPU_x86.SetInterruptDescriptorEntry(30, (uint32_t)isr30 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);	
	CPU_x86.SetInterruptDescriptorEntry(31, (uint32_t)isr31 , 0x08 /** code sel = 0x08 **/, 0x8E /** 0x8E = Kernel interrupt **/);
	CPU_x86.SetInterruptDescriptorEntry(32, (uint32_t)irq0, 0x08, 0x8E);
	CPU_x86.SetInterruptDescriptorEntry(33, (uint32_t)irq1, 0x08, 0x8E);
	CPU_x86.SetInterruptDescriptorEntry(34, (uint32_t)irq2, 0x08, 0x8E);
	CPU_x86.SetInterruptDescriptorEntry(35, (uint32_t)irq3, 0x08, 0x8E);
	CPU_x86.SetInterruptDescriptorEntry(36, (uint32_t)irq4, 0x08, 0x8E);
	CPU_x86.SetInterruptDescriptorEntry(37, (uint32_t)irq5, 0x08, 0x8E);
	CPU_x86.SetInterruptDescriptorEntry(38, (uint32_t)irq6, 0x08, 0x8E);
	CPU_x86.SetInterruptDescriptorEntry(39, (uint32_t)irq7, 0x08, 0x8E);
	CPU_x86.SetInterruptDescriptorEntry(40, (uint32_t)irq8, 0x08, 0x8E);
	CPU_x86.SetInterruptDescriptorEntry(41, (uint32_t)irq9, 0x08, 0x8E);
	CPU_x86.SetInterruptDescriptorEntry(42, (uint32_t)irq10, 0x08, 0x8E);
	CPU_x86.SetInterruptDescriptorEntry(43, (uint32_t)irq11, 0x08, 0x8E);
	CPU_x86.SetInterruptDescriptorEntry(44, (uint32_t)irq12, 0x08, 0x8E);
	CPU_x86.SetInterruptDescriptorEntry(45, (uint32_t)irq13, 0x08, 0x8E);
	CPU_x86.SetInterruptDescriptorEntry(46, (uint32_t)irq14, 0x08, 0x8E);
	CPU_x86.SetInterruptDescriptorEntry(47, (uint32_t)irq15, 0x08, 0x8E);
	CPU_x86.FlushInterruptTable((uint32_t)&idt_ptr);
}
static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
   idt_entries[num].base_lo = base & 0xFFFF;
   idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

   idt_entries[num].sel     = sel;
   idt_entries[num].always0 = 0;
   // We must uncomment the OR below when we get to using user-mode.
   // It sets the interrupt gate's privilege level to 3.
   idt_entries[num].flags   = flags /* | 0x60 */;
} 
void isr_handler(registers_t regs)
{	
	Console.WriteLine("Interrupt Received: %q0x%x%y\n", Console.Yellow, regs.int_no);
	Console.WriteLine("EAX : 0x%x, EBX : 0x%x, ECX : 0x%x, EDX : 0x%x, EDI : 0x%x, ESI : 0x%x, ESP : 0x%x\n", regs.eax, regs.ebx, regs.ecx, regs.edx, regs.edi, regs.esi, regs.esp);
	// Is it something bad?
	switch(regs.int_no)
	{
		case DIVIDE_BY_ZERO:
			CPU_x86.DivideByZeroException(regs);
		case OVERFLOW:
			CPU_x86.OverflowException(regs);
		case PAGE_FAULT:
			CPU_x86.PageFaultException(regs);
		case BND_RANGE_EXCEED:
			CPU_x86.BoundRangeExceededException(regs);
		case INVALID_OPCODE:
			CPU_x86.InvalidOpcodeException(regs);
		case STACK_SEG_FAULT:
			CPU_x86.StackSegmentFaultException(regs);
		case GENERAL_PROTECTION_FAULT:
			CPU_x86.GeneralProtectionException(regs);
		case INV_TSS:
			CPU_x86.InvalidTSSException(regs);
		case SEGMENT_NOT_PRESENT:
			
		case DOUBLE_FAULT:	
			CPU_x86.DoubleFaultException(regs);
		default:
			return;
	}
	
	
}
