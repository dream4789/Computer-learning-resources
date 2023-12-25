DATAS SEGMENT 
    STRING DB 10,13,'$'  ;���лس�
DATAS ENDS
 
STACKS SEGMENT STACK
    
STACKS ENDS
 
CODES SEGMENT
    ASSUME CS:CODES, DS:DATAS, SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX

    mov AX,123  ;(7b)
    CALL Binary       ;�������������
    CALL symoutput    ;�޷���ʮ�������
    CALL HEXADECIMAL  ;ʮ�������������
    
    MOV AH,4CH
    INT 21H

; �������������
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
    
    CALL LINEFEED ;���лس�
    RET
Binary ENDP


; ʮ�������������
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
    
    CALL LINEFEED ;���лس�
    RET 
HEXADECIMAL ENDP


;�޷���ʮ�������
symoutput proc
    PUSH AX
    mov cl, 10; cl ��ÿ�� ���� 10
    mov ch, 0; ���� ���˶��ٴΣ�Ҳ�����м�λ
    
L0:	
    div cl; ax ���� cl
  	push ax; ��ʱ���̴洢�� al �У�
  	;�����洢�� ah �У���ʱ ax = ah
  	add ch, 1
  	mov ah, 0
  	cmp ax, 0;��� ax �� 0��˵�����ɾ���
  	jne L0
	
again: 
    cmp ch, 0; ��ʱ ch ��ֵ����λ����ÿ�γ�ջ��
  	je over
  	pop dx; ��ջ��Ԫ�ش洢�� dx ��
  	mov dl, dh;Ȼ�� dl ��ֵ���� dh
  	add dl, 48
  	mov ah, 2
  	int 21h
  	
  	dec ch
  	jmp again

over:
    POP AX;
    CALL LINEFEED ;���лس�
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