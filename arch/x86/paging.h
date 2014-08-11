/** x86 - Page Structures **/
#ifndef __X86PAGING_H
#define __X86PAGING_H
#include <klib/kbool.h>
#include <arch/x86/x86.h>
#include <stdint.h>
#define PAGE_SIZE 0x400000
#define NUMBER_OF_PT_ENTRIES 1024
#define I86_PAGE_WRITEABLE 0x2
#define I86_PAGE_PRESENT 0x1
#define I86_PAGE_4MB 0x80
#define I86_PAGE_USER 0x4
typedef uint32_t page_t;
typedef struct sPage_dir {
	page_t pages[NUMBER_OF_PT_ENTRIES];
	uint32_t physaddr;
} page_dir_t;
extern uint32_t k_page_dir_addr;
void map_page_kernel(uint32_t vaddr, uint32_t paddr);
void switch_page_directory(uint32_t page_dir_addr);
void map_page(uint32_t vaddr, uint32_t paddr, bool is_user, page_dir_t* page_dir);
void map_kernel_to_addr_space(page_dir_t* page_dir);
void initialise_paging(int total_mem);
uint32_t alloc_frame(void);
void free_frame(uint32_t);
int get_physaddr(int vaddr);
#endif
