.intel_syntax noprefix


.section .data
printc_chaine:
.ascii "\0\0"

.section .text
.global _start

_start:
call main
int 0x60

.global asm_printc
asm_printc:
pushad
push edx
and al,0x0F
or al,0x10
mov [printc_chaine],al
mov edx, offset printc_chaine
mov   al,6
int   0x61
pop edx
mov   al,6
int   0x61
movb [printc_chaine],0x17
mov edx, offset printc_chaine
mov   al,6
int   0x61
popad
ret



