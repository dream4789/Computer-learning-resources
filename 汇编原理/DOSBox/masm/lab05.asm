DATAS SEGMENT
      X DB 5,-4,0,3,100,-51 ;ѭ��6��
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
  
  MOV SI,OFFSET X ;���� X ��ƫ�Ƶ�ַ
  ;STD 
  ;CLD            ;��λ�����־��DF=0
  MOV CX,6        ;����ѭ������
  
CHECK:
  MOV AL,[SI]
  CMP AL,00H
  JE  NEXT1  ;������ת
  JG  NEXT2  ;������ת
  MOV DI,OFFSET DATA3 ;���� DATA3 ��ƫ�Ƶ�ַ
  JMP DONE  ;С����ת
  
NEXT1:
  MOV DI,OFFSET DATA1
  JMP DONE
  
NEXT2:
  MOV DI,OFFSET DATA2
  
DONE:
  MOV DX,DI   ;DX�ִ��׵�ַ
  MOV AH,09H  ;���һ����"$"��β���ַ�������ʾ��
  INT 21H
  
  INC SI      ;��һ��X
  LOOP CHECK  ;CX-=1
  
  MOV AH, 4CH ;����DOS
  INT 21H
  
CODES ENDS
  END START