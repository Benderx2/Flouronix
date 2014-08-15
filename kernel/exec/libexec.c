#include <kernel/heap/kheap.h>
#include <kernel/exec/elf.h>
#include <arch/x86/x86.h>
#include <arch/x86/paging.h>
int load_elf(void* elf_addr)
{
	//! Allocate space for page directory
	page_dir_t* page_dir = (page_dir_t*)KernelHeap.Alloc(sizeof(page_dir_t));
	//! Since the page directory is allocated from the heap, it's physical address will be 
	page_dir->physaddr = PHYSICAL_TO_VIRTUAL((uint32_t)page_dir));
	//! Map the kernel to this address space
	CPU_x86.MapKerneltoAddressSpace(page_dir);
}
