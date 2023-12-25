
; �س�����10���ɼ�������ÿ���ɼ����������

CRLF MACRO
    MOV DL, 0DH
    MOV AH, 02H  ;�س�
    INT 21H
    MOV DL, 0AH
    MOV AH, 02H  ;����
    INT 21H
ENDM

DATA SEGMENT
    STUNUM EQU 10
    MESS   DB 'INPUT 10 STUDENTS SCORE: ',0DH,0AH,'$';��ʾ����10λͬѧ�ĳɼ�
    ERROR  DB 'INPUT ERROR!',0DH,0AH,'$';��ʾ�������
    ORG    1000H
    SCORE  DB 10 DUP (?)   ;�ɼ�
    ORG    2000H
    SEQU   DB 10 DUP (?)
DATA ENDS

STACK SEGMENT STACK
    STA DW 12 DUP (?)
    TOP DW ?
STACK ENDS

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA,ES:DATA,SS:STACK
START:
    MOV AX, DATA
    MOV DS, AX
    MOV ES, AX
    MOV SP, TOP         ; ��ʼ��
    MOV DX, OFFSET MESS
    MOV AH, 09H
    INT 21H             ; ��ʾ��ʾ������Ϣ
    MOV SI, OFFSET SCORE; �ɼ�����ַ
    MOV CX, STUNUM      ; ѧ������CX
UUU: 
    CALL GETNUM         ; ��ȡ������ֵ��DX
    MOV [SI], DL        ; ����ɼ�������
    INC SI              ; ָ����һ��Ԫ
    LOOP UUU
    MOV CX, STUNUM      ; ѧ����
    MOV DI, OFFSET SEQU ; ���α���ַ
VVV: 
    CALL SCAN           ; ɨ���ӳ���
    MOV AL, STUNUM      ; ѧ����
    SUB AL, CL
    INC AL              ; ��������
    MOV BX, DX 
    MOV [DI+BX], AL     ; ��DXѧ�Ŷ�Ӧ����
    LOOP VVV
    MOV CX, STUNUM      ; ѧ����
    MOV SI, OFFSET SEQU ; ���α���ַ
WWW: 
    MOV AL, [SI]
    CALL DISP1
    CRLF
    INC SI
    LOOP WWW      ;��ʾ�Ŷ���ѧ������
    MOV AX, 4C00H
    INT 21H

SCAN PROC NEAR
;�ӳ���,ÿɨ��һ��ɼ�������, �ҳ����гɼ��������DXָ��ָʾ��Ӧѧ��֮�󽫸óɼ�������Ա���һ��ɨ��
    PUSH CX
    MOV CX, STUNUM;ѧ����
    MOV AL, 00H   ;��ͳɼ�
    MOV BX, OFFSET SCORE
    MOV SI, BX    ;ָ��ɼ�����ַ
CCC: 
    CMP AL, [SI]
    JAE JJJ       ;AL�еĳɼ������ڳɼ���ָ��SI��ָ��Ԫ�ĳɼ���תJJJ
    MOV AL, [SI]  ;AL��Žϸߵĳɼ�
    MOV DX, SI 
    SUB DX, BX    ;DXΪ��Ӧѧ��
JJJ:
    INC  SI       ;ָ����һ��Ԫ
    LOOP CCC
    ADD  BX, DX
    MOV  BYTE PTR[BX], 00H;����ɨ��ɼ��������0
    POP  CX
    RET
SCAN ENDP

DISP1 PROC NEAR
    PUSH CX
    MOV  BL, AL
    MOV  DL, BL
    MOV  CL, 04
    ROL  DL, CL
    AND  DL, 0FH
    CALL DISPL
    MOV  DL, BL
    AND  DL, 0FH
    CALL DISPL
    POP CX
    RET
DISP1 ENDP

DISPL PROC NEAR 
    JMP DDD2      ;��������ת��DDD2
DDD2:
    MOV AL,DL     ;��dl�е�ֵ���ݸ�al
    CBW           ;�ӳ��򴫵ݲ�����ax����al�ַ���չ��ax
    CALL EXCHANGE ;�����ӳ���16����ת��Ϊ10����
    RET

EXCHANGE PROC
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX
    XOR CX,CX
    CMP AX,0
    JNE L1     ;ax��Ϊ0
    ADD AX,'0' ;axΪ0ʱ���⴦��
    PUSH AX
    MOV AX,0
    MOV CX,1
L1:
    MOV BL,AL;
    ADD BL,AH
    CMP BL,0
    JNE L2;��10ȡ������Ϊ0
    JMP L3
L2:
    MOV DL,10
    DIV DL;��10���ౣ��
    MOV BX,0
    MOV BL,AH
    ADD BL,'0'
    PUSH BX;λ����1
    INC CX;����Ϊ����������ѭ��
    MOV AH,0
    JMP L1
L3:
    POP DX;Ϊ0����
    MOV AH,2
    INT 21H
    LOOP L3
    POP DX
    POP CX
    POP BX
    POP AX
    JMP EXIT
EXIT:
    RET
EXCHANGE ENDP

DISPL ENDP

GETNUM PROC NEAR
PUSH CX
XOR DX, DX
GGG: 
    MOV AH, 01H
    INT 21H
    CMP AL, 0DH
    JZ PPP
    CMP AL, 20H
    JZ PPP
    SUB AL, 30H
    JB KKK
    CMP AL, 0AH
    JB GETS
    CMP AL, 11H
    JB KKK
    SUB AL, 07H
    CMP AL, 0FH
    JBE GETS
    CMP AL, 2AH
    JB KKK
    CMP AL, 2FH
    JA KKK
    SUB AL, 20H
GETS:
    MOV CL, 04
    SHL DX, CL
    XOR AH, AH
    ADD DX, AX
    JMP GGG
KKK:
    MOV AH, 09H
    MOV DX, OFFSET ERROR
    INT 21H
PPP:
    PUSH DX 
    CRLF
    POP DX
    POP CX
    RET
GETNUM ENDP

CODE ENDS
    END START
