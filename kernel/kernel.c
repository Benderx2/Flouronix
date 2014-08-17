#include <klib/stdio.h>
#include <klib/stddef.h>
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
// RME Emulator
#include <arch/x86/emulator/rme.h>
int kmain(unsigned long magic)
{
	// Enable Interrupts
	CPU_x86.EnableInterrupts();	
	Console.Clear();
	Console.WriteLine("kmain(), Magic Number passed by bootloader: %q%x%y, initrd location: %x\n", Console.Green, magic, *(uint32_t*)mboot_info->mods_addr);
	if(magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		Console.WriteLine("Sorry, you aren't using a multiboot compatible loader. Please feel free to fuck off\n");
		CPU_x86.halt();
	}
	// Initialise the page frame allocator and map 0x00000000 - 0x000bfffff to 0xc0000000 - 0xc0bfffff
	uint32_t total_mem = (mboot_info->mem_upper + mboot_info->mem_lower) * 1024;
	kassert(total_mem >= REQUIRED_MEM_SIZE); // Also check for memory.
	initialise_paging(total_mem);
	CPU_x86.MapKernelPage(0x400000, 0xC0400000);
	CPU_x86.MapKernelPage(0x800000, 0xC0800000);
	// Intialise the page directory heap
	initialise_pd_heap();
	kassert(PHYSICAL_TO_VIRTUAL(mboot_info->mods_count) > 0);
	/** Initialise ramfs **/
	uint32_t ramfs_location = PHYSICAL_TO_VIRTUAL((*((uint32_t*)(PHYSICAL_TO_VIRTUAL(mboot_info->mods_addr)))));
	initialise_ramfs(ramfs_location);
	Console.WriteLine("Flouronix 0.1.7. Available Memory (kilobytes) : %d\n", mboot_info->mem_upper + mboot_info->mem_lower);
	FS_Device* ramfs = KernelVFS.GetDevice("ramfs.0");	
	kassert(ramfs != NULL);	
	Console.WriteLine("List contents of /ramfs.0\n");
	FS_Unit* ramfs_root = KernelVFS.FopenDevice(ramfs, "/");
	kassert(ramfs_root != NULL);
	struct dirent* dirent0;
	int roots = 0;
	while((dirent0 = KernelVFS.ReadDirDevice(ramfs, ramfs_root)) != NULL)
	{
		if(dirent0->flags == IS_DIRECTORY)
		{
			Console.WriteLine("<dir>");
		}
		Console.WriteLine(" name: %s inode : %d\n", dirent0->name, dirent0->inode);
		roots++;
		ramfs_root->offset = roots;		
	}
	FS_Unit* file = KernelVFS.FopenDevice(ramfs, "test1.txt");
	Console.WriteLine("test1.txt size : %d\n", file->length);
	char* buf = KernelHeap.Alloc(32);
	file->offset = 0; // Start at offset 0
	Console.WriteLine("file->inode : %d\n", file->inode);
	KernelVFS.ReadDevice(ramfs, file, buf, 31);
	Console.WriteLine("Read 'test1.txt' under /%s. Contents : \n%s\n", ramfs->name, buf);
	CPU_x86.halt();
}
