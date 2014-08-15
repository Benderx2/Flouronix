#include <kernel/console/console.h>
#include <arch/x86/exceptions.h>
#include <arch/x86/x86.h>
#include <stdint.h>
extern uint32_t read_cr2();
void GPF_handler(registers_t regs);
void PF_handler(registers_t regs);
void SSF_handler(registers_t regs);
void IOP_handler(registers_t regs);
void BREE_handler(registers_t regs);
void DIVZERO_handler(registers_t regs);
void SIMD_handler(registers_t regs);
void OFLOW_handler(registers_t regs);
void INVTSS_handler(registers_t regs);
void DF_handler(registers_t regs);
void SNP_handler(registers_t regs);
void initialise_exceptions(void)
{
	CPU_x86.GeneralProtectionException = &GPF_handler;
	CPU_x86.PageFaultException = &PF_handler;
	CPU_x86.StackSegmentFaultException = &SSF_handler;
	CPU_x86.InvalidOpcodeException = &IOP_handler;
	CPU_x86.BoundRangeExceededException = &BREE_handler;
	CPU_x86.DivideByZeroException = &DIVZERO_handler;
	CPU_x86.SIMDFloatingPointException = &SIMD_handler;
	CPU_x86.OverflowException = &OFLOW_handler;
	CPU_x86.InvalidTSSException = &INVTSS_handler;
	CPU_x86.DoubleFaultException = &DF_handler;
	CPU_x86.SegmentNotPresent = &SNP_handler;
}
void GPF_handler(registers_t regs)
{
	Console.WriteLine("PANIC: %qGeneral Protection Fault!%y\n", Console.Red);
	Console.WriteLine("CS : 0x%x, DS : 0x%x, SS : 0x%x\n", regs.cs, regs.ds, regs.ss);
	CPU_x86.halt();
}
void PF_handler(registers_t regs)
{
	int present = !(regs.err_code & 0x1);   // Page not present
   	int rw = regs.err_code & 0x2;           // Write operation?
   	int us = regs.err_code & 0x4;           // Processor was in user-mode?
   	int reserved = regs.err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
   	int id = regs.err_code & 0x10;          // Caused by an instruction fetch?
	Console.WriteLine("PANIC: %qPage Fault!%y\n", Console.Red);
	Console.WriteLine("CR2 : 0x%x, At EIP: 0x%x\n", read_cr2(), regs.eip);
	if(present) { Console.WriteLine("Page Not Present!\n"); }
	if(rw) { Console.WriteLine("Attempt to write to a Read-Only page!\n"); }
	if(us) { Console.WriteLine("Processor was in User mode\n"); }
	if(reserved) { Console.WriteLine("Reserved\n"); }
	if(id) { Console.WriteLine("Invalid Instruction fetch\n"); }
	CPU_x86.halt();
}
void SSF_handler(registers_t regs)
{
	Console.WriteLine("PANIC: %qStack Segment Fault%y\n", Console.Red);
	CPU_x86.halt();
}
void IOP_handler(registers_t regs)
{
	Console.WriteLine("PANIC: %qInvalid Opcode!%y\n", Console.Red);
	Console.WriteLine("At EIP : 0x%x\n", regs.eip);
	CPU_x86.halt();
}
void BREE_handler(registers_t regs)
{
	Console.WriteLine("PANIC: %qBound Rage Exceeded!%y\n", Console.Red);
	Console.WriteLine("At EIP : 0x%x\n", regs.eip);
	CPU_x86.halt();
}
void DIVZERO_handler(registers_t regs)
{
	Console.WriteLine("PANIC: %qAttempt to divide by 0!%y\n", Console.Red);
	Console.WriteLine("At EIP : 0x%x\n", regs.eip);
	CPU_x86.halt();
}
void SIMD_handler(registers_t regs)
{
	Console.WriteLine("PANIC: %qSIMD Floating Point Exception!%y\n", Console.Red);
	Console.WriteLine("At EIP : 0x%x\n", regs.eip);
	CPU_x86.halt();
}
void OFLOW_handler(registers_t regs)
{
	Console.WriteLine("PANIC: %qOverflow Exception!%y\n", Console.Red);
	Console.WriteLine("At EIP : 0x%x\n", regs.eip);
	CPU_x86.halt();
}
void INVTSS_handler(registers_t regs)
{
	Console.WriteLine("PANIC: %qInvalid Task State Segment (TSS)%y\n", Console.Red);
	Console.WriteLine("At EIP : 0x%x\n", regs.eip);
}
void DF_handler(registers_t regs)
{
	Console.WriteLine("SUPER PANIC! %qDouble Fault!%x\n", Console.Yellow);
	Console.WriteLine("At EIP : 0x%x\n", regs.eip);
}
void SNP_handler(registers_t regs)
{
	Console.WriteLine("PANIC: %qSegment Not Present%y\n", Console.Red);
	Console.WriteLine("At EIP : 0x%x\n", regs.eip);
}
