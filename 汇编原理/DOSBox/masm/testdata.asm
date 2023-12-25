data segment
  	A db '12345678909999'
  	n equ $-a        ;n存放 A的字节数db（10个）
    C db '123456'
  	B db n dup(?)
data ends

STACK SEGMENT PARA STACK 'stack'
    ;DW 0,0,0,0, 0,0,0,0, 0,0,0,0
    ;DW 0FFFFH,0FFFFH,0FFFFH,0FFFFH, 0FFFFH,0FFFFH,0FFFFH,0FFFFH
STACK ENDS

code segment
	  assume cs:code,ds:data
start:
  	mov ax,data
  	mov ds,ax
  	lea si,a
  	lea di,b
   	add di,n 
   	mov cx,n
move:	
    mov al,[si]
   	mov [di],al
  	inc si
  	dec di
  	loop move
  	mov ah,4ch
  	int 21h
code ends
 	  end start