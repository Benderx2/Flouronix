#include <klib/kassert.h>
#include <klib/kbool.h>
#include <klib/string.h>
#include <kernel/multiboot/multiboot.h>
#include <kernel/heap/kheap.h>
#include <kernel/console/console.h>
#include <kernel/fs/vfs.h>
#include <kernel/fs/ramfs/ramfs.h>
#include <arch/x86/x86.h>
#include <arch/x86/interrupts.h>
#include <arch/x86/paging.h>
#define random 0xc0400000
int kmain(unsigned long magic)
{
	CPU_x86.EnableInterrupts();	
	Console.Clear();
	Console.WriteLine("kmain(), Magic Number passed by bootloader: %q%x%y, initrd location: %x\n", Console.Green, magic, *(uint32_t*)mboot_info->mods_addr);
	if(magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		Console.WriteLine("Sorry, you aren't using a multiboot compatible loader. Please feel free to fuck off\n");
		CPU_x86.halt();
	}
	/** Initialise ramfs **/
	initialise_paging((mboot_info->mem_upper + mboot_info->mem_lower) * 1024);
	kassert(mboot_info->mods_count > 0);
	uint32_t ramfs_location = PHYSICAL_TO_VIRTUAL((*((uint32_t*)(mboot_info->mods_addr))));
	//map_page_kernel(ramfs_location);
	initialise_ramfs(ramfs_location);
	Console.WriteLine("Flouronix 0.1.7. Available Memory (kilobytes) : %d\n", mboot_info->mem_upper + mboot_info->mem_lower);
	page_dir_t* k_page_dir = (page_dir_t*)(k_page_dir_addr);
	Console.WriteLine("Kernel Page Dir Address (Virtual): %x\n", (int)k_page_dir);
	Console.WriteLine("Kernel Page Dir address (Physical): %x\n", (int)k_page_dir->physaddr);
	FS_Device* ramfs = KernelVFS.GetDevice("ramfs.0");
	FS_Unit* file = KernelVFS.FopenDevice(ramfs, "test1.txt");
	Console.WriteLine("test1.txt size : %d\n", file->length);
	char* buf = KernelHeap.Alloc(32);
	file->offset = 0; // Start at offset 0
	Console.WriteLine("file->inode : %d\n", file->inode);
	KernelVFS.ReadDevice(ramfs, file, buf, 31);
	CPU_x86.MapKernelPage(0xC00000, 0xC00000);
	uint8_t* a = (uint8_t*)0xC00000;
	*a = 'C';
	Console.WriteLine("Read 'test1.txt' under /%s. Contents : \n%s\n", ramfs->name, buf);
	char n;
	while(true)
	{
		n = 0;
		Console.WriteLine(">:");
		while( n != '\n')
		{
			n = Console.ReadChar();
			Console.WriteChar(n);
		}
	}
}
