
; 回车输入10个成绩，给出每个成绩的排名序号

CRLF MACRO
    MOV DL, 0DH
    MOV AH, 02H  ;回车
    INT 21H
    MOV DL, 0AH
    MOV AH, 02H  ;换行
    INT 21H
ENDM

DATA SEGMENT
    STUNUM EQU 10
    MESS   DB 'INPUT 10 STUDENTS SCORE: ',0DH,0AH,'$';提示输入10位同学的成绩
    ERROR  DB 'INPUT ERROR!',0DH,0AH,'$';提示输入错误
    ORG    1000H
    SCORE  DB 10 DUP (?)   ;成绩
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
    MOV SP, TOP         ; 初始化
    MOV DX, OFFSET MESS
    MOV AH, 09H
    INT 21H             ; 显示提示输入信息
    MOV SI, OFFSET SCORE; 成绩表首址
    MOV CX, STUNUM      ; 学生数送CX
UUU: 
    CALL GETNUM         ; 读取键入数值送DX
    MOV [SI], DL        ; 存入成绩表缓冲区
    INC SI              ; 指向下一单元
    LOOP UUU
    MOV CX, STUNUM      ; 学生数
    MOV DI, OFFSET SEQU ; 名次表首址
VVV: 
    CALL SCAN           ; 扫描子程序
    MOV AL, STUNUM      ; 学生数
    SUB AL, CL
    INC AL              ; 计算名次
    MOV BX, DX 
    MOV [DI+BX], AL     ; 记DX学号对应名次
    LOOP VVV
    MOV CX, STUNUM      ; 学生数
    MOV SI, OFFSET SEQU ; 名次表首址
WWW: 
    MOV AL, [SI]
    CALL DISP1
    CRLF
    INC SI
    LOOP WWW      ;显示排定的学生名次
    MOV AX, 4C00H
    INT 21H

SCAN PROC NEAR
;子程序,每扫描一遍成绩表缓冲区, 找出其中成绩最高者由DX指针指示对应学生之后将该成绩清除，以便下一次扫描
    PUSH CX
    MOV CX, STUNUM;学生数
    MOV AL, 00H   ;最低成绩
    MOV BX, OFFSET SCORE
    MOV SI, BX    ;指向成绩表首址
CCC: 
    CMP AL, [SI]
    JAE JJJ       ;AL中的成绩不低于成绩表指针SI所指单元的成绩则转JJJ
    MOV AL, [SI]  ;AL存放较高的成绩
    MOV DX, SI 
    SUB DX, BX    ;DX为对应学号
JJJ:
    INC  SI       ;指向下一单元
    LOOP CCC
    ADD  BX, DX
    MOV  BYTE PTR[BX], 00H;本次扫描成绩最高者清0
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
    JMP DDD2      ;将程序跳转到DDD2
DDD2:
    MOV AL,DL     ;将dl中的值传递给al
    CBW           ;子程序传递参数是ax，将al字符扩展到ax
    CALL EXCHANGE ;调用子程序将16进制转化为10进制
    RET

EXCHANGE PROC
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX
    XOR CX,CX
    CMP AX,0
    JNE L1     ;ax不为0
    ADD AX,'0' ;ax为0时特殊处理
    PUSH AX
    MOV AX,0
    MOV CX,1
L1:
    MOV BL,AL;
    ADD BL,AH
    CMP BL,0
    JNE L2;除10取余数不为0
    JMP L3
L2:
    MOV DL,10
    DIV DL;除10求余保存
    MOV BX,0
    MOV BL,AH
    ADD BL,'0'
    PUSH BX;位数加1
    INC CX;商作为被除数继续循环
    MOV AH,0
    JMP L1
L3:
    POP DX;为0跳出
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
