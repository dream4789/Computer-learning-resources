DATA SEGMENT
    HINT_1  DB "please input password:",0AH,0DH,'$'
    HINT_2  DB "password wrong !",0AH,0DH,'$'
    HINT_3  DB "three times !",0AH,0DH,'$'
    HINT_4  DB "password success !",0AH,0DH,'$'
    HINT_5  DB "error,please input a number !",0AH,0DH,'$'
    HINT_6  DB "please input the grade:",0AH,0DH,'$'
    HINT_7  DB "GRADE SUCCESS !",0AH,0DH,'$'
    HINT_8  DB "number of failed:",0AH,0DH,'$'
    HINT_9  DB "the average grade is:",0AH,0DH,'$'
    HINT_10 DB "PLEASE CHOOSE:",0AH,0DH,"3.SORT",0AH,0DH,"4.FAILED",0AH,0DH,"5.AVERAGE",0AH,0DH,"6.EXIT",0AH,0DH,'$'
    COUNT_1 DB 3  ;����������
    COUNT_2 DW 6  ;����ĸ���
    COUNT_3 DW 35 ;�༶ͬѧ����
    COUNT_4 DW 68 ;���ڼ�¼�������ڴ��������±꣬��COUNT_3*2-2
    COUNT_5 DW 0  ;���ڼ�¼�����������
    COUNT_6 DW 3  ;����3λС��
    COUNT_7 DW ?  ;��¼�û�������������
    PASSWORD DB "111111"
    STRING  DB 20 DUP(0)
    CRLF    DB 0AH,0DH,'$'
    N       DW ?
    NUM     DW 0  ;�洢��ǰ�ַ�
    FLAG_1  DB 0  ;0���������֣�1����������
    GRADE   DW 35 DUP(0);�洢35��ѧ���ɼ�
    ;GRADE   DW 2,4,3,7
    TEN     DW 10
    SIXTY   DW 60 ;�����
    INDEX   DW 0
    AVERAGE DW 0
    CHOOSE  DB ?  ;�û������ѡ��
DATA ENDS

STACK SEGMENT PARA STACK
	  DW 20H DUP(0)
STACK ENDS


code segment
    assume cs:code, ds:data, ss:stack
;������
START:
    CALL LOP1
    CALL LOP2
    LEA  DX,HINT_10
    MOV  AH,09H
    INT  21H
    
SETCHOOSE:
    MOV AH,01H
    INT 21H
    MOV CHOOSE,AL
    CALL OUTPUTCRLF
    CMP CHOOSE,'3'
    JZ  CALL3
    CMP CHOOSE,'4'
    JZ  CALL4
    CMP CHOOSE,'5'
    JZ  CALL5
    CMP CHOOSE,'6'
    JZ  ENDMAIN
    JNZ SETCHOOSE
CALL3:
  	CALL LOP3
  	JMP  SETCHOOSE
CALL4:
  	CALL LOP4
  	JMP  SETCHOOSE
CALL5:
  	CALL LOP5
  	JMP  SETCHOOSE
ENDMAIN:
    MOV AH,4CH
    INT 21H


;������������
LOP1 PROC
    CMP COUNT_1,0  ;COUNT_1 �� 0 ��������������δ������룬���������
    JZ  END1       ;=0
    DEC COUNT_1
    MOV SI,0
    MOV BX,COUNT_2 ;���õ��������
    MOV COUNT_7,0  ;��¼������������
    
;��ʼ����������Ԫ����Ϊ0
INITIAL:
    MOV STRING[SI],0
    INC SI
    DEC BX
    CMP BX,0
    JNZ INITIAL
    MOV SI,0
    MOV DX,OFFSET HINT_1
    MOV AH,09H
    INT 21H

;��������
INPUTPASSWORD:
    MOV AL,0
    MOV AH,08H
    INT 21H
    CMP AL,0DH;�ж��Ƿ�Ϊ�س����ǵĻ�˵���������
    JZ CHECK
    MOV STRING[SI],AL
    INC SI
    INC COUNT_7
    MOV DL,'*'
    MOV AH,02H
    INT 21H
    JMP INPUTPASSWORD
  
;������������Ƿ���ȷ
CHECK:
    LEA DX,CRLF;�������
    MOV AH,09H
    INT 21H
    MOV CX,COUNT_7
    CMP COUNT_2,CX
    JNZ CONTINUE;����������ԣ��������
    MOV DI,OFFSET STRING
    MOV SI,OFFSET PASSWORD
    CLD
    REPZ CMPSB
    JZ SUCCESS;������ȷ
    
CONTINUE:
    MOV DX,OFFSET HINT_2
    MOV AH,09H
    INT 21H
    JMP LOP1
    
;����������Σ���������	
END1:
    MOV DX,OFFSET HINT_3
    MOV AH,09H
    INT 21H
    MOV AH,4CH
    INT 21H
    
SUCCESS:
    LEA DX,HINT_4
    MOV AH,09H
    INT 21H
    RET
LOP1 ENDP

;��������ȫ��ͬѧ�ܳɼ�
LOP2 PROC
    MOV CX,0
    MOV SI,0
    LEA DX,HINT_6
    MOV AH,09H
    INT 21H
    
INPUT:
    ;CMP CX,0
    ;JZ END2;��������35�����ֺ��������
    MOV AH,01H
    INT 21H
    CMP AL,0DH;�����س�˵��һ�������������
    JZ SAVENUM
    ;JZ END2
    CMP AL,' ';�����ո�˵��һ�������������
    JZ SAVENUM;
    MOV DL,AL
    MOV DH,0
    PUSH DI
    PUSH DX
    CALL ISDIGITAL
    POP DX
    POP DI
    CMP FLAG_1,0;����������֣���Ҫ����������
    JZ INPUT
    ;MOV NUM,0
    MOV N,DX
    SUB N,30H
    MOV AX,NUM
    MUL TEN
    ADD AX,N
    MOV NUM,AX
    JMP INPUT

;�洢����ĳɼ�
SAVENUM:
    INC CX
    MOV BX,NUM
    MOV GRADE[SI],BX
    MOV NUM,0
    ADD SI,2
    CMP AL,0DH;���������ǻس������������
    JZ END2
    JMP INPUT
    
;�������
END2:
    MOV COUNT_3,CX
    LEA DX,HINT_7
    MOV AH,09H
    INT 21H
    RET
LOP2 ENDP

;�ж�������Ƿ�Ϊ�����ַ�
ISDIGITAL PROC
    MOV BP,SP
    MOV DI,[BP+2]
    
ISBIGGER:;���0����Ļ�������������
    CMP DI,'0'
    JB NONDIGITAL
    
ISSMALL:;���9����Ļ�����������
    CMP DI,'9'
    JBE DIGITAL
    JMP NONDIGITAL
    
NONDIGITAL:
    MOV FLAG_1,0
    CALL OUTPUTCRLF
    LEA DX,HINT_5
    MOV NUM,0;���������������
    MOV AH,09H
    INT 21H
    RET
    
DIGITAL:
    MOV FLAG_1,1
    RET
ISDIGITAL ENDP

;�Ӹߵ�������
LOP3 PROC
    MOV CX,0
    
FIRST:
    MOV DI,0
    INC CX
    CMP CX,COUNT_3
    JZ OUTPUT_3
    
COMPARE:
    MOV BX,GRADE[DI]
    CMP BX,GRADE[DI+2]
    JB SWAP
    
RETURN1:
    ADD DI,2
    CMP COUNT_4,DI
    JZ FIRST
    JMP COMPARE
    
SWAP:;����
    MOV AX,GRADE[DI+2]
    MOV GRADE[DI],AX
    MOV GRADE[DI+2],BX
    JMP RETURN1
    
OUTPUT_3:;�ȽϽ���
    MOV CX,COUNT_3
    MOV SI,0
    
OUTPUT0:
  	MOV AX,GRADE[SI]
  	PUSH AX
  	CALL OUTPUT
  	CALL OUTPUTSPACE
  	ADD SI,2
  	DEC CX
  	CMP CX,0
  	JNZ OUTPUT0
    CALL OUTPUTCRLF
    RET
LOP3 ENDP

;��������������
LOP4 PROC
    MOV COUNT_5,0
    MOV SI,0
    MOV CX,0
    
COMPARE2:
    MOV BX,SIXTY
    CMP GRADE[SI],BX
    JB ACCOUNT
    
RETURN2:
    ADD SI,2
    INC CX
    CMP CX,COUNT_3
    JNZ COMPARE2
    JZ END4

;������������1
ACCOUNT:
    INC COUNT_5
    JMP RETURN2

;�������������
END4:
    LEA DX,HINT_8
    MOV AH,09H
    INT 21H
    MOV AX,COUNT_5
    PUSH AX
    CALL OUTPUT
    CALL OUTPUTCRLF
    RET
LOP4 ENDP

;��ƽ���ɼ�
LOP5 PROC	
    MOV SI,0
    MOV CX,COUNT_3
    DEC CX
    MOV BX,GRADE[SI]
    ADD AVERAGE,BX
    ADDSUM:
    ADD SI,2
    MOV BX,GRADE[SI]
    ADC AVERAGE,BX
    LOOP ADDSUM
    LEA DX,HINT_9
    MOV AH,09H
    INT 21H
    MOV AX,AVERAGE
    CWD
    DIV  COUNT_3
    PUSH DX;��������
    PUSH AX
    CALL OUTPUT
    MOV  DX,'.'
    MOV  AH,02H
    INT  21H
    
    MOV  CX,COUNT_6
    POP  AX
    
;С���Ĵ���
DECIMAL:
    MUL  TEN
    CWD
    DIV  COUNT_3
    PUSH DX;��������
    PUSH AX;�����
    CALL OUTPUT
    POP  AX;����������10�ٳ��Գ���
    LOOP DECIMAL
    CALL OUTPUTCRLF
    RET
LOP5 ENDP

;������תʮ���Ƶ�����ӳ���Ҫ�������������ѹ��ջ���ı���AX,DX
OUTPUT PROC
    MOV BP,SP
    MOV AX,[BP+2]
    MOV INDEX,0
OUTPUT2:
    CWD
    DIV  TEN
    ADD  DX,30H
    PUSH DX
    INC INDEX
    CMP AX,0
    JZ  OUTPUT3
    JMP OUTPUT2
OUTPUT3:
    CMP INDEX,0
    JZ  OUTPUTEND
    POP DX
    MOV AH,02H
    INT 21H
    DEC INDEX
    JMP OUTPUT3
OUTPUTEND:
    RET 2
OUTPUT ENDP

;����ո�
OUTPUTSPACE PROC
    MOV DX,20H
    MOV AH,02H
    INT 21H
    RET
OUTPUTSPACE ENDP

;�������
OUTPUTCRLF PROC
    LEA DX,CRLF
    MOV AH,09H
    INT 21H
    RET
OUTPUTCRLF ENDP

code ends
    end START

