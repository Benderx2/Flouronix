org 0xC0800000
use32
_start:
	mov al, 'A'
	mov byte [0xC0000000+0xB8000], al
	mov eax, 200
	ret
