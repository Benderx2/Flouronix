#ifndef __RAMFS_H
#define __RAMFS_H
#include <stdint.h>
typedef struct {
	uint32_t nFiles;
} ramfs_header;
typedef struct {
	uint8_t magic;
	int8_t name[64];
	uint32_t offset;
	uint32_t length;
} ramfs_file_header;
void initialise_ramfs(uint32_t ramfs_location, int user, int grp);
#endif
