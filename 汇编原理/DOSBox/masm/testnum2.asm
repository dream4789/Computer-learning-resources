; ���16���ƣ�ԭ�����AX���
STACK SEGMENT STACK
    DW 64 DUP(?)
STACK ENDS

DATAS segment
    Temp db '0000H','$'
DATAS ends

CODES segment
    ASSUME CS:CODES, DS:DATAS, SS:STACK
START:
    mov AX,DATAS
    mov DS,AX

    ;mov AX,12ABH        ;������Ҫ��ʾ��AX��ֵ
    mov AX,5050          ;���13BA
    
    
    ;call symoutput
    call dec_out1        ; ��������ܴ����
    
    mov ah,4CH
    int 21H

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


;�޷���ʮ�������
symoutput proc
    mov si,offset Temp+3;����洢������ַ��������һ���ַ�ƫ�Ƶ�ַ
    xor cx,cx           ;��cX����
    mov cl,4            ;����ѭ������Ϊ4��

MainPart:
    mov DH,AL           ;��Al�����ݴ��͸�DH

    shr AX,1
    shr AX,1
    shr AX,1
    shr AX,1
                ;����4��ΪʹAX�߼�����4λ �����Ͽ���д�� shr AX ,cl(cl����Ϊ4)
                ;������ط�clҪ��¼ѭ������ÿ��ѭ������cl-1�����޷�������������λ��Ҫ
    and dh,0FH
    add dh,30H
    cmp dh,':'  ;':'��ASCII��9��1 ����ĸ��ASCII�������ֵ�ASCII���м����7�������ַ�
    ja isLetter ;���Ϊ��ĸ����ת
    jb No       ;�������

isLetter:
    add dh,7H   ;ASCII���7��Ϊ��ĸ
    
No:
    mov [si],dh ;���ַ�����,��������ݵ��ַ����Ķ�Ӧλ��
    dec si      ;��������ݵ��ڴ��ַ�Լ�1
    loop MainPart

print:
    mov dx,offset Temp  ;������ӡ���ַ�����ƫ�Ƶ�ַ��Ž�dx��
    mov ah,09           ;����DOS 09�Ź���
    int 21H         ;���ܵ���
    mov al,0
    
    ret
symoutput endp


CODES ends
    end START