#include <klib/kbool.h>
#include <klib/kassert.h>
#include <klib/string.h>
#include <kernel/multiboot/multiboot.h>
#include <kernel/heap/kheap.h>
#include <kernel/console/console.h>
#include <arch/x86/paging.h>
page_dir_t* k_page_dir;
uint32_t nFrames;
uint32_t* Frames;
uint32_t placement_addr;
void map_page(uint32_t vaddr, uint32_t paddr, bool is_user, page_dir_t* page_dir);
#define PAGE_DIR_OFFSET(x) (x >> 22)
#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))
static void set_frame(uint32_t frame_addr)
{
   uint32_t frame = frame_addr / PAGE_SIZE;
   uint32_t idx = INDEX_FROM_BIT(frame);
   uint32_t off = OFFSET_FROM_BIT(frame);
   Frames[idx] |= (0x1 << off);
}
static void clear_frame(uint32_t frame_addr)
{
   uint32_t frame = frame_addr/ PAGE_SIZE;
   uint32_t idx = INDEX_FROM_BIT(frame);
   uint32_t off = OFFSET_FROM_BIT(frame);
   Frames[idx] &= ~(0x1 << off);
}
static uint32_t test_frame(uint32_t frame_addr)
{
   uint32_t frame = frame_addr / PAGE_SIZE;
   uint32_t idx = INDEX_FROM_BIT(frame);
   uint32_t off = OFFSET_FROM_BIT(frame);
   return (Frames[idx] & (0x1 << off));
}
uint32_t return_first_free_frame(void)
{
    uint32_t i, j;
    for (i = 0; i < nFrames; i++)
    {
        if (Frames[i] != 0xFFFFFFFF) // nothing free, exit early.
        {
            // at least one bit is free here.
            for (j = 0; j < 32; j++)
            {
                uint32_t toTest = 0x1 << j;
                if ( !(Frames[i]&toTest) )
                {
                    return i*4*8+j;
                }
            }
        }
    }
    return -1;
}
uint32_t alloc_frame(void)
{
	uint32_t frame_index = return_first_free_frame();
	kassert(frame_index != -1);
	set_frame(frame_index * PAGE_SIZE);
	Console.WriteLine("Page Frame Allocation, Frame Index : %x\n", frame_index);
	return frame_index * PAGE_SIZE;
	
}
void free_frame(uint32_t addr)
{
   uint32_t frame;
   if (!(frame=addr))
   {
       return; // The given page didn't actually have an allocated frame!
   }
   else
   {
       clear_frame(frame); // Frame is now free again.
   }
} 
void initialise_paging(int total_mem)
{
	nFrames = total_mem / PAGE_SIZE;
	Console.WriteLine("Total Memory : 0x%x, Number of page frames : 0x%x\n", total_mem, nFrames);
	Frames = (uint32_t*)KernelHeap.Alloc(nFrames);
	memset(Frames, 0, nFrames);	
	set_frame(0 * PAGE_SIZE); // The 0th frame is already mapped.
	CPU_x86.AllocatePageFrame = &alloc_frame;
	CPU_x86.FreePageFrame = &free_frame;
	CPU_x86.MapKernelPage = &map_page_kernel;
	CPU_x86.MapPage = &map_page;
	CPU_x86.MapKerneltoAddressSpace = &map_kernel_to_addr_space;
	CPU_x86.SwitchAddressSpace = &switch_page_directory;
}
void print_first_k_entry(void)
{
	page_dir_t* k_page_dir = (page_dir_t*)(k_page_dir_addr);
	Console.WriteLine("First Entry in Kernel Page Directory: %x\n", k_page_dir->pages[0]);
}

void map_page_kernel(uint32_t paddr, uint32_t vaddr)
{	
	set_frame(paddr); // Is mapped.
	Console.WriteLine("Mapping page, Physical Address: %x, Virtual Address : %x, Page : %x\n", paddr, vaddr, paddr | I86_PAGE_PRESENT | I86_PAGE_WRITEABLE | I86_PAGE_4MB);
	k_page_dir = (page_dir_t*)(k_page_dir_addr);
	uint32_t offset = vaddr >> 22;
	k_page_dir->pages[offset] = paddr | I86_PAGE_PRESENT | I86_PAGE_WRITEABLE | I86_PAGE_4MB;
	Console.WriteLine("Going to switch_page_directory CR3: %x\n", k_page_dir->physaddr);
	asm volatile("mov %0, %%cr3":: "r"(k_page_dir->physaddr));
}
void map_kernel_to_addr_space(page_dir_t* page_dir)
{
	// map the kernel to this space
	if(page_dir != NULL)
	{
		map_page(0xc0000000, 0x100000, false, page_dir);
	}
}
void map_page(uint32_t paddr, uint32_t vaddr, bool is_user, page_dir_t* page_dir)
{
	if(is_user == true)
	{
		page_dir->pages[PAGE_DIR_OFFSET(vaddr)] = paddr | I86_PAGE_PRESENT | I86_PAGE_WRITEABLE | I86_PAGE_4MB; 
	}
	else {
		page_dir->pages[PAGE_DIR_OFFSET(vaddr)] = paddr | I86_PAGE_PRESENT | I86_PAGE_WRITEABLE | I86_PAGE_4MB;	
	} 
}
void switch_page_directory(uint32_t page_dir_addr)
{
	asm volatile("mov %0, %%cr3":: "r"(page_dir_addr));
}

int get_physaddr(int vaddr)
{
	  k_page_dir = (page_dir_t*)(k_page_dir_addr);
	  unsigned long ptindex = (unsigned long)vaddr >> 22;	
	  return (int)((k_page_dir->pages[ptindex] & ~0xFFF) + ((unsigned long)vaddr & 0xFFF));
}
