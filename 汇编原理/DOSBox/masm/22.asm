DATA SEGMENT
    STR  DB 5 DUP(0)
         DB '$'
    disp DB 'S=1+2x3+3x4+4x5+...+N(N+1)+...=$'   ; ¶¨ÒåÊä³ö×Ö·û´®
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA
START: 
    MOV AX,DATA
    MOV DS,AX
    MOV DX,1
    MOV BL,2
LOP:   
    MOV AL,BL
    INC BL
    MUL BL
    ADD DX,AX
    CMP AX,200
    JBE LOP
    MOV AX,DX
    LEA DI,STR+4
LOP2:  
    MOV CL,10
    DIV CL
    ADD AH,30H
    MOV [DI],AH
    AND AX,00FFH
    DEC DI 
    CMP AL,0
    JNE LOP2
    
    ;push dx
    ;push ax
    lea dx,disp
    mov ah,09h
    int 21h
    ;pop ax
    ;pop dx
  
    LEA DX,STR
    MOV AH,9
    INT 21H
    
    MOV AH,4CH
    INT 21H
CODE ENDS
    END START