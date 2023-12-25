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
    COUNT_1 DB 3  ;最大输入次数
    COUNT_2 DW 6  ;密码的个数
    COUNT_3 DW 35 ;班级同学人数
    COUNT_4 DW 68 ;用于记录人数在内存中最后的下标，即COUNT_3*2-2
    COUNT_5 DW 0  ;用于记录不及格的人数
    COUNT_6 DW 3  ;保留3位小数
    COUNT_7 DW ?  ;记录用户输入的密码个数
    PASSWORD DB "111111"
    STRING  DB 20 DUP(0)
    CRLF    DB 0AH,0DH,'$'
    N       DW ?
    NUM     DW 0  ;存储当前字符
    FLAG_1  DB 0  ;0代表不是数字，1代表是数字
    GRADE   DW 35 DUP(0);存储35个学生成绩
    ;GRADE   DW 2,4,3,7
    TEN     DW 10
    SIXTY   DW 60 ;及格分
    INDEX   DW 0
    AVERAGE DW 0
    CHOOSE  DB ?  ;用户输入的选择
DATA ENDS

STACK SEGMENT PARA STACK
	  DW 20H DUP(0)
STACK ENDS


code segment
    assume cs:code, ds:data, ss:stack
;主程序
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


;密码输入与检测
LOP1 PROC
    CMP COUNT_1,0  ;COUNT_1 减 0 ，如果输入了三次错误密码，则结束程序
    JZ  END1       ;=0
    DEC COUNT_1
    MOV SI,0
    MOV BX,COUNT_2 ;设置的密码个数
    MOV COUNT_7,0  ;记录输入的密码个数
    
;初始化，将数组元素置为0
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

;输入密码
INPUTPASSWORD:
    MOV AL,0
    MOV AH,08H
    INT 21H
    CMP AL,0DH;判断是否为回车，是的话说明输入结束
    JZ CHECK
    MOV STRING[SI],AL
    INC SI
    INC COUNT_7
    MOV DL,'*'
    MOV AH,02H
    INT 21H
    JMP INPUTPASSWORD
  
;检测密码输入是否正确
CHECK:
    LEA DX,CRLF;输出换行
    MOV AH,09H
    INT 21H
    MOV CX,COUNT_7
    CMP COUNT_2,CX
    JNZ CONTINUE;密码个数不对，密码错误
    MOV DI,OFFSET STRING
    MOV SI,OFFSET PASSWORD
    CLD
    REPZ CMPSB
    JZ SUCCESS;密码正确
    
CONTINUE:
    MOV DX,OFFSET HINT_2
    MOV AH,09H
    INT 21H
    JMP LOP1
    
;密码错误三次，结束程序	
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

;键盘输入全班同学总成绩
LOP2 PROC
    MOV CX,0
    MOV SI,0
    LEA DX,HINT_6
    MOV AH,09H
    INT 21H
    
INPUT:
    ;CMP CX,0
    ;JZ END2;当输入完35个数字后结束输入
    MOV AH,01H
    INT 21H
    CMP AL,0DH;遇到回车说明一个数据输入完成
    JZ SAVENUM
    ;JZ END2
    CMP AL,' ';遇到空格说明一个数据输入完成
    JZ SAVENUM;
    MOV DL,AL
    MOV DH,0
    PUSH DI
    PUSH DX
    CALL ISDIGITAL
    POP DX
    POP DI
    CMP FLAG_1,0;如果不是数字，则要求重新输入
    JZ INPUT
    ;MOV NUM,0
    MOV N,DX
    SUB N,30H
    MOV AX,NUM
    MUL TEN
    ADD AX,N
    MOV NUM,AX
    JMP INPUT

;存储输入的成绩
SAVENUM:
    INC CX
    MOV BX,NUM
    MOV GRADE[SI],BX
    MOV NUM,0
    ADD SI,2
    CMP AL,0DH;如果输入的是回车，则结束输入
    JZ END2
    JMP INPUT
    
;输入完成
END2:
    MOV COUNT_3,CX
    LEA DX,HINT_7
    MOV AH,09H
    INT 21H
    RET
LOP2 ENDP

;判断输入的是否为数字字符
ISDIGITAL PROC
    MOV BP,SP
    MOV DI,[BP+2]
    
ISBIGGER:;如果0更大的话就跳到非数字
    CMP DI,'0'
    JB NONDIGITAL
    
ISSMALL:;如果9更大的话就跳到数字
    CMP DI,'9'
    JBE DIGITAL
    JMP NONDIGITAL
    
NONDIGITAL:
    MOV FLAG_1,0
    CALL OUTPUTCRLF
    LEA DX,HINT_5
    MOV NUM,0;将缓存的数据清零
    MOV AH,09H
    INT 21H
    RET
    
DIGITAL:
    MOV FLAG_1,1
    RET
ISDIGITAL ENDP

;从高到低排名
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
    
SWAP:;交换
    MOV AX,GRADE[DI+2]
    MOV GRADE[DI],AX
    MOV GRADE[DI+2],BX
    JMP RETURN1
    
OUTPUT_3:;比较结束
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

;输出不及格的人数
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

;不及格人数加1
ACCOUNT:
    INC COUNT_5
    JMP RETURN2

;输出不及格人数
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

;求平均成绩
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
    PUSH DX;保护余数
    PUSH AX
    CALL OUTPUT
    MOV  DX,'.'
    MOV  AH,02H
    INT  21H
    
    MOV  CX,COUNT_6
    POP  AX
    
;小数的处理
DECIMAL:
    MUL  TEN
    CWD
    DIV  COUNT_3
    PUSH DX;保护余数
    PUSH AX;输出商
    CALL OUTPUT
    POP  AX;余数继续乘10再除以除数
    LOOP DECIMAL
    CALL OUTPUTCRLF
    RET
LOP5 ENDP

;二进制转十进制的输出子程序，要将想输出的数据压入栈，改变了AX,DX
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

;输出空格
OUTPUTSPACE PROC
    MOV DX,20H
    MOV AH,02H
    INT 21H
    RET
OUTPUTSPACE ENDP

;输出换行
OUTPUTCRLF PROC
    LEA DX,CRLF
    MOV AH,09H
    INT 21H
    RET
OUTPUTCRLF ENDP

code ends
    end START

