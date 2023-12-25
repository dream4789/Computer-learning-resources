stack segment stack
  db	200 dup(0)
stack ends

data segment
  disp db 'Hello World!$'   ; ¶¨ÒåÊä³ö×Ö·û´®
data ends

code segment
  assume cs:code, ds:data, ss:stack
main: 
  mov ax,data
  mov ds,ax
  
  lea dx,disp
  
  mov ah,09h
  int 21h
  
  mov ah,4ch
  int 21h
code ends
      end main
