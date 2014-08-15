#ifndef __KHEAP_H
#define __KHEAP_H
#define INITIAL_HEAP_SIZE 0x800000
#include <stdint.h>
typedef void* kptr_t;
typedef struct sHeap {
	kptr_t (*Alloc)(uint32_t bytes);
	void (*Free)(void* ptr);
	int Size;
} Heap_t;
typedef struct _KHEAPBLOCKBM {
	struct _KHEAPBLOCKBM *next;
	uint32_t size;
	uint32_t used;
	uint32_t bsize;
        uint32_t lfb;
} KHEAPBLOCKBM;
 
typedef struct _KHEAPBM {
	KHEAPBLOCKBM			*fblock;
} KHEAPBM;
void initialise_heap(void);
void* kmalloc(uint32_t n);
void* kpagealloc(uint32_t n);
void kpagefree(void* n);
void kfree(void* ptr);
void k_heapBMInit(KHEAPBM *heap);
int k_heapBMAddBlock(KHEAPBM *heap, uintptr_t addr, uint32_t size, uint32_t bsize);
static uint8_t k_heapBMGetNID(uint8_t a, uint8_t b);
void *k_heapBMAlloc(KHEAPBM *heap, uint32_t size);
void k_heapBMFree(KHEAPBM *heap, void *ptr);
void initialise_pd_heap(void);
extern Heap_t KernelHeap;
extern Heap_t KernelPageHeap;
#endif

