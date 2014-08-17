#include <kernel/console/console.h>
#include <kernel/heap/kheap.h>
#include <kernel/fs/vfs.h>
#include <kernel/fs/ramfs/ramfs.h>
#include <klib/string.h>
ramfs_header* header;
ramfs_file_header* file_headers;
FS_Unit* ramfs_units;
struct dirent dirent; 
FS_Unit* ramfs_fopen(char* name);
int ramfs_read(FS_Unit*, char*, int);
struct dirent *ramfs_readdir(FS_Unit* Unit);
void initialise_ramfs(uint32_t ramfs_location)
{
	header = (ramfs_header*)ramfs_location;
	file_headers = (ramfs_file_header*)(ramfs_location + sizeof(ramfs_header));
	FS_Device* ramfs_dev = (FS_Device*)KernelHeap.Alloc(sizeof(FS_Device));
	ramfs_units = (FS_Unit*)kmalloc((header->nFiles + 1) * sizeof(FS_Unit));
	KernelHeap.Alloc(16);
	strcpy(ramfs_dev->name, "ramfs.0");
	ramfs_dev->fopen = &ramfs_fopen;
	ramfs_dev->read = &ramfs_read;
	ramfs_dev->readdir = &ramfs_readdir;
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
	// Add the initrd_root
	ramfs_units[header->nFiles+1].flags = IS_DIRECTORY;
	strcpy(ramfs_units[header->nFiles+1].name, "/");
	ramfs_units[header->nFiles+1].inode = header->nFiles;
	ramfs_units[header->nFiles+1].parent_index = ramfs_dev->id;
	Console.WriteLine("%qRamFS Initialized%y\n", Console.LightBlue);
}
FS_Unit* ramfs_fopen(char* name)
{
	for(int i = 0; i <= header->nFiles + 1; i++)
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
struct dirent *ramfs_readdir(FS_Unit* Unit)
{
	if(Unit->flags != IS_DIRECTORY)
	{
		return NULL;
	}
	else {
		if(Unit->offset > header->nFiles + 1 || Unit->offset < 0)
		{
			return NULL;
		} 
		else {
			strcpy(dirent.name, ramfs_units[Unit->offset].name);
			dirent.inode = ramfs_units[Unit->offset].inode;
			dirent.flags = ramfs_units[Unit->offset].flags;
			return &dirent;
		}
		
	}
		
}
