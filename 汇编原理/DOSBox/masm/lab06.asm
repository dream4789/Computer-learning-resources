; S=1+2*3+3*4+4*5+...+N(N+1)+...=045F 16进制输出
STACK SEGMENT PARA STACK 'stack'
    DB 1024 DUP(0)
STACK ENDS

DATA SEGMENT
    BUF DB 'S=1+2*3+3*4+4*5+...+N(N+1)+...=','$'  ;buf 存储提示信息字符串
    RES DB 4 DUP(0),'$'    ;res四位 存储结果的asii码，$符结束字符串
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:STACK ;伪指令
START: 
    MOV AX,DATA
    MOV DS,AX          ;装入代码段寄存器

    ;MOV DX,OFFSET BUF ;BUF变量的有效地址装入DX
    LEA DX,BUF         ;BUF变量的有效地址装入DX
    MOV AH,09H         ;输出字符串
    INT 21H

    MOV DX,1
    MOV BL,2

NEXT: 
    MOV AL,BL
    INC BL
    MUL BL       ;AL * BL -> AX (2*3,3*4...)
    ADD DX,AX    ;AX + DX -> DX
    CMP AX,200   ;将N(N+1)乘积与200比较
    JNA NEXT     ;不大于200

    MOV CX,0004H ;(CX)=4，装入cx，循环次数，把四组二进制数分别转换为asii码
    MOV DI,OFFSET RES
    ADD DI,03H   ;DI内容加三，因为先处理低四位，转换完成后存入到res+3字节

NEXT1: 
    MOV AX,DX
    AND AX,000FH ;AX与0000 0000 0000 1111B进行逻辑与运算，目的是其他位置零，保留第四位
    CMP AL,0AH  ;AL与10比较
    JB  NEXT2   ;若小于10则直接跳入next2标号
    ADD AL,07H  ;否则加7校正

NEXT2: 
    ADD AL,30H  ;AL加30H转换为ASII码
    MOV [DI],AL ;转换完成后存入DI当前指向的存储单元
    DEC DI      ;存入后DI减一，因为下一循环过程结果存入上一字节

    PUSH CX     ;保存CX内容
    MOV CL,04   ;装入CL，为4，为移位次数
    SHR DX,CL   ;循环右移4次，将低四位移出，高位补零
    POP CX      ;还原cx的内容

    LOOP NEXT1  ;cx-1

    MOV DX,OFFSET RES  ;res偏移地址装入DX
    MOV AH,09H
    INT 21H     ;输出字符串

    MOV AH,4CH
    INT 21H
    
CODE ENDS
    END START
