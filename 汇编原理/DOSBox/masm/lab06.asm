; S=1+2*3+3*4+4*5+...+N(N+1)+...=045F 16�������
STACK SEGMENT PARA STACK 'stack'
    DB 1024 DUP(0)
STACK ENDS

DATA SEGMENT
    BUF DB 'S=1+2*3+3*4+4*5+...+N(N+1)+...=','$'  ;buf �洢��ʾ��Ϣ�ַ���
    RES DB 4 DUP(0),'$'    ;res��λ �洢�����asii�룬$�������ַ���
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:STACK ;αָ��
START: 
    MOV AX,DATA
    MOV DS,AX          ;װ�����μĴ���

    ;MOV DX,OFFSET BUF ;BUF��������Ч��ַװ��DX
    LEA DX,BUF         ;BUF��������Ч��ַװ��DX
    MOV AH,09H         ;����ַ���
    INT 21H

    MOV DX,1
    MOV BL,2

NEXT: 
    MOV AL,BL
    INC BL
    MUL BL       ;AL * BL -> AX (2*3,3*4...)
    ADD DX,AX    ;AX + DX -> DX
    CMP AX,200   ;��N(N+1)�˻���200�Ƚ�
    JNA NEXT     ;������200

    MOV CX,0004H ;(CX)=4��װ��cx��ѭ����������������������ֱ�ת��Ϊasii��
    MOV DI,OFFSET RES
    ADD DI,03H   ;DI���ݼ�������Ϊ�ȴ������λ��ת����ɺ���뵽res+3�ֽ�

NEXT1: 
    MOV AX,DX
    AND AX,000FH ;AX��0000 0000 0000 1111B�����߼������㣬Ŀ��������λ���㣬��������λ
    CMP AL,0AH  ;AL��10�Ƚ�
    JB  NEXT2   ;��С��10��ֱ������next2���
    ADD AL,07H  ;�����7У��

NEXT2: 
    ADD AL,30H  ;AL��30Hת��ΪASII��
    MOV [DI],AL ;ת����ɺ����DI��ǰָ��Ĵ洢��Ԫ
    DEC DI      ;�����DI��һ����Ϊ��һѭ�����̽��������һ�ֽ�

    PUSH CX     ;����CX����
    MOV CL,04   ;װ��CL��Ϊ4��Ϊ��λ����
    SHR DX,CL   ;ѭ������4�Σ�������λ�Ƴ�����λ����
    POP CX      ;��ԭcx������

    LOOP NEXT1  ;cx-1

    MOV DX,OFFSET RES  ;resƫ�Ƶ�ַװ��DX
    MOV AH,09H
    INT 21H     ;����ַ���

    MOV AH,4CH
    INT 21H
    
CODE ENDS
    END START
