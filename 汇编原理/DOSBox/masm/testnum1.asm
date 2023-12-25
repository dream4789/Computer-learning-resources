DATAS SEGMENT 
    STRING DB 10,13,'$'  ;换行回车
DATAS ENDS
 
STACKS SEGMENT STACK
    
STACKS ENDS
 
CODES SEGMENT
    ASSUME CS:CODES, DS:DATAS, SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX

    mov AX,123  ;(7b)
    CALL Binary       ;二进制输出函数
    CALL symoutput    ;无符号十进制输出
    CALL HEXADECIMAL  ;十六进制输出函数
    
    MOV AH,4CH
    INT 21H

; 二进制输出函数
Binary PROC
    PUSH CX
    PUSH DX
    MOV CX,16

BinaryL1:
    ROL AX,1
    MOV DL,AL
    AND DL,1
    ADD DL,48
    
    PUSH AX
    MOV AH,2
    INT 21H
    POP AX
    
    LOOP BinaryL1
    
    POP DX
    POP CX
    
    CALL LINEFEED ;换行回车
    RET
Binary ENDP


; 十六进制输出函数
HEXADECIMAL PROC
    PUSH BX
    PUSH CX
    PUSH DX
    MOV BX,16

HEXADECIMALL1:
    CMP BX,0
    JE HEXADECIMALL3
    
    MOV CL,4
    ROL AX,CL
    MOV DL,AL
    AND DL,15
    ADD DL,48
    CMP DL,58
    JL HEXADECIMALL2
    
    SUB DL,48
    ADD DL,55
    
HEXADECIMALL2:
    PUSH AX
    MOV AH,2
    INT 21H
    POP AX
    
    SUB BX,4
    JMP HEXADECIMALL1
    
HEXADECIMALL3:
    MOV DL,'H'
    MOV AH,2
    INT 21H
    
    POP BX
    POP CX
    POP DX
    
    CALL LINEFEED ;换行回车
    RET 
HEXADECIMAL ENDP


;无符号十进制输出
symoutput proc
    PUSH AX
    mov cl, 10; cl 是每次 除以 10
    mov ch, 0; 计算 除了多少次，也就是有几位
    
L0:	
    div cl; ax 除以 cl
  	push ax; 此时的商存储在 al 中，
  	;余数存储在 ah 中，此时 ax = ah
  	add ch, 1
  	mov ah, 0
  	cmp ax, 0;如果 ax 是 0，说明除干净了
  	jne L0
	
again: 
    cmp ch, 0; 此时 ch 的值就是位数，每次出栈，
  	je over
  	pop dx; 把栈顶元素存储到 dx 中
  	mov dl, dh;然后将 dl 的值等于 dh
  	add dl, 48
  	mov ah, 2
  	int 21h
  	
  	dec ch
  	jmp again

over:
    POP AX;
    CALL LINEFEED ;换行回车
    ret
symoutput endp


LINEFEED PROC
    PUSH AX
    PUSH DX
    
    MOV DX,OFFSET STRING
    MOV AH,9
    INT 21H
    
    POP DX
    POP AX
    RET
LINEFEED ENDP

CODES ENDS
    END START