/** x86 - Page Structures **/
#ifndef __X86PAGING_H
#define __X86PAGING_H
#include <klib/kbool.h>
#include <arch/x86/x86.h>
#include <stdint.h>
#define NUMBER_OF_PT_ENTRIES 1024
typedef struct sPage {
	uint32_t present : 1; // Is this page present in memory?
	uint32_t rw : 1; // Read / Write Bit
	uint32_t dpl : 1; // Kernel or User?
	uint32_t p_access : 1; // Page Accessed since last refresh
	uint32_t p_write : 1; // Page written to since last refresh	
	uint32_t reserved : 7; // Reserved
	uint32_t frame : 20; // 20-bits for page frame
} page_t;
typedef struct sPage_dir {
	page_t pages[NUMBER_OF_PT_ENTRIES];
	uint32_t physaddr;
} page_dir_t;
extern uint32_t k_page_dir_addr;
void map_page_kernel(uint32_t addr);
#endif
