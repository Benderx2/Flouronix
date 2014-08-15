#ifndef __X86_H
#define __X86_H
#include <klib/kbool.h>
#include <arch/x86/paging.h>
#define PAGE_ALIGN 4096
#define PHYSICAL_TO_VIRTUAL(a) (a + 0xC0000000)
#include <stdint.h>
typedef uint32_t DWORD;
typedef uint16_t WORD;
typedef uint8_t BYTE;
typedef struct registers
{
   //uint32_t cr2;
   uint32_t ds;                  // Data segment selector
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   uint32_t int_no,  err_code;    // Interrupt number and error code (if applicable)
   uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t; 
typedef void (*isr_t)(registers_t);
typedef struct sCPUx86 {
	void (*outportb)(uint16_t, uint8_t);
	uint8_t (*inportb)(uint16_t);
	void (*outportw)(uint16_t, uint16_t);
	uint16_t (*inportw)(uint16_t);
	void (*outportl)(uint16_t, uint32_t);	
	uint32_t (*inportl)(uint16_t);
	void (*cpuid)(int code, uint32_t* a, uint32_t* b);
	void (*halt)(void);
	void (*EnableInterrupts)(void);
	void (*DisableInterrupts)(void);
	void (*GeneralProtectionException)(registers_t regs);
	void (*PageFaultException)(registers_t regs);
	void (*StackSegmentFaultException)(registers_t regs);
	void (*InvalidOpcodeException)(registers_t regs);
	void (*BoundRangeExceededException)(registers_t regs);
	void (*DivideByZeroException)(registers_t regs);
	void (*SIMDFloatingPointException)(registers_t regs);
	void (*OverflowException)(registers_t regs);
	void (*InvalidTSSException)(registers_t regs);
	void (*DoubleFaultException)(registers_t regs);
	void (*SegmentNotPresent)(registers_t regs);
	// Interrupt related stuff...
	void (*SetInterruptDescriptorEntry)(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
	void (*FlushInterruptTable)(uint32_t);
	// IRQ stuff
	void (*SetIRQHandler)(uint8_t n, isr_t handler);
	// Pagin'
	void (*invlpg)(void* m);
	uint32_t (*AllocatePageFrame)(void);
	void (*FreePageFrame)(uint32_t);
	void (*MapKernelPage)(uint32_t, uint32_t);
	void (*MapPage)(uint32_t, uint32_t, bool, page_dir_t*);
	void (*MapKerneltoAddressSpace)(page_dir_t*);
	void (*SwitchAddressSpace)(uint32_t);
} CPUx86_t;
uint8_t inportb(uint16_t);
void outportb(uint16_t  port, uint8_t value);
uint16_t inportw(uint16_t port);
void sys_halt();
void cpuid(int code, uint32_t *a, uint32_t *d);
void outportw(uint16_t portid, uint16_t value);
void outportl(uint16_t portid, uint32_t value);
void outportl(uint16_t portid, uint32_t value);
void EnableInterrupts(void);
void DisableInterrupts(void);
uint32_t inportl(uint16_t portid);
static inline void invlpg(void* m);
extern CPUx86_t CPU_x86;
#endif
