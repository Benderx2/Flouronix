#include <kernel/console/console.h>
#include <kernel/heap/kheap.h>
#include <kernel/fs/vfs.h>
#include <klib/string.h>
VFS_t KernelVFS;
FS_Device* last;
FS_Device* first;
int nDevices;
void MountDevice(FS_Device* Device);
void UnMountDevice(FS_Device* Device);
FS_Device* GetDevice(char* name);
FS_Unit* FOpenDevice(FS_Device* Device, char* Unit);
int ReadDevice(FS_Device* Device, FS_Unit* Unit, char* buf, int bytes);
int WriteDevice(FS_Device* Device, FS_Unit* Unit, char* buf, int bytes);
int FCloseDevice(FS_Device* Device, FS_Unit* Unit);
struct dirent* ReadDirDevice(FS_Device* Device, FS_Unit* Unit);
int UnLinkDevice(FS_Device* Device, FS_Unit* Unit);
void initialise_vfs(void)
{
	KernelVFS.MountDevice = &MountDevice;
	KernelVFS.UnMountDevice = &UnMountDevice;
	KernelVFS.GetDevice = &GetDevice;
	KernelVFS.FopenDevice = &FOpenDevice;
	KernelVFS.ReadDevice = &ReadDevice;
	KernelVFS.WriteDevice = &WriteDevice;
	KernelVFS.ReadDirDevice = &ReadDirDevice;
	KernelVFS.UnLinkDevice = &UnLinkDevice;
	KernelVFS.FcloseDevice = &FCloseDevice;
	FS_Device* Root = (FS_Device*)KernelHeap.Alloc(sizeof(FS_Device));
	strcpy(Root->name, "root");
	KernelVFS.MountDevice(Root);
	Console.WriteLine("VFS Services are activated!\n");
}
void MountDevice(FS_Device* Device)
{
	if(nDevices == 0)
	{
		last = Device;	
		first = Device;
		Device->next = NULL;
		Device->prev = NULL;
		Device->id = 0;
	}
	else {
		last->next = Device;
		Device->prev = last;
		Device->next = NULL;
		Device->id = nDevices;		
		last = Device;
	}
	nDevices++;
}
void UnMountDevice(FS_Device* Device)
{
	FS_Device* nextdevice = (FS_Device*)Device->next;
	FS_Device* previousdevice = (FS_Device*)Device->prev;
	nextdevice->prev = (struct sFS_Device*)previousdevice;
	previousdevice->next = (struct sFS_Device*)nextdevice;
}
FS_Device* GetDevice(char* name)
{
	FS_Device* NextDevice = first;
	while(NextDevice != NULL)
	{
		if(!strcmp(name, NextDevice->name))
		{
			return NextDevice;
		}
		NextDevice = (FS_Device*)NextDevice->next;
	}
	return NULL;
}
FS_Unit* FOpenDevice(FS_Device* Device, char* Unit)
{
	if(Device->fopen != NULL)
	{
		return Device->fopen(Unit);
	}
	return NULL;
	
}
int ReadDevice(FS_Device* Device, FS_Unit* Unit, char* buf, int bytes)
{
	if(Device->read != NULL)
	{
		return Device->read(Unit, buf, bytes);
	}
	return 0;
}
int WriteDevice(FS_Device* Device, FS_Unit* Unit, char* buf, int bytes)
{
	if(Device->read != NULL)
	{
		return Device->write(Unit, buf, bytes);
	}
	return 0;
}
int FCloseDevice(FS_Device* Device, FS_Unit* Unit)
{
	if(Device->fclose != NULL)
	{
		return Device->fclose(Unit);
	}
	return 0;
}
struct dirent* ReadDirDevice(FS_Device* Device, FS_Unit* Unit)
{
	if(Device->readdir != NULL && Unit->flags == IS_DIRECTORY)
	{
		return Device->readdir(Unit);
	}
	return 0;
}
int UnLinkDevice(FS_Device* Device, FS_Unit* Unit)
{
	if(Device->unlink != NULL)
	{
		return Device->unlink(Unit);
	}
	return 0;
}
