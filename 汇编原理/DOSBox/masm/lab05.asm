DATAS SEGMENT
      X DB 5,-4,0,3,100,-51 ;循环6次
  DATA1 DB 'Y= 0',0DH,0AH,'$'
  DATA2 DB 'Y= 1',0DH,0AH,'$'
  DATA3 DB 'Y=-1',0DH,0AH,'$'
DATAS ENDS

stack segment stack
    ;db	200 dup(0)
stack ends

CODES SEGMENT
  ASSUME CS:CODES, DS:DATAS, SS:stack
START:
  MOV AX,DATAS
  MOV DS,AX
  
  MOV SI,OFFSET X ;返回 X 的偏移地址
  ;STD 
  ;CLD            ;复位方向标志：DF=0
  MOV CX,6        ;用于循环计数
  
CHECK:
  MOV AL,[SI]
  CMP AL,00H
  JE  NEXT1  ;等于跳转
  JG  NEXT2  ;大于跳转
  MOV DI,OFFSET DATA3 ;返回 DATA3 的偏移地址
  JMP DONE  ;小于跳转
  
NEXT1:
  MOV DI,OFFSET DATA1
  JMP DONE
  
NEXT2:
  MOV DI,OFFSET DATA2
  
DONE:
  MOV DX,DI   ;DX字串首地址
  MOV AH,09H  ;输出一个以"$"结尾的字符串到显示器
  INT 21H
  
  INC SI      ;下一个X
  LOOP CHECK  ;CX-=1
  
  MOV AH, 4CH ;返回DOS
  INT 21H
  
CODES ENDS
  END START