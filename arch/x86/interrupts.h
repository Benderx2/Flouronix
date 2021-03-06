#ifndef __X86_IDT_H
#define __X86_IDT_H
#include <stdint.h>
struct sidt_entry {
	uint16_t base_lo;
	uint16_t sel;
	uint8_t always0;
	uint8_t flags;
	uint16_t base_hi;
} __attribute__((packed));
typedef struct sidt_entry idt_entry_t;
struct sidt_ptr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));
typedef struct sidt_ptr idt_ptr_t;
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void idt_flush(uint32_t);
void initialise_interrupts(void);
void isr_handler(registers_t regs);
#endif
