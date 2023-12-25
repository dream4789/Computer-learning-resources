;1+2+3+..+100 = 5050

STACK SEGMENT STACK
    DW 64 DUP(?)
STACK ENDS

DATA SEGMENT
    STRING db '1+2+3+..+100 = $'
    CRLF   db 0AH, 0DH, "$"
    S DW ?
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:STACK
START:
    MOV AX,DATA
    MOV DS,AX
    
    MOV CX,100
    MOV AX,0H
    MOV BX,1H

    
LOOP1:
    ADD AX,BX
    INC BX
    LOOP LOOP1 ; 1+2+3+..+100 = 5050(13BA)
    
    ;ax=13BA bx=0065  
    ;MOV AX,5050
    
    CALL pri_str
    CALL dec_out1     ;可以输出很大十进制数
    
    MOV AH,4CH
    INT 21H

pri_str proc near
    PUSH DX
    PUSH AX
    
    LEA DX,STRING
    MOV AH,9
    INT 21H
    
    POP AX
    POP DX
    ret
pri_str endp

; 可以输出很大十进制数
dec_out1 proc near
    push ax
    push bx
    push cx
    push dx

    mov bx,10
    mov cx,0

yazhan:
    mov dx,0
    div bx
    
    push dx
    inc cx
    
    cmp ax,0
    jz chuzhan
    
    jmp yazhan
    
chuzhan:
    pop dx
    add dl,30h
    mov ah,2            
    int 21h
           
    loop chuzhan
    
    pop dx
    pop cx
    pop bx
    pop ax
    
    ret
dec_out1 endp

CODE ENDS
    END START