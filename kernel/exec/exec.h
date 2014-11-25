#ifndef __FEF_H
#define __FEF_H
// Flouronix Executable Format
#include <stdint.h>
#include <kernel/fs/vfs.h>
int exec_prog(FS_Device* Device, char* file_path);
#endif
