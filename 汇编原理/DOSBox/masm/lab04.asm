DATA SEGMENT 
    STRING  DB      50        ;字符串最大长度
        	  DB      0         ;字符串实际长度
        	  DB	    50 DUP(0) ;字符串有效长度
    MSG1 DB 'INPUT STRING:$'  ;提示信息
    MSG2 DB 'OUTPUT STRING:$'
    CRLF DB 0DH, 0AH, '$'     ;换行
DATA ENDS 

CODE SEGMENT
    ASSUME  CS:CODE, DS:DATA
START:

    MOV AX,DATA 
    MOV DS,AX

	  LEA	DX,MSG1       ;显示提示信息
	  MOV AH,09H
	  INT 21H

	  LEA	DX,STRING     ;输入字符串
	  MOV AH,0AH
	  INT 21H

	  LEA SI,STRING+1
	  XOR CX,CX
    MOV CX,[SI]       ;循环次数
    LEA BX,STRING+2   ;把STRING的偏移地址送到BX
                
ALP:   
    MOV AL,[BX]
    CMP AL,'$'             ;判断是否为最后一个字符
    JZ  OVER               ;等于$，则执行OVER                             
    CMP AL,'a'             ;AL与小写a比较           
    JB  NEXT               ;AL比a小时执行NEXT         
    CMP AL,'z'      
    JA  NEXT               ;AL比z大时执行NEXT
    SUB AL,20H             ;小写转成大写
    JMP NEXT 

NEXT:  
    MOV  [BX],AL           ;把转换后的字符串送回原地址
    INC  BX 
    LOOP ALP

OVER:
  	LEA DX,CRLF
  	MOV AH,09H           ;换行
  	INT 21H
  
  	LEA DX,MSG2
  	MOV AH,09H           ;显示提示信息
  	INT 21H 
  
  	LEA DX,STRING+2      ;输出转换后的字符串
  	MOV AH,09H
  	INT 21H
   
    MOV AH,4CH
    INT 21H
      
CODE ENDS
    END START
