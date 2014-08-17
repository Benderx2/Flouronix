#ifndef __VFS_H
#define __VFS_H
#include <klib/kbool.h>
#include <stdint.h>
#define IS_FILE 0x0
#define IS_DIRECTORY 0x01
#define IS_MOUNTPOINT 0x02
#define IS_ROOT 0xE5F4
#define IS_USER 0xE5F5
#define IS_GUEST 0xE6F6
typedef struct sFS_unit {
	char name[128];
	int group_id;
	int user_id;
 	/** The Index of the parent directory **/
	uint32_t parent_index;
	/** Flags - Directory, File, Mountpoint, root etc. **/
	uint8_t flags;
	/** inode - Index Node, Usually provided by filesystems to identify a specific file **/
	uint32_t inode;
	/** Length of the file in bytes **/
	uint32_t length;
	/** FD - File Descriptor, used by OS to identify files **/
	int fd;
	/** offset - Offset in a file */
	int offset;
	
} FS_Unit;
struct dirent {
	char name[128];
	uint32_t inode;
	uint8_t flags;
};
typedef struct sFS_Device {
	char name[128];
	void (*shit)(void);
	int (*donotuse)(FS_Unit*, char*, int);
	int (*write)(FS_Unit*, char* buf, int bytes);
	int (*unlink)(FS_Unit*);
	FS_Unit* (*fopen)(char* name);
	int (*fclose)(FS_Unit*);
	int (*read)(FS_Unit*, char*, int);
	struct dirent* (*readdir)(FS_Unit*);
	int id;
	int group_id;
	int user_id;
	struct sFS_Device* prev;
	struct sFS_Device* next;
} FS_Device;
typedef struct sVFS {
	void (*MountDevice)(FS_Device*);
	void (*UnMountDevice)(FS_Device*);
	FS_Device* (*GetDevice)(char*);
	FS_Unit* (*FopenDevice)(FS_Device*, char*);
	int (*ReadDevice)(FS_Device*, FS_Unit*, char*, int);	
	int (*WriteDevice)(FS_Device*, FS_Unit*, char*, int);	
	struct dirent* (*ReadDirDevice)(FS_Device*, FS_Unit*);
	int (*UnLinkDevice)(FS_Device*, FS_Unit*);
	int (*FcloseDevice)(FS_Device*, FS_Unit*);
} VFS_t;
extern VFS_t KernelVFS;
#endif
