; S=1+2*3+3*4+4*5+...+N(N+1)+...=1119 10�������
STACK SEGMENT STACK
    DW 64 DUP(?)
STACK ENDS

DATA SEGMENT
    BUF DB 'S=1+2*3+3*4+4*5+...+N(N+1)+...=','$'  ;buf �洢��ʾ��Ϣ�ַ���
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:STACK
START: 
    MOV AX,DATA
    MOV DS,AX
    MOV DX,0001H
    MOV BL,02H

A1:    
    MOV AL,BL
    INC BL
    MUL BL
    ADD DX,AX    ;������� DX ��
    CMP AX,00C8H ;�ж� N(N+1)�� 200 �Ĵ�С
    JNA A1
    
    MOV AX,DX
    
    CALL pri_str
    CALL dec_out1
    
    MOV AX,4C00H
    INT 21H

; ��������ܴ�ʮ������
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


pri_str proc
    PUSH DX
    PUSH AX
    MOV DX,OFFSET BUF  ;resƫ�Ƶ�ַװ��DX
    ;LEA DX,RES;
    MOV AH,09H
    INT 21H
    POP AX
    POP DX
    ret
pri_str endp

CODE ENDS
    END START
