#include <kernel/console/console.h>
#include <arch/x86/paging.h>
page_dir_t* k_page_dir;
union page_union {
	uint32_t page_int;
	page_t page;
};
void map_page_kernel(uint32_t addr)
{	
	addr /= 0x1000;
	uint32_t offset = addr / 1024;
	Console.WriteLine("Mapping Kernel page, address : %x, offset : %d, sizeof(page_t) : %d\n", addr, offset, sizeof(page_t));
	k_page_dir = (page_dir_t*)(k_page_dir_addr);
	union page_union temp2;
	temp2.page = k_page_dir->pages[offset];
	if(temp2.page_int)
	{
		Console.WriteLine("Page already exists not creating a new one, returning...");
		return;
	}
	Console.WriteLine("Page doesn't exist. Creating new page....");
	union page_union temp;
	temp.page.present = 1;
	temp.page.rw = 1;
	temp.page.reserved = 0;
	temp.page.dpl = 1;
	temp.page.frame = addr;
	Console.WriteLine("Page Integer : %x\n", temp.page_int );
	k_page_dir->pages[offset] = temp.page; // Present, Kernel, 4MB page
	Console.WriteLine("[SWITCH_PAGE_DIR]Page Directory Address : %x\n", k_page_dir->physaddr);
	asm volatile("mov %0, %%cr3":: "r"(k_page_dir->physaddr));
}
