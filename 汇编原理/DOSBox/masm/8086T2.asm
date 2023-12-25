;------------------------------------------------------------------
;Function: (tip:配套SCNU微机原理实验箱)
;微机原理红绿灯设计，按下12号按键启动系统，东西方向和南北方向交替通行，
;为一般红绿灯规律，红绿两灯的时间设置范围为6~99（可自己修改），黄灯时间设置范围为2~5S（可自己修改）
;按键对应功能：矩阵键盘，对应原理图看
;---------------------------------------------------------------------------
;-  (东西南北禁止通行)           (恢复正常)                    (东西禁止通行)         (南北禁止通行)
;y  (设置时间启动)               (设置红灯时间)                (设置绿灯时间)         (设置黄灯时间)
;轴 (选择设置哪种灯后按下则增加1)(选择设置哪种灯后按下则减少1) (结束选中设定时间的灯) (设置时间结束，恢复计时)
;-  ()                           ()                            ()                     (启动系统)
;-------------------------------------x轴-----------------------------------
DATA	SEGMENT		;数据段		
      ;此处输入数据段
      LED DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,6FH,77H,7CH,39H,5EH,79H,71H
          
      IOY0 EQU  0600H;8255地址，对应IOY0
      IOY1 EQU  0640H;8254地址，对应IOY1
      IOY2 EQU  0650H;仿真用于8259，试验箱不用
      PORTA EQU IOY0
      PORTB EQU IOY0+02H
      PORTC EQU IOY0+04H
      CS8255 EQU IOY0+06H
      ; A口工作方式0 输入  B口工作方式0 输入 
      REGIS EQU 88H;AB口方式0，全为输出，C口高四位输入，低四位输出 
      
      CS8253 EQU IOY1+06H
      TRANAL0 EQU IOY1
      TRANAL1 EQU IOY1+02H
      
      
      ICW1 EQU  20H;0620H
      
      ICW2 EQU 21H;0622H
      ICW3 EQU 21H;0622H
      ICW4 EQU 21H;0622H 
      
      OCW1 EQU 21H;0622H
      OCW2 EQU 20H;0620H
      OCW3 EQU 20H;0620H
      
      CNT DB 15;倒计时变量
      CNT_TEMP DB 15H;锁存所有当前状态的变量
      TIME_OF_RED_LED DB 10;初始红灯时间
      TIME_OF_GREEN_LED DB 15;初始绿灯时间
      TIME_OF_YELLOW_LED DB 3;初始黄灯时间
      BREAK DB 00H;用于跳出按键5的设置时间状态
      STATE DB 00H;00H--EWG-SNR;01H--EWG-SNY;10H--EWR-SNG;11H--EWY-SNG

DATA	ENDS

EXTRA	SEGMENT	;	;附加段
 
 
 
EXTRA	ENDS
;


STACK	SEGMENT  PARA  STACK  'STACK'  ;堆栈段
STAPN	DB     500 DUP (00H)	;定义100字节空间
TOP	EQU  LENGTH  STAPN
STACK	ENDS
           
 
           
CODE	SEGMENT			
MAIN	PROC   FAR			;过程定义语句
				;说明4个段寄存器分别与哪些段有关
		ASSUME  CS:CODE, DS:DATA,ES:EXTRA,SS:STACK
 
START: 

		
        MOV AX,DATA
        MOV DS,AX    
        
        MOV AX, EXTRA
        MOV ES,AX
        
        MOV AX,STACK
        MOV SS,AX
        
        ; 此处输入代码 
        ; 初始化8255
        MOV DX,CS8255
        MOV AL,REGIS
        OUT DX,AL
        ;初始化8253,产生1HZ信号
        MOV AL,00110101B;  
        MOV DX,CS8253  
	    OUT DX,AL  
	    MOV AL,00  
	    MOV DX,TRANAL0
	    OUT DX,AL
	    MOV AL,10H     
	    MOV DX,TRANAL0
	    OUT DX,AL
	    
        MOV AL,01110110B     
        MOV DX,CS8253 
        OUT DX,AL
        MOV AL,0E8H        
        MOV DX,TRANAL1
        OUT DX,AL
        MOV AL,03H  
        MOV DX,TRANAL1 
        OUT DX,AL               
        
        
	    
NOT_BEGIN:
		;(X4,Y4)12，对应右下角按键，按下才能正常启动系统
		MOV DX,PORTC
		MOV AL,00000111B 
		OUT DX,AL
		IN AL,DX
		AND AL,0F0H
		CMP AL,01110000B
		JNZ NOT_BEGIN
		JMP BEGIN 
BEGIN:	
        ; 显示计数的初始值
        MOV BX, OFFSET LED
        MOV AL,CNT
        XLAT
        
        MOV DX,PORTB
        OUT DX,AL
        
        ; 对8259 初始化
        
        MOV DX,ICW1
        MOV AL, 11H;00010011B
        OUT DX,AL
        
        MOV DX,ICW2
        MOV AL,08H;003CH
        OUT DX,AL
        
       
        MOV DX,ICW4
        MOV AL,01H;00000001B
        OUT DX,AL
        
        MOV DX,OCW1
        MOV AL,6FH;11111000B
        OUT DX,AL 
        
        ;定义中断向量表
        MOV AX,00H
        MOV ES,AX
        
        MOV BX, 003CH
        MOV AX,OFFSET INT0 
        MOV ES:[BX],AX 
        
        MOV AX,CS
        MOV ES:[BX+2],AX   
        STI
       ;数码管片选
CS_CONTRO:     
         XOR AX,AX;需要清零
         MOV AL,CNT    
         MOV BL,10
         DIV BL  ;除以10，十位在AL，个位在AH，注意只有AL能OUT
         ;十位显示
         MOV BX,AX
         MOV DX,PORTC 
         MOV AL,00001010B;两个1代表两个十位，东西方向和南北方向的数码管显示是一样的
         OUT DX,AL  
         MOV AX,BX              
         MOV BX,OFFSET LED
         XLAT          
         MOV DX,PORTB
         OUT DX,AL  
         CALL delay10ms 
         CALL CLEAR;记得清屏里要延时
         ;个位显示 
         MOV BX,AX
         MOV DX,PORTC
         MOV AL,00000101B   
         OUT DX,AL
         MOV AX,BX
         MOV AL,AH
         MOV BX,OFFSET LED
         XLAT          
         MOV DX,PORTB
         OUT DX,AL                     
         CALL delay10ms
         CALL CLEAR
         ;键盘扫描，扫描1~5按键，6~12按键在按键5中扫描，为嵌套扫描
         ;(X1,Y1)
         MOV DX,PORTC
         MOV AL,00001110B 
         OUT DX,AL
         IN AL,DX
         AND AL,0F0H
         CMP AL,11100000B
         JNZ KEY_Y1_X1_NO
         CALL KEY_Y1_X1_YES
KEY_Y1_X1_NO:         
		 ;(X2,Y1)
         MOV DX,PORTC
         MOV AL,00001101B 
         OUT DX,AL
         IN AL,DX
         AND AL,0F0H
         CMP AL,11100000B
         JNZ KEY_Y1_X2_NO
         CALL KEY_Y1_X2_YES        
KEY_Y1_X2_NO:            
         ;(X3,Y1)
         MOV DX,PORTC
         MOV AL,00001011B 
         OUT DX,AL
         IN AL,DX
         AND AL,0F0H
         CMP AL,11100000B
         JNZ KEY_Y1_X3_NO
         CALL KEY_Y1_X3_YES
KEY_Y1_X3_NO:         
		 ;(X4,Y1)
         MOV DX,PORTC
         MOV AL,00000111B 
         OUT DX,AL
         IN AL,DX
         AND AL,0F0H
         CMP AL,11100000B
         JNZ KEY_Y1_X4_NO
         CALL KEY_Y1_X4_YES        
KEY_Y1_X4_NO:
         ;(X1,Y2)
         MOV DX,PORTC
         MOV AL,00001110B 
         OUT DX,AL
         IN AL,DX
         AND AL,0F0H
         CMP AL,11010000B
         JNZ KEY_Y2_X1_NO
         CALL KEY_Y2_X1_YES
KEY_Y2_X1_NO:         
        JMP CS_CONTRO
        
        
        
  L1:
       JMP L1      
        
   
        
        RET
MAIN	ENDP		;MAIN过程结束

;按键1
KEY_Y1_X1_YES PROC
CLI
PUSH AX
PUSH DX
CALL DELAY_FOR_KEY
MOV AL,CNT
MOV CNT_TEMP,AL
MOV AL,88
MOV CNT,AL
;状态不会变，不需要锁存
MOV DX,PORTA
MOV AL,10010000B
OUT DX,AL

;MOV DX,PORTC
;MOV AL,0F0H
;OUT DX,AL

POP DX
POP AX
RET
KEY_Y1_X1_YES ENDP


;按键2
KEY_Y1_X2_YES PROC
PUSH AX
PUSH DX
CALL DELAY_FOR_KEY
MOV AL,CNT_TEMP
MOV CNT,AL
STI

POP DX
POP AX
RET
KEY_Y1_X2_YES ENDP


;按键3--东西方向强行通车，南北方向禁止通车
KEY_Y1_X3_YES PROC
CLI
PUSH AX
PUSH DX
CALL DELAY_FOR_KEY
MOV AL,CNT
MOV CNT_TEMP,AL
MOV AL,88
MOV CNT,AL
;状态不会变，不需要锁存
MOV DX,PORTA
MOV AL,01010000B
OUT DX,AL

POP DX
POP AX
RET
KEY_Y1_X3_YES ENDP


;按键4--南北方向强行通车，东西方向禁止通车
KEY_Y1_X4_YES PROC
CLI
PUSH AX
PUSH DX
CALL DELAY_FOR_KEY
MOV AL,CNT
MOV CNT_TEMP,AL
MOV AL,88
MOV CNT,AL
;状态不会变，不需要锁存
MOV DX,PORTA
MOV AL,10001000B
OUT DX,AL

POP DX
POP AX
RET
KEY_Y1_X4_YES ENDP


;按键5--设置时间
KEY_Y2_X1_YES PROC
CLI
PUSH AX
PUSH DX
CALL DELAY_FOR_KEY

CONTINU_CHECK:
	;(X2,Y2)6
	MOV DX,PORTC
	MOV AL,00001101B 
	OUT DX,AL
	IN AL,DX
	AND AL,0F0H
	CMP AL,11010000B
	JNZ KEY_Y2_X2_NO
	CALL KEY_Y2_X2_YES        
KEY_Y2_X2_NO:
	;(X3,Y2)7
	MOV DX,PORTC
	MOV AL,00001011B 
	OUT DX,AL
	IN AL,DX
	AND AL,0F0H
	CMP AL,11010000B
	JNZ KEY_Y2_X3_NO
	CALL KEY_Y2_X3_YES        
KEY_Y2_X3_NO:
	;(X4,Y2)8
	MOV DX,PORTC
	MOV AL,00000111B 
	OUT DX,AL
	IN AL,DX
	AND AL,0F0H
	CMP AL,11010000B
	JNZ KEY_Y2_X4_NO
	CALL KEY_Y2_X4_YES  
KEY_Y2_X4_NO:
	;(X4,Y3)12
	MOV DX,PORTC
	MOV AL,00000111B 
	OUT DX,AL
	IN AL,DX
	AND AL,0F0H
	CMP AL,10110000B
	JNZ KEY_Y3_X4_NO
	JMP END_SET_TIME 
KEY_Y3_X4_NO:	
	JMP CONTINU_CHECK

END_SET_TIME: 
STI      
POP DX
POP AX
RET
KEY_Y2_X1_YES ENDP


;按键6--在这里扫描9，10，11号按键，实现加减
KEY_Y2_X2_YES PROC
PUSH AX
PUSH DX
PUSH BX
CALL DELAY_FOR_KEY
KEY6_CONTINU_CHECK:
	;显示调整的时间
	     MOV DX,PORTC
	     MOV AL,0FH
	     OUT DX,AL
         XOR AX,AX
         MOV AL,TIME_OF_RED_LED 
         MOV BL,10
         DIV BL  
         ;十位显示
         MOV BX,AX
         MOV DX,PORTA 
         MOV AL,00000010B
         OUT DX,AL  
         MOV AX,BX              
         MOV BX,OFFSET LED
         XLAT          
         MOV DX,PORTB
         OUT DX,AL  
         CALL delay10ms 
         CALL CLEAR
         ;个位显示 
         MOV BX,AX
         MOV DX,PORTA
         MOV AL,00000001B   
         OUT DX,AL
         MOV AX,BX
         MOV AL,AH
         MOV BX,OFFSET LED
         XLAT          
         MOV DX,PORTB
         OUT DX,AL                     
         CALL delay10ms
         CALL CLEAR
	;(X1,Y3)9--加法
	MOV DX,PORTC
	MOV AL,00001110B 
	OUT DX,AL
	IN AL,DX
	AND AL,0F0H
	CMP AL,10110000B
	JNZ KEY_Y3_X1_NO_RED
	CALL DELAY_FOR_KEY
	MOV AL,TIME_OF_RED_LED
	INC AL
	MOV TIME_OF_RED_LED,AL
	CMP AL,99
	JNA ADD_OVER_RED
 	MOV AL,6
ADD_OVER_RED:	
		MOV TIME_OF_RED_LED,AL   
KEY_Y3_X1_NO_RED:
	;(X2,Y3)10--减法
	MOV DX,PORTC
	MOV AL,00001101B 
	OUT DX,AL
	IN AL,DX
	AND AL,0F0H
	CMP AL,10110000B
	JNZ KEY_Y3_X2_NO_RED
	CALL DELAY_FOR_KEY
	MOV AL,TIME_OF_RED_LED
	DEC AL
	MOV TIME_OF_RED_LED,AL
	CMP AL,6
	JA DELETE_OVER_RED
 	MOV AL,6
DELETE_OVER_RED:	
		MOV TIME_OF_RED_LED,AL   	
KEY_Y3_X2_NO_RED:
	;(X3,Y3)11
	MOV DX,PORTC
	MOV AL,00001011B 
	OUT DX,AL
	IN AL,DX
	AND AL,0F0H
	CMP AL,10110000B
	JNZ KEY_Y3_X3_NO_RED
	JMP END_SET_TIME_OF_RED_LED
KEY_Y3_X3_NO_RED:
			JMP KEY6_CONTINU_CHECK
END_SET_TIME_OF_RED_LED:
POP BX
POP DX
POP AX
RET
KEY_Y2_X2_YES ENDP

;按键7，同按键6，只是变为针对绿灯
KEY_Y2_X3_YES PROC
PUSH AX
PUSH DX
PUSH BX
CALL DELAY_FOR_KEY
KEY7_CONTINU_CHECK:
	;显示调整的时间
	     MOV DX,PORTC
	     MOV AL,0FH
	     OUT DX,AL
         XOR AX,AX
         MOV AL,TIME_OF_GREEN_LED 
         MOV BL,10
         DIV BL  
         ;十位显示
         MOV BX,AX
         MOV DX,PORTA 
         MOV AL,00000010B
         OUT DX,AL  
         MOV AX,BX              
         MOV BX,OFFSET LED
         XLAT          
         MOV DX,PORTB
         OUT DX,AL  
         CALL delay10ms 
         CALL CLEAR
         ;个位显示 
         MOV BX,AX
         MOV DX,PORTA
         MOV AL,00000001B   
         OUT DX,AL
         MOV AX,BX
         MOV AL,AH
         MOV BX,OFFSET LED
         XLAT          
         MOV DX,PORTB
         OUT DX,AL                     
         CALL delay10ms
         CALL CLEAR
	;(X1,Y3)9--加法
	MOV DX,PORTC
	MOV AL,00001110B 
	OUT DX,AL
	IN AL,DX
	AND AL,0F0H
	CMP AL,10110000B
	JNZ KEY_Y3_X1_NO_GREEN
	CALL DELAY_FOR_KEY
	MOV AL,TIME_OF_GREEN_LED
	INC AL
	MOV TIME_OF_GREEN_LED,AL
	CMP AL,99
	JNA ADD_OVER_GREEN
 	MOV AL,6
ADD_OVER_GREEN:	
		MOV TIME_OF_GREEN_LED,AL   
KEY_Y3_X1_NO_GREEN:
	;(X2,Y3)10--减法
	MOV DX,PORTC
	MOV AL,00001101B 
	OUT DX,AL
	IN AL,DX
	AND AL,0F0H
	CMP AL,10110000B
	JNZ KEY_Y3_X2_NO_GREEN
	CALL DELAY_FOR_KEY
	MOV AL,TIME_OF_GREEN_LED
	DEC AL
	MOV TIME_OF_GREEN_LED,AL
	CMP AL,6
	JA DELETE_OVER_GREEN
 	MOV AL,6
DELETE_OVER_GREEN:	
		MOV TIME_OF_GREEN_LED,AL   	
KEY_Y3_X2_NO_GREEN:
	;(X3,Y3)11
	MOV DX,PORTC
	MOV AL,00001011B 
	OUT DX,AL
	IN AL,DX
	AND AL,0F0H
	CMP AL,10110000B
	JNZ KEY_Y3_X3_NO_GREEN
	JMP END_SET_TIME_OF_GREEN_LED
KEY_Y3_X3_NO_GREEN:
			JMP KEY7_CONTINU_CHECK
END_SET_TIME_OF_GREEN_LED:
POP BX
POP DX
POP AX
RET
KEY_Y2_X3_YES ENDP


;按键8--同按键6，只是变为针对黄灯
KEY_Y2_X4_YES PROC
PUSH AX
PUSH DX
PUSH BX
CALL DELAY_FOR_KEY
KEY8_CONTINU_CHECK:
	;显示调整的时间
	     MOV DX,PORTC
	     MOV AL,0FH
	     OUT DX,AL
         XOR AX,AX
         MOV AL,TIME_OF_YELLOW_LED 
         MOV BL,10
         DIV BL  
         ;十位显示
         MOV BX,AX
         MOV DX,PORTA 
         MOV AL,00000010B
         OUT DX,AL  
         MOV AX,BX              
         MOV BX,OFFSET LED
         XLAT          
         MOV DX,PORTB
         OUT DX,AL  
         CALL delay10ms 
         CALL CLEAR
         ;个位显示 
         MOV BX,AX
         MOV DX,PORTA
         MOV AL,00000001B   
         OUT DX,AL
         MOV AX,BX
         MOV AL,AH
         MOV BX,OFFSET LED
         XLAT          
         MOV DX,PORTB
         OUT DX,AL                     
         CALL delay10ms
         CALL CLEAR
	;(X1,Y3)9--加法
	MOV DX,PORTC
	MOV AL,00001110B 
	OUT DX,AL
	IN AL,DX
	AND AL,0F0H
	CMP AL,10110000B
	JNZ KEY_Y3_X1_NO_YELLOW
	CALL DELAY_FOR_KEY
	MOV AL,TIME_OF_YELLOW_LED
	INC AL
	MOV TIME_OF_YELLOW_LED,AL
	CMP AL,5
	JNA ADD_OVER_YELLOW
 	MOV AL,5
ADD_OVER_YELLOW:	
		MOV TIME_OF_YELLOW_LED,AL   
KEY_Y3_X1_NO_YELLOW:
	;(X2,Y3)10--减法
	MOV DX,PORTC
	MOV AL,00001101B 
	OUT DX,AL
	IN AL,DX
	AND AL,0F0H
	CMP AL,10110000B
	JNZ KEY_Y3_X2_NO_YELLOW
	CALL DELAY_FOR_KEY
	MOV AL,TIME_OF_YELLOW_LED
	DEC AL
	MOV TIME_OF_YELLOW_LED,AL
	CMP AL,2
	JA DELETE_OVER_YELLOW
 	MOV AL,2
DELETE_OVER_YELLOW:	
		MOV TIME_OF_YELLOW_LED,AL   	
KEY_Y3_X2_NO_YELLOW:
	;(X3,Y3)11
	MOV DX,PORTC
	MOV AL,00001011B 
	OUT DX,AL
	IN AL,DX
	AND AL,0F0H
	CMP AL,10110000B
	JNZ KEY_Y3_X3_NO_YELLOW
	JMP END_SET_TIME_OF_YELLOW_LED
KEY_Y3_X3_NO_YELLOW:
			JMP KEY8_CONTINU_CHECK
END_SET_TIME_OF_YELLOW_LED:
POP BX
POP DX
POP AX
RET
KEY_Y2_X4_YES ENDP




;中断主要实现接收8254的OUT2的上升沿触发，实现CNT+1，还有就是变换STATE，调用相应的子程序进行数码管显示和灯的显示
;在写程序之前先画好状态机流程图
INT0 PROC
     PUSH AX
     CLI
     
     ;MOV AL,CNT
;     INC AL
;     AND AL,0FH 
;     MOV CNT,AL 
     
     MOV AL,CNT  
     DEC AL  
     MOV CNT,AL
     
     MOV AL,STATE
     CMP AL,00H
     JZ EWG_SNR
     
     CMP AL,01H
     JZ EWY_SNR

     CMP AL,10H
     JZ EWR_SNG
     
     CMP AL,11H
     JZ EWR_SNY
    

EWG_SNR:
		MOV DX,PORTA
		MOV AL,01010011B;最后两位为11，防止显示倒计时时产生干扰
	    OUT DX,AL
	    MOV AL,CNT
	    CMP AL,TIME_OF_YELLOW_LED
	    JNZ END_EWG_SNR
	    CALL EWG_SNR_PROC
END_EWG_SNR:
	    JMP END_INTO0 
	    
	    
EWY_SNR:
		MOV DX,PORTA
		MOV AL,00110011B
	    OUT DX,AL
	    CALL DELAY_FOR_YELLOW
	    MOV AL,00010011B
	    OUT DX,AL
	    
	    MOV AL,CNT
	    CMP AL,0
	    JNZ END_EWY_SNR
	    CALL EWY_SNR_PROC
END_EWY_SNR:
	    JMP END_INTO0
	    
	    
EWR_SNG:
		MOV DX,PORTA
		MOV AL,10001011B
	    OUT DX,AL
	    MOV AL,CNT
	    CMP AL,TIME_OF_YELLOW_LED
	    JNZ END_EWR_SNG
	    CALL EWR_SNG_PROC
END_EWR_SNG:
	    JMP END_INTO0
	    
	    
EWR_SNY:
		MOV DX,PORTA
		MOV AL,10000111B
	    OUT DX,AL
	    CALL DELAY_FOR_YELLOW
	    MOV AL,10000011B
	    OUT DX,AL
	    
	    MOV AL,CNT
	    CMP AL,0
	    JNZ END_EWR_SNY
	    CALL EWR_SNY_PROC
END_EWR_SNY:
	    JMP END_INTO0	
	    
	    						    
END_INTO0:     
     MOV DX,OCW2
     MOV AL,20H
     OUT DX,AL
     
     STI
     POP AX
     
    
    IRET
INT0 ENDP


EWG_SNR_PROC PROC
	PUSH AX
	MOV AL,STATE
	MOV AL,01H
	MOV STATE,AL
	POP AX
	RET
EWG_SNR_PROC ENDP



EWY_SNR_PROC PROC
	PUSH AX
	MOV AL,STATE
	MOV AL,10H
	MOV STATE,AL
	MOV AL,TIME_OF_RED_LED
	MOV CNT,AL
	POP AX
	RET
EWY_SNR_PROC ENDP


EWR_SNG_PROC PROC
	PUSH AX
	MOV AL,STATE
	MOV AL,11H
	MOV STATE,AL
	POP AX
	RET
EWR_SNG_PROC ENDP



EWR_SNY_PROC PROC
	PUSH AX
	MOV AL,STATE
	MOV AL,00H
	MOV STATE,AL
	MOV AL,TIME_OF_GREEN_LED
	MOV CNT,AL
	POP AX
	RET
EWR_SNY_PROC ENDP

;不准确的延时
delay10ms proc
	PUSH CX						
	push ax
    MOV CX,000aH
T1:	MOV AX,008FH
T2:	DEC AX
	JNZ T2
	LOOP T1
    pop ax
	POP CX
	RET
delay10ms endp

;按键消抖
DELAY_FOR_KEY PROC
	PUSH CX						
	PUSH AX
    MOV CX,0AAAH
T3:	MOV AX,008FH
T4:	DEC AX
	JNZ T4
	LOOP T3
    POP AX
	POP CX
	RET
DELAY_FOR_KEY ENDP


;作为黄灯闪烁的时钟
DELAY_FOR_YELLOW PROC
	PUSH CX						
	PUSH AX
    MOV CX,009AH
T5:	MOV AX,008FH
T6:	DEC AX
	JNZ T6
	LOOP T5
    POP AX
	POP CX
	RET
DELAY_FOR_YELLOW ENDP    


clear proc
    push dx
    push ax 
    mov dx,PORTB
    mov al,00H
    out dx,al
    call delay10ms
    pop ax
    pop dx
    ret
clear endp


CODE 	ENDS	          	;代码段结束
    END   MAIN	;整个源代码结束
