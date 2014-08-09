;; x86 Interrupt Descriptor Table
global idt_flush
idt_flush:
	;; Grab the address of IDTR from stack
	mov eax, [esp + 4]
	lidt [eax]
	ret
	;; Taken from JamesM, make life easier....
	%macro ISR_NOERRCODE 1
		global isr%1
		isr%1:
		cli
		push 0
		push %1 
		jmp isr_common_stub 
	%endmacro
	%macro ISR_ERRCODE 1
	global isr%1
	isr%1:
		cli 
		push %1 
		jmp isr_common_stub
	%endmacro
;; Yup, define these entries
ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31
ISR_NOERRCODE 255
;; Defined by C code
[extern isr_handler]
isr_common_stub:
		;; Save register states
		pushad
		xor eax, eax
		;; Save current data selector
		mov ax, ds
		;; Push data selector
		push eax
		;; Switch to kernel data selector
		mov ax, 0x10
		mov ds, ax
		mov es, ax
		mov fs, ax
		mov gs, ax
		;; Call our handler
		call isr_handler
		;; Restore eax and cr2
		pop eax
		;; Switch back to old segment
		mov ds, ax
		mov es, ax
		mov fs, ax
		mov gs, ax
		popad
		add esp, 8
		sti
		;; Return from interrupt
		iretd
