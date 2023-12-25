
; 输出各段多少人： 1 2 1 4 1 1
DATA SEGMENT
    GRADE DW 56,69,84,82,73,88,99,63,100,80 
    S5    DW 0 
    S6    DW 0 
    S7    DW 0 
    S8    DW 0 
    S9    DW 0 
    S10   DW 0 
DATA ENDS

STACK SEGMENT PARA STACK 'stack'
    DB 1024 DUP(0)
STACK ENDS

CODE SEGMENT

MAIN PROC FAR
    ASSUME CS:CODE, DS:DATA, SS:STACK
START:
    PUSH DS
    SUB  AX , AX
    PUSH AX
    
    MOV  AX , DATA
    MOV  DS , AX
    
    MOV  S5 , 0
    MOV  S6 , 0 
    MOV  S7 , 0 
    MOV  S8 , 0 
    MOV  S9 , 0 
    MOV  S10, 0 
    
    MOV  CX , 10
    
    MOV  BX , OFFSET GRADE
COMPARE:
    MOV AX,[BX]
    CMP AX, 60  ; <60? 
    JL  FIVE
    CMP AX, 70  ; <70? 
    JL  SIX
    CMP AX, 80  ; <80? 
    JL  SEVEN
    CMP AX, 90  ; <90? 
    JL  EIGHT
    CMP AX, 100 ; =100? 
    JNE NINE
    INC S10
    JMP SHORT CHANGE_ADDR
NINE: 
    INC S9
    JMP SHORT CHANGE_ADDR
EIGHT: 
    INC S8
    JMP SHORT CHANGE_ADDR
SEVEN: 
    INC S7
    JMP SHORT CHANGE_ADDR
SIX:
    INC S6
    JMP SHORT CHANGE_ADDR 
FIVE: 
    INC S5

CHANGE_ADDR:
    ADD  BX, 2 
    LOOP COMPARE 
    MOV  CX,6         ;设置6个成绩阶段
    MOV  SI,OFFSET S5 ;从S5开始输出
    
AGAIN:
    MOV  DX,[SI]
    ADD  DX,30H   ;将数字转化为字符
    MOV  AH,02    ;调用02号ah输出字符
    INT  21H
    
    MOV  DL,20H   ;在屏幕上显示空格（20h）
    MOV  AH,02    ;调用02号ah输出字符
    INT  21H
    
    ADD  SI,2     ;一个Sx是dw类型，占据两个字节
    LOOP AGAIN
    
    RET
MAIN ENDP

CODE ENDS
    END START
