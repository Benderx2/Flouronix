#ifndef __X86EXCEPTIONS_H
#define __X86EXCEPTIONS_H
#define DIVIDE_BY_ZERO 0x0
#define DEBUG_TRAP 0x1
#define NMI 0x2
#define BREAK_POINT 0x3 // When your OS and the CPU are having a good time with each other, and suddenly they break up.
#define OVERFLOW 0x4 // Yo mama so fat that even a uint32_t cannot store the amount of calories she has.
#define BND_RANGE_EXCEED 0x5 
#define INVALID_OPCODE 0x6 
#define STACK_SEG_FAULT 0xC 
#define GENERAL_PROTECTION_FAULT 0xD // Eh? Didn't use protection while banging?
#define PAGE_FAULT 0xE 
#define SIMD_FLOATING_POINT 0x13
#define VIRT_EXCEP 0x14
#define INV_TSS 0xA
#define SEGMENT_NOT_PRESENT 0xB
#define DOUBLE_FAULT 0x8 // Didn't use it again? So sorry.
void initialise_exceptions(void);
#endif
