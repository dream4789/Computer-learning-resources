DATA SEGMENT 
    STRING  DB      50        ;�ַ�����󳤶�
        	  DB      0         ;�ַ���ʵ�ʳ���
        	  DB	    50 DUP(0) ;�ַ�����Ч����
    MSG1 DB 'INPUT STRING:$'  ;��ʾ��Ϣ
    MSG2 DB 'OUTPUT STRING:$'
    CRLF DB 0DH, 0AH, '$'     ;����
DATA ENDS 

CODE SEGMENT
    ASSUME  CS:CODE, DS:DATA
START:

    MOV AX,DATA 
    MOV DS,AX

	  LEA	DX,MSG1       ;��ʾ��ʾ��Ϣ
	  MOV AH,09H
	  INT 21H

	  LEA	DX,STRING     ;�����ַ���
	  MOV AH,0AH
	  INT 21H

	  LEA SI,STRING+1
	  XOR CX,CX
    MOV CX,[SI]       ;ѭ������
    LEA BX,STRING+2   ;��STRING��ƫ�Ƶ�ַ�͵�BX
                
ALP:   
    MOV AL,[BX]
    CMP AL,'$'             ;�ж��Ƿ�Ϊ���һ���ַ�
    JZ  OVER               ;����$����ִ��OVER                             
    CMP AL,'a'             ;AL��Сдa�Ƚ�           
    JB  NEXT               ;AL��aСʱִ��NEXT         
    CMP AL,'z'      
    JA  NEXT               ;AL��z��ʱִ��NEXT
    SUB AL,20H             ;Сдת�ɴ�д
    JMP NEXT 

NEXT:  
    MOV  [BX],AL           ;��ת������ַ����ͻ�ԭ��ַ
    INC  BX 
    LOOP ALP

OVER:
  	LEA DX,CRLF
  	MOV AH,09H           ;����
  	INT 21H
  
  	LEA DX,MSG2
  	MOV AH,09H           ;��ʾ��ʾ��Ϣ
  	INT 21H 
  
  	LEA DX,STRING+2      ;���ת������ַ���
  	MOV AH,09H
  	INT 21H
   
    MOV AH,4CH
    INT 21H
      
CODE ENDS
    END START
