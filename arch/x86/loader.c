#include <stdint.h>
#include <arch/x86/x86.h>
#include <arch/x86/loader.h>
#include <kernel/heap/kheap.h>
page_dir_t* create_page_directory(void)
{
	page_dir_t* new_page_dir = (page_dir_t*)KernelPageHeap.Alloc(1);
	CPU_x86.MapKerneltoAddressSpace(new_page_dir);
	return new_page_dir;
}
