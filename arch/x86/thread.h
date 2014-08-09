#ifndef __THREAD_H
#define __THREAD_H
#include <stdint.h>
#include <arch/x86/x86.h>
typedef struct sTask {
	int pid;
	DWORD esp;	
	DWORD ebp, eip;
	DWORD eflags;
	struct sTask* next;
	struct sTask* prev;
} task_t; 
#endif
