#include <klib/stdint.h>
#include <klib/string.h>
#include <klib/kassert.h>
#include <arch/x86/x86.h>
#include <kernel/multiboot/multiboot.h>
#include <kernel/heap/kheap.h>
extern uint32_t k_end;
uint32_t heap_addr;
Heap_t KernelHeap;
Heap_t KernelPageHeap;
#define K_HEAP_SIZE 0x400000
/** Original Implementation: http://wiki.osdev.org/User:Pancakes/BitmapHeapImplementation **/
KHEAPBM kernel_heap;
KHEAPBM kernel_page_heap;
void initialise_heap(void)
{
	k_heapBMInit(&kernel_heap);
	heap_addr = (PHYSICAL_TO_VIRTUAL(*((uint32_t*)(mboot_info->mods_addr+4))));
	Console.WriteLine("Heap_Addr: %d\n", heap_addr);
	kassert(heap_addr > (int)&k_end); 
	k_heapBMAddBlock(&kernel_heap, (uintptr_t)heap_addr , K_HEAP_SIZE, 32);
	KernelHeap.Alloc = &kmalloc;
	KernelHeap.Free = &kfree;
	KernelHeap.Size = 0x200000;
}
void initialise_pd_heap(void)
{
	k_heapBMInit(&kernel_page_heap);
	k_heapBMAddBlock(&kernel_page_heap, (uintptr_t)(heap_addr + K_HEAP_SIZE), K_HEAP_SIZE, 4096);	
	KernelPageHeap.Alloc = &kpagealloc;
	KernelPageHeap.Free = &kpagefree;
	KernelPageHeap.Alloc(1); // Do it to make sure it's aligned
}
void* kpagealloc(uint32_t n)
{
	void* addr = k_heapBMAlloc(&kernel_page_heap, n);
	kassert(addr != NULL);
	return addr;
}
void kpagefree(void* ptr)
{
	k_heapBMFree(&kernel_page_heap, ptr);
}
void* kmalloc(uint32_t n)
{
	void* addr = k_heapBMAlloc(&kernel_heap, n);
	kassert(addr != NULL);
	return addr;
}
void kfree(void* ptr)
{
	k_heapBMFree(&kernel_heap, ptr);
}
void k_heapBMInit(KHEAPBM *heap) {
	heap->fblock = 0;
}
 
int k_heapBMAddBlock(KHEAPBM *heap, uintptr_t addr, uint32_t size, uint32_t bsize) 
{
	KHEAPBLOCKBM		*b;
	uint32_t				bcnt;
	uint32_t				x;
	uint8_t				*bm;
 
	b = (KHEAPBLOCKBM*)addr;
	b->size = size - sizeof(KHEAPBLOCKBM);
	b->bsize = bsize;
 
	b->next = heap->fblock;
	heap->fblock = b;
 
	bcnt = size / bsize;
	bm = (uint8_t*)&b[1];
 
	/* clear bitmap */
	for (x = 0; x < bcnt; ++x) {
			bm[x] = 0;
	}
 
	/* reserve room for bitmap */
	bcnt = (bcnt / bsize) * bsize < bcnt ? bcnt / bsize + 1 : bcnt / bsize;
	for (x = 0; x < bcnt; ++x) {
			bm[x] = 5;
	}
 
	b->lfb = bcnt - 1;
 
	b->used = bcnt;
 
	return 1;
}
 
static uint8_t k_heapBMGetNID(uint8_t a, uint8_t b) {
	uint8_t		c;	
	for (c = a + 1; c == b || c == 0; ++c);
	return c;
}
 
void *k_heapBMAlloc(KHEAPBM *heap, uint32_t size) {
	KHEAPBLOCKBM		*b;
	uint8_t				*bm;
	uint32_t				bcnt;
	uint32_t				x, y, z;
	uint32_t				bneed;
	uint8_t				nid;
 
	/* iterate blocks */
	for (b = heap->fblock; b; b = b->next) {
		/* check if block has enough room */
		if (b->size - (b->used * b->bsize) >= size) {
 
			bcnt = b->size / b->bsize;		
			bneed = (size / b->bsize) * b->bsize < size ? size / b->bsize + 1 : size / b->bsize;
			bm = (uint8_t*)&b[1];
 
			for (x = (b->lfb + 1 >= bcnt ? 0 : b->lfb + 1); x != b->lfb; ++x) {
				/* just wrap around */
				if (x >= bcnt) {
					x = 0;
				}		
 
				if (bm[x] == 0) {	
					/* count free blocks */
					for (y = 0; bm[x + y] == 0 && y < bneed && (x + y) < bcnt; ++y);
 
					/* we have enough, now allocate them */
					if (y == bneed) {
						/* find ID that does not match left or right */
						nid = k_heapBMGetNID(bm[x - 1], bm[x + y]);
 
						/* allocate by setting id */
						for (z = 0; z < y; ++z) {
							bm[x + z] = nid;
						}
 
						/* optimization */
						b->lfb = (x + bneed) - 2;
 
						/* count used blocks NOT bytes */
						b->used += y;
 
						return (void*)(x * b->bsize + (uintptr_t)&b[1]);
					}
 
					/* x will be incremented by one ONCE more in our FOR loop */
					x += (y - 1);
					continue;
				}
			}
		}
	}
 
	return 0;
}
 
void k_heapBMFree(KHEAPBM *heap, void *ptr) {
	KHEAPBLOCKBM		*b;	
	uintptr_t				ptroff;
	uint32_t				bi, x;
	uint8_t				*bm;
	uint8_t				id;
	uint32_t				max;
 
	for (b = heap->fblock; b; b = b->next) {
		if ((uintptr_t)ptr > (uintptr_t)b && (uintptr_t)ptr < (uintptr_t)b + b->size) {
			/* found block */
			ptroff = (uintptr_t)ptr - (uintptr_t)&b[1];  /* get offset to get block */
			/* block offset in BM */
			bi = ptroff / b->bsize;
			/* .. */
			bm = (uint8_t*)&b[1];
			/* clear allocation */
			id = bm[bi];
			/* oddly.. GCC did not optimize this */
			max = b->size / b->bsize;
			for (x = bi; bm[x] == id && x < max; ++x) {
				bm[x] = 0;
			}
			/* update free block count */
			b->used -= x - bi;
			return;
		}
	}
 
	/* this error needs to be raised or reported somehow */
	return;
}
