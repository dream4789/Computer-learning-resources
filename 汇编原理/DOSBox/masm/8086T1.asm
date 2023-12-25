;====================================================================
; Main.asm file generated by New Project wizard
;
; Created:   
; Processor: 8086
; Compiler:  MASM32
;
; Before starting simulation set Internal Memory Size 
; in the 8086 model properties to 0x10000
;====================================================================

CODE    SEGMENT PUBLIC 'CODE'
ASSUME CS:CODE,DS:DATA,SS:STACK
ORG 100H;避开中断向量表
START:
  ; Write your code here
  MOV AX,DATA;数据段
  MOV DS,AX
  MOV AX,STACK;堆栈段
  MOV SS,AX
  MOV AX,TOP
  MOV SP,AX
  CLI
  ;设置中断向量INT7（优先级比INT6低，等INT6执行完，IRR置1，IMR=0允许中断）
  PUSH DS
  MOV AX,0
  MOV DS,AX
  MOV BX,156;27H*4
  MOV AX,OFFSET INT7
  MOV [BX],AX
  MOV AX,0
  MOV [BX+2],AX
  POP DS
  ;修改  
  ;设置中断向量INT6（优先级高，IRR先置1）
  PUSH DS
  MOV AX,0
  MOV DS,AX
  MOV BX,26H*4;26H*4(8086根据中断类型码26H，找到中断IR6中断向量在中断向量表的位置，类似于26H左移两位，IMR=0允许中断)
  MOV AX,OFFSET INT6
  MOV [BX],AX 
  MOV AX,0
  MOV [BX+2],AX
  POP DS
  
  ;8259初始化（初始化之后8259进入就绪状态）
  MOV DX,CS8259A ;写ICW1（写入偶地址端口A0=0，接入A0的是A1）
  MOV AL,ICW1
  OUT DX,AL
  MOV DX,CS8259B ;写ICW2（写入奇地址端口A0=1，接入A0的是A1）
  MOV AL,ICW2
  OUT DX,AL
  MOV AL,ICW4;写ICW4
  OUT DX,AL
  MOV AL,OCW1;写OCW1（普通屏蔽方式，写入奇地址端口）
  OUT DX,AL
  STI        ;开中断
  
  ;8255初始化
  MOV AL,80H; 1000 0000B,1000A口输出，工作方式0，0000B口输出，工作方式0，C端口输出
  MOV DX,CT_PORT
  OUT DX,AL
  MOV AL,00
  MOV DX,A_PORT
  OUT DX,AL
  
  ;8253初始化（8253是定时用，通过写入计数初值实现软件定时，时钟输入频率是1MHZ（通过计数器0和计数器1级联实现）周期为1s）
  MOV DX,CTL;0号计数器写入控制字
  MOV AL,00110110B;00：0号计数器，11：16位（先写低八位再写高八位），011：工作方式3（方波发生器），0：二进制计数
  OUT DX,AL
  MOV DX,CNT0;0号计数器写入初值1000
  MOV AX,1000;先写低八位再写高八位
  OUT DX,AL
  MOV AL,AH
  OUT DX,AL
  MOV DX,CTL;1号计数器写入控制字
  MOV AL,01110110B;1号计数器16位工作方式3（方波发生器）二进制计数
  OUT DX,AL
  MOV DX,CNT1;1号计数器写入初值1000
  MOV AX,1000;先写低八位再写高八位
  OUT DX,AL
  MOV AL,AH
  OUT DX,AL

LP:     NOP ;主程序
  STI
  JMP LP
  ;修改（普通中断优先级高于IR7）
INT6:   CLI
  PUSH AX ;IR6中断服务子程序
  PUSH BX
  PUSH CX
  PUSH DX
  STI
  MOV DX,A_PORT
  MOV AL,00001001B ;B道红灯，A道红灯（B黄绿红 A黄绿红）
  OUT DX,AL
  MOV CX,5;通过延时子程序延时5s

NEXT:   LEA BX,TAB
  ADD BX,CX
  MOV AL,[BX]
  MOV DX,B_PORT
  OUT DX,AL
  LEA BX,TAB
  ADD BX,CX
  MOV AL,[BX]
  MOV DX,C_PORT
  OUT DX,AL
  CALL DELAY100;延时子程序
  LOOP NEXT
  MOV DX,CS8259A ;中断服务子程序结束指令
  MOV AL,20H
  OUT DX,AL
  CLI
  POP DX
  POP CX
  POP BX
  POP AX
  OUT DX,AL ;将进入中断时信号灯情况进行恢复
  STI
  IRET;中断返回，中断结束之前将ISR6置0

;延时子程序
DELAY100 PROC
  PUSH CX
  MOV CX,0
  LOOP $
  LOOP $
  LOOP $
  MOV CX,15000
  LOOP $
  POP CX
  RET
DELAY100 ENDP

INT7:   CLI  
  PUSH AX
  PUSH BX
  PUSH CX
  PUSH DX
  MOV CX,FLAG
  CMP CX,0
  JG B0
  MOV FLAG,20;一个循环周期设为20s

B0:     DEC FLAG
  CMP CX,10
  JAE A0   ;>10-A道
  CMP CX,3
  JBE B1  ;<3--B道黄灯亮，A道红灯亮
  ;B道绿灯亮，A道红灯亮
  MOV AL,00010001B;B黄绿红 A黄绿红
  MOV DX,A_PORT
  OUT DX,AL
  JMP LEDB

B1:     ;B道黄灯亮，A道红灯亮
  MOV AL,00100001B;B黄绿红 A黄绿红
  MOV DX,A_PORT
  OUT DX,AL
  LEA BX,TAB
  ADD BX,CX
  MOV AL,[BX]
  MOV DX,C_PORT
  OUT DX,AL
  MOV DX,B_PORT
  OUT DX,AL
  JMP EXIT

LEDB:   LEA BX,TAB
  ADD BX,CX
  MOV AL,[BX]
  MOV DX,B_PORT
  OUT DX,AL
  LEA BX,TAB
  ADD BX,CX
  MOV AL,[BX]
  MOV DX,C_PORT
  OUT DX,AL
  JMP EXIT

A0:     SUB CX,10
  CMP CX,3
  JBE A1;<=3,A道黄灯亮，B道红灯亮
  ;A道绿灯亮，B道红灯亮
  MOV AL,00001010B;B黄绿红 A黄绿红
  MOV DX,A_PORT
  OUT DX,AL
  JMP LEDA

A1:     ;A道黄灯亮，B道红灯亮
  MOV AL,00001100B;B黄绿红 A黄绿红
  MOV DX,A_PORT
  OUT DX,AL
  LEA BX,TAB
  ADD BX,CX
  MOV AL,[BX]
  MOV DX,C_PORT
  OUT DX,AL
  MOV DX,B_PORT
  OUT DX,AL
  JMP EXIT

LEDA:   LEA BX,TAB
  ADD BX,CX
  MOV AL,[BX]
  MOV DX,C_PORT
  OUT DX,AL
  LEA BX,TAB
  ADD BX,CX
  MOV AL,[BX]
  MOV DX,B_PORT
  OUT DX,AL

EXIT:   MOV DX,CS8259A;中断服务子程序结束指令
MOV AL,20H
OUT DX,AL
CLI
POP DX
POP CX
POP BX
POP AX
STI
IRET;中断返回，中断结束之前将ISR7置0
CODE    ENDS

DATA SEGMENT
;Y0--8259（8位）
CS8259A EQU 8000H;1000 0000 0000 0000B,偶地址A0是0
CS8259B EQU 8002H;1000 0000 0000 0010B,奇地址A0是1
ICW1 EQU 00010011B
ICW2 EQU 00100000B
ICW4 EQU 00000001B
OCW1 EQU 00111111B;OCW1控制字开中断IR7和IR6（OCW1是普通屏蔽方式）
;Y1--8253（写入计数初值是软件启动）
CNT0 EQU 9000H;A15……A0：1001 0000 0000 0000，9000H（计数器0）
CNT1 EQU 9002H;A15……A0：1001 0000 0000 0010，9000H（计数器1）
CNT2 EQU 9004H;A15……A0：1001 0000 0000 0100，9004H（计数器2）
CTL  EQU 9006H;A15……A0：1001 0000 0000 0000，9006H（控制字）
;Y2--8255，10000000B,1000：A口输出，工作方式0，0000：B口输出，工作方式0，C端口输出
A_PORT EQU 0A000H;A19……A2A1A0：0000 1010 0000 0000 0000（A口输出A道红绿灯）
B_PORT EQU 0A002H;A19……A2A1A0：0000 1010 0000 0000 0010（B口输出B道红绿灯）
C_PORT EQU 0A004H;A19……A2A1A0：0000 1010 0000 0000 0100（C口输出显示数码管）
CT_PORT EQU 0A006H;A19……A2A1A0：0000 1010 0000 0000 0110（控制字）
FLAG DW 20  ;A+B道总循环秒数
;7seg（7段数码表）
TAB DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,67H,77H,7CH,39H,5EH,79H,71H
DATA ENDS
STACK SEGMENT STACK
STA DB 512 DUP(0FFH)
TOP EQU $-STA
STACK ENDS
END START