;; arch/x86/boot/grub/boot.asm
;; Multiboot init module for x86.
;; Multiboot header, Segment Flush and Wakeup call to main
;; Compile with: nasm -f elf arch/x86/boot/grub/boot.asm -o boot.o
;; A few multiboot constants
;; Defined by linker script
align 4
extern code, bss, end, kmain
extern initialise_console, initialise_interrupts, initialise_hardware_interrupts, initialise_x86, initialise_heap, initialise_exceptions, initialise_vfs, initialise_mboot
;; 32-bit Addressing Mode.
[BITS 32] 
MODULEALIGN equ  1<<0            
MEMINFO equ  1<<1            
FLAGS equ  MODULEALIGN | MEMINFO 
MAGIC equ 0x1BADB002  
CHECKSUM equ -(MAGIC + FLAGS)
KERNEL_VIRTUAL_BASE equ 0xC0000000                
KERNEL_PAGE_NUMBER equ (KERNEL_VIRTUAL_BASE >> 22)  
global KERNEL_STACK
;; Code Section
[SECTION .text]
align 4
header:
dd MAGIC
dd FLAGS
dd CHECKSUM
;.magic dd 0x1BADB002
;.flags dd 3
;.checksum dd 0 - 0x1BADB002 - 3
align 4096
global k_page_dir
k_page_dir:
    dd 0x00000083
    times (KERNEL_PAGE_NUMBER - 1) dd 0                 ; Pages before kernel space.
    ; This page directory entry defines a 4MB page containing the kernel.
    dd 0x00000083
    times (1024 - KERNEL_PAGE_NUMBER - 1) dd 0  ;
    dd k_page_dir - KERNEL_VIRTUAL_BASE
global start
start equ (early_start )
global k_page_dir_addr
k_page_dir_addr:
	dd k_page_dir
;global early_start
early_start:	
    	; Set CR3 to physical address of page directory
    	mov ecx, (k_page_dir - KERNEL_VIRTUAL_BASE)
   	mov cr3, ecx                                       
    	; Enable 4MB pages (PSE)
    	mov ecx, cr4
    	or ecx, 0x00000010                          
    	mov cr4, ecx 
	; Enable VME (Virtual 8086 Extensions)
	mov ecx, cr4
	or cl, 1
	mov cr4, ecx
    	; Set PG bit in CR0 i.e. enable paging
    	mov ecx, cr0
    	or ecx, 0x80000000                        
    	mov cr0, ecx
    	; Load the "virtual" address in ECX and jump!
    	lea ecx, [.jump_to_higher_half]
    	jmp ecx 
.jump_to_higher_half:
    	;; Set the kernel stack
    	mov esp, KERNEL_STACK
    	;; Jump to wake up call
    	jmp WAKEUP_CALL
WAKEUP_CALL:
	push eax
	;; Load the descriptor tables
	;; Make sure interrupts are cleared
	cli
	lgdt [GDTR]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov fs, ax
	mov gs, ax
	jmp 0x8:Flush
Flush:
	; Woo! We're finally in a state to proceed to our C code.	
	; Enable SSE
	mov eax, cr0
	and ax, 0xFFFB	
	or ax, 0x2			
	mov cr0, eax
	mov eax, cr4
	or ax, 3 << 9		
	mov cr4, eax	
	pop eax
	; Save these two registers, they contain multiboot information
	mov dword [save_eax], eax
	mov dword [save_ebx], ebx
	; Call Constructors
	push ebx
	call initialise_mboot
	call initialise_x86
	call initialise_console
	call initialise_interrupts
	call initialise_hardware_interrupts
	call initialise_exceptions
	call initialise_heap
	call initialise_vfs
	;mov dword [k_page_dir], 0
	;invlpg [0]
	; Push the multiboot regs to stack.
	push dword [save_eax]
	; kmain!
	call kmain
	; Halt the CPU if kmain returns
	cli
	hlt
	jmp $
global read_cr2
read_cr2:
	mov eax, cr2
	ret
[SECTION .data]
save_eax: dd 0
save_ebx: dd 0
align 4
GDT32:
;; Segment 0x0 - NULL Segment
.NULL:
	;; Null Descriptor
	times 2 dd 0x0
;; Segment 0x8 - Kernel Code Segment
.K_CODE:
	;; Kernel Code Segment
	;; Limit
	dw 0xFFFF
	;; Lower 16-bits of base
	dw 0
	;; Middle 8-bits 
	db 0
	;; Access Byte
	db 10011010b
	;; Granularity
	db 11001111b
	;; Higher 8-bits 
	db 0
;; Segment 0x10 - Kernel Data Segment
.K_DATA:
	;; All same as above
	dw 0xFFFF
	dw 0
	db 0
	db 10010010b
	db 11001111b
	db 0
.VM86_TSS:
	dw 0xFFFF
	dw 0
	db 0
	db 0x89
	db 0x8F
	db 0
.END:
	;; End of GDT
GDTR:
.SIZE:
	dw GDT32.END - GDT32 - 1 	;; Size of the Table
.GDT:
	dd GDT32			;; Address of GDT
[SECTION .bss]
; Kernel Stack
KERNEL_STACK_BUFFER:
	resb 8192
KERNEL_STACK:	  
  
