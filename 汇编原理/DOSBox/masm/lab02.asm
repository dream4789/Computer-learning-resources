stack  segment stack
      db	200 dup(0)
stack  ends

code segment
      assume cs:code,ss:stack
main: 
      ;MOV SP,2000H
      ;MOV AX,3000H
      ;MOV BX,5000H
      ;MOV SS,AX
      
      ;PUSH AX
      ;PUSH BX
      ;POP  AX
      ;POP  BX
      
      MOV BX,0300H
      MOV SI,0002H
      
      MOV AX,BX       ;ax==0300h
      MOV AX,0304H    ;ax==0304h
      MOV AX,[0304H]
      MOV AX,[BX]     ;ax==0b0ah
      MOV AX,0001[BX] ;ax==0c0bh
      MOV AX,[BX][SI] ;ax==0d0ch
      MOV AX,0001[BX][SI] ;ax==0e0dh
      HLT             ;ax==0e0dh
            
      MOV AX,4C00H
      INT 21H
      
code ends
      end main