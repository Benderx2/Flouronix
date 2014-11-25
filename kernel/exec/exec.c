#include <kernel/heap/kheap.h>
#include <kernel/exec/exec.h>
#include <kernel/fs/vfs.h>
#include <arch/x86/x86.h>
#include <arch/x86/paging.h>
#include <kernel/console/console.h>
#include <string.h>
int (*ptr)(void);
#define LOAD_ADDR 0xC0800000
int exec_prog(FS_Device* Device, char* file_path)
{
	FS_Unit* newfile = KernelVFS.FopenDevice(Device, file_path);
	char* space = KernelHeap.Alloc(newfile->length);
	KernelVFS.ReadDevice(Device, newfile, space, newfile->length);
	memcpy((char*)LOAD_ADDR, space, newfile->length);
	KernelHeap.Free(space);
	ptr = (void*)LOAD_ADDR;
	return ptr();
}
