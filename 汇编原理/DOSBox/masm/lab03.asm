stack segment stack
    db	200 dup(0)
stack ends

DATA SEGMENT
    TABLE	DB  30H, 31H, 32H, 33H, 34H, 35H, 36H, 37H
         	DB  38H, 39H, 41H, 42H, 43H, 44H, 45H, 46H
    HEX		DB  10   ; X为待转换的十六进制数
    ASCI	DB  ?    ; 存放转换后的ASCII码
DATA ENDS

code segment
    assume cs:code, ds:data, ss:stack
main: 
    MOV   AX, data
    MOV   DS, AX
    
    LEA   BX, table
    MOV   AL, HEX
    XLAT
    MOV   asci, AL
    
    MOV   AH, 2
    INT   21H
    
    MOV   AH,4CH
    INT   21h
code ends
    end main

