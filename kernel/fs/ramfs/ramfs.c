#include <kernel/console/console.h>
#include <kernel/heap/kheap.h>
#include <kernel/fs/vfs.h>
#include <kernel/fs/ramfs/ramfs.h>
#include <klib/string.h>
ramfs_header* header;
ramfs_file_header* file_headers;
FS_Unit* ramfs_units;
FS_Unit* ramfs_fopen(char* name);
int ramfs_read(FS_Unit*, char*, int);
void initialise_ramfs(uint32_t ramfs_location)
{
	header = (ramfs_header*)ramfs_location;
	file_headers = (ramfs_file_header*)(ramfs_location + sizeof(ramfs_header));
	ramfs_units = (FS_Unit*)kmalloc(header->nFiles);
	FS_Device* ramfs_dev = (FS_Device*)KernelHeap.Alloc(sizeof(FS_Device));
	strcpy(ramfs_dev->name, "ramfs.0");
	ramfs_dev->fopen = &ramfs_fopen;
	ramfs_dev->read = &ramfs_read;
	KernelVFS.MountDevice(ramfs_dev);
	for(int i = 0; i < header->nFiles; i++)
	{
		file_headers[i].offset += ramfs_location;
		strcpy(ramfs_units[i].name, file_headers[i].name);
		ramfs_units[i].inode = i;
		ramfs_units[i].flags = IS_FILE;
		ramfs_units[i].length = file_headers[i].length;
		ramfs_units[i].parent_index = ramfs_dev->id;
	}
	Console.WriteLine("%qRamFS Initialized%y\n", Console.LightBlue);
}
FS_Unit* ramfs_fopen(char* name)
{
	for(int i = 0; i < header->nFiles; i++)
	{
		if(!strcmp(ramfs_units[i].name, name))
		{
			return &(ramfs_units[i]);
		}
	}
	return NULL;
}
int ramfs_read(FS_Unit* Unit, char* buf, int size)
{
	ramfs_file_header header = file_headers[Unit->inode];
	if(Unit->offset > header.length)
	{
		return 0;
	}
	if(Unit->offset + size > header.length)
	{
		size = header.length - Unit->offset;
	}
	memcpy(buf, (uint8_t*)(header.offset + Unit->offset), size);
	return size;
}
