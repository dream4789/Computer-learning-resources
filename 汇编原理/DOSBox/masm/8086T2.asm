;------------------------------------------------------------------
;Function: (tip:����SCNU΢��ԭ��ʵ����)
;΢��ԭ����̵���ƣ�����12�Ű�������ϵͳ������������ϱ�������ͨ�У�
;Ϊһ����̵ƹ��ɣ��������Ƶ�ʱ�����÷�ΧΪ6~99�����Լ��޸ģ����Ƶ�ʱ�����÷�ΧΪ2~5S�����Լ��޸ģ�
;������Ӧ���ܣ�������̣���Ӧԭ��ͼ��
;---------------------------------------------------------------------------
;-  (�����ϱ���ֹͨ��)           (�ָ�����)                    (������ֹͨ��)         (�ϱ���ֹͨ��)
;y  (����ʱ������)               (���ú��ʱ��)                (�����̵�ʱ��)         (���ûƵ�ʱ��)
;�� (ѡ���������ֵƺ���������1)(ѡ���������ֵƺ��������1) (����ѡ���趨ʱ��ĵ�) (����ʱ��������ָ���ʱ)
;-  ()                           ()                            ()                     (����ϵͳ)
;-------------------------------------x��-----------------------------------
DATA	SEGMENT		;���ݶ�		
      ;�˴��������ݶ�
      LED DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,6FH,77H,7CH,39H,5EH,79H,71H
          
      IOY0 EQU  0600H;8255��ַ����ӦIOY0
      IOY1 EQU  0640H;8254��ַ����ӦIOY1
      IOY2 EQU  0650H;��������8259�������䲻��
      PORTA EQU IOY0
      PORTB EQU IOY0+02H
      PORTC EQU IOY0+04H
      CS8255 EQU IOY0+06H
      ; A�ڹ�����ʽ0 ����  B�ڹ�����ʽ0 ���� 
      REGIS EQU 88H;AB�ڷ�ʽ0��ȫΪ�����C�ڸ���λ���룬����λ��� 
      
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
      
      CNT DB 15;����ʱ����
      CNT_TEMP DB 15H;�������е�ǰ״̬�ı���
      TIME_OF_RED_LED DB 10;��ʼ���ʱ��
      TIME_OF_GREEN_LED DB 15;��ʼ�̵�ʱ��
      TIME_OF_YELLOW_LED DB 3;��ʼ�Ƶ�ʱ��
      BREAK DB 00H;������������5������ʱ��״̬
      STATE DB 00H;00H--EWG-SNR;01H--EWG-SNY;10H--EWR-SNG;11H--EWY-SNG

DATA	ENDS

EXTRA	SEGMENT	;	;���Ӷ�
 
 
 
EXTRA	ENDS
;


STACK	SEGMENT  PARA  STACK  'STACK'  ;��ջ��
STAPN	DB     500 DUP (00H)	;����100�ֽڿռ�
TOP	EQU  LENGTH  STAPN
STACK	ENDS
           
 
           
CODE	SEGMENT			
MAIN	PROC   FAR			;���̶������
				;˵��4���μĴ����ֱ�����Щ���й�
		ASSUME  CS:CODE, DS:DATA,ES:EXTRA,SS:STACK
 
START: 

		
        MOV AX,DATA
        MOV DS,AX    
        
        MOV AX, EXTRA
        MOV ES,AX
        
        MOV AX,STACK
        MOV SS,AX
        
        ; �˴�������� 
        ; ��ʼ��8255
        MOV DX,CS8255
        MOV AL,REGIS
        OUT DX,AL
        ;��ʼ��8253,����1HZ�ź�
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
		;(X4,Y4)12����Ӧ���½ǰ��������²�����������ϵͳ
		MOV DX,PORTC
		MOV AL,00000111B 
		OUT DX,AL
		IN AL,DX
		AND AL,0F0H
		CMP AL,01110000B
		JNZ NOT_BEGIN
		JMP BEGIN 
BEGIN:	
        ; ��ʾ�����ĳ�ʼֵ
        MOV BX, OFFSET LED
        MOV AL,CNT
        XLAT
        
        MOV DX,PORTB
        OUT DX,AL
        
        ; ��8259 ��ʼ��
        
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
        
        ;�����ж�������
        MOV AX,00H
        MOV ES,AX
        
        MOV BX, 003CH
        MOV AX,OFFSET INT0 
        MOV ES:[BX],AX 
        
        MOV AX,CS
        MOV ES:[BX+2],AX   
        STI
       ;�����Ƭѡ
CS_CONTRO:     
         XOR AX,AX;��Ҫ����
         MOV AL,CNT    
         MOV BL,10
         DIV BL  ;����10��ʮλ��AL����λ��AH��ע��ֻ��AL��OUT
         ;ʮλ��ʾ
         MOV BX,AX
         MOV DX,PORTC 
         MOV AL,00001010B;����1��������ʮλ������������ϱ�������������ʾ��һ����
         OUT DX,AL  
         MOV AX,BX              
         MOV BX,OFFSET LED
         XLAT          
         MOV DX,PORTB
         OUT DX,AL  
         CALL delay10ms 
         CALL CLEAR;�ǵ�������Ҫ��ʱ
         ;��λ��ʾ 
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
         ;����ɨ�裬ɨ��1~5������6~12�����ڰ���5��ɨ�裬ΪǶ��ɨ��
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
MAIN	ENDP		;MAIN���̽���

;����1
KEY_Y1_X1_YES PROC
CLI
PUSH AX
PUSH DX
CALL DELAY_FOR_KEY
MOV AL,CNT
MOV CNT_TEMP,AL
MOV AL,88
MOV CNT,AL
;״̬����䣬����Ҫ����
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


;����2
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


;����3--��������ǿ��ͨ�����ϱ������ֹͨ��
KEY_Y1_X3_YES PROC
CLI
PUSH AX
PUSH DX
CALL DELAY_FOR_KEY
MOV AL,CNT
MOV CNT_TEMP,AL
MOV AL,88
MOV CNT,AL
;״̬����䣬����Ҫ����
MOV DX,PORTA
MOV AL,01010000B
OUT DX,AL

POP DX
POP AX
RET
KEY_Y1_X3_YES ENDP


;����4--�ϱ�����ǿ��ͨ�������������ֹͨ��
KEY_Y1_X4_YES PROC
CLI
PUSH AX
PUSH DX
CALL DELAY_FOR_KEY
MOV AL,CNT
MOV CNT_TEMP,AL
MOV AL,88
MOV CNT,AL
;״̬����䣬����Ҫ����
MOV DX,PORTA
MOV AL,10001000B
OUT DX,AL

POP DX
POP AX
RET
KEY_Y1_X4_YES ENDP


;����5--����ʱ��
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


;����6--������ɨ��9��10��11�Ű�����ʵ�ּӼ�
KEY_Y2_X2_YES PROC
PUSH AX
PUSH DX
PUSH BX
CALL DELAY_FOR_KEY
KEY6_CONTINU_CHECK:
	;��ʾ������ʱ��
	     MOV DX,PORTC
	     MOV AL,0FH
	     OUT DX,AL
         XOR AX,AX
         MOV AL,TIME_OF_RED_LED 
         MOV BL,10
         DIV BL  
         ;ʮλ��ʾ
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
         ;��λ��ʾ 
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
	;(X1,Y3)9--�ӷ�
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
	;(X2,Y3)10--����
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

;����7��ͬ����6��ֻ�Ǳ�Ϊ����̵�
KEY_Y2_X3_YES PROC
PUSH AX
PUSH DX
PUSH BX
CALL DELAY_FOR_KEY
KEY7_CONTINU_CHECK:
	;��ʾ������ʱ��
	     MOV DX,PORTC
	     MOV AL,0FH
	     OUT DX,AL
         XOR AX,AX
         MOV AL,TIME_OF_GREEN_LED 
         MOV BL,10
         DIV BL  
         ;ʮλ��ʾ
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
         ;��λ��ʾ 
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
	;(X1,Y3)9--�ӷ�
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
	;(X2,Y3)10--����
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


;����8--ͬ����6��ֻ�Ǳ�Ϊ��ԻƵ�
KEY_Y2_X4_YES PROC
PUSH AX
PUSH DX
PUSH BX
CALL DELAY_FOR_KEY
KEY8_CONTINU_CHECK:
	;��ʾ������ʱ��
	     MOV DX,PORTC
	     MOV AL,0FH
	     OUT DX,AL
         XOR AX,AX
         MOV AL,TIME_OF_YELLOW_LED 
         MOV BL,10
         DIV BL  
         ;ʮλ��ʾ
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
         ;��λ��ʾ 
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
	;(X1,Y3)9--�ӷ�
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
	;(X2,Y3)10--����
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




;�ж���Ҫʵ�ֽ���8254��OUT2�������ش�����ʵ��CNT+1�����о��Ǳ任STATE��������Ӧ���ӳ�������������ʾ�͵Ƶ���ʾ
;��д����֮ǰ�Ȼ���״̬������ͼ
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
		MOV AL,01010011B;�����λΪ11����ֹ��ʾ����ʱʱ��������
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

;��׼ȷ����ʱ
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

;��������
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


;��Ϊ�Ƶ���˸��ʱ��
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


CODE 	ENDS	          	;����ν���
    END   MAIN	;����Դ�������
