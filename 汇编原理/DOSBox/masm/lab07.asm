data segment
    GRADE   DB 04H, 05H, 03H, 30H, 29H, 26H, 27H, 31H, 35H, 39H
    RANK    DB $-GRADE DUP(?)
    TEMP    DB ?
    ORGINAL DB "Original data :$"
    destiny DB "After sorting :$"	
data ends

stack segment stack
stack ends

code segment
    assume cs:code, ds:data, ss:stack
start:
    mov ax,data
    mov ds,ax
    
    call COPY
    
    MOV DX,OFFSET ORGINAL
    MOV AH,09H
    INT 21H
    
    CALL ENTER_
    CALL SHOW
    
    MOV DL,0AH
    MOV AH,02H
    INT 21H
    
    CALL SORT
     
    MOV DX,OFFSET DESTINY
    MOV AH,09H
    INT 21H
    
    CALL ENTER_
    CALL SHOW
    
    mov AH,4ch
    int 21h
 
;排序函数
SORT PROC NEAR
    LEA DI,RANK
    LEA SI,RANK
    ADD SI,9
    
LOOP1:
    CMP SI,OFFSET RANK
    LEA DI,RANK
    JB  STOP
    
LOOP2:   
    CMP DI,SI
    JNB BREAK
    MOV AL,BYTE PTR [SI]
    CMP AL,[DI]
    JNB CONTINUE
    MOV BYTE PTR TEMP,AL
    MOV            AL,BYTE PTR [DI]
    MOV BYTE PTR [SI],AL
    MOV            AL,BYTE PTR TEMP
    MOV BYTE PTR [DI],AL
    
CONTINUE:
    INC DI
    JMP LOOP2
    
BREAK:
    DEC SI
    JMP LOOP1 
    
STOP:
    RET
    
SORT ENDP



;复制 
COPY PROC NEAR
    LEA SI,GRADE
    LEA DI,RANK
    MOV CX ,10

NEXT:
    MOV            AL,BYTE PTR [SI]
    MOV BYTE PTR [DI],AL
    INC SI
    INC DI
    LOOP NEXT
    RET

COPY ENDP



;输出目标数组中的值
SHOW PROC NEAR
    MOV BH,10
    LEA SI, RANK

PRINT: 
    MOV BL,BYTE PTR[SI]
    MOV DL,BL
    AND DL,0F0H;
    MOV CL,4
    ROR DL,CL
    
    OR DL,30H
    MOV AH,02H
    INT 21H
    
    MOV DL,BL
    AND DL,0FH
    
    OR DL,30H
    MOV AH,02H
    INT 21H
    
    MOV DL,09H
    MOV AH,02H
    INT 21H
    
    INC SI
    DEC BH
    JNZ PRINT
    RET

SHOW ENDP



ENTER_ PROC NEAR
    MOV DL,0DH
    MOV AH,02H
    INT 21H 
    
    MOV DL,0AH
    MOV AH,02H
    INT 21H
    
    RET
ENTER_ ENDP



code ends
    end start
