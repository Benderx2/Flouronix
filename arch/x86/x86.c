#include <arch/x86/x86.h>
#include <stdint.h>
CPUx86_t CPU_x86;
void initialise_x86(void)
{
	CPU_x86.outportb = &outportb;
	CPU_x86.inportb = &inportb;
	CPU_x86.inportw = &inportw;
	CPU_x86.outportw = &outportw;
	CPU_x86.outportl = &outportl;
	CPU_x86.inportl = &inportl;
	CPU_x86.cpuid = &cpuid;
	CPU_x86.EnableInterrupts = &EnableInterrupts;
	CPU_x86.DisableInterrupts = &DisableInterrupts;
	CPU_x86.halt = &sys_halt;
	CPU_x86.invlpg = &invlpg;
}
void outportb(uint16_t  port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

uint8_t inportb(uint16_t  port)
{
   uint8_t ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

uint16_t inportw(uint16_t port)
{
   	uint16_t ret;
   	asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   	return ret;
} 
void sys_halt(void)
{
	asm("cli");
	for(;;);
}
void EnableInterrupts(void)
{
	asm("sti");
}
void DisableInterrupts(void)
{
	asm("cli");
}
void cpuid(int code, uint32_t *a, uint32_t *d) {
  	asm volatile("cpuid":"=a"(*a),"=d"(*d):"a"(code):"ecx","ebx");
}
void outportw(uint16_t portid, uint16_t value)
{
	asm volatile("outw %%ax, %%dx": :"d" (portid), "a" (value));
}
void outportl(uint16_t portid, uint32_t value)
{
	asm volatile("outl %%eax, %%dx": :"d" (portid), "a" (value));
}
uint32_t inportl(uint16_t portid)
{
		uint32_t ret;
		asm volatile("inl %%dx, %%eax":"=a"(ret):"d"(portid));
		return ret;
}
static inline void invlpg(void* m)
{
    /* Clobber memory to avoid optimizer re-ordering access before invlpg, which may cause nasty bugs. */
    //asm volatile ( "invlpg (%0)" : : "m"(m) : "memory" );
}

