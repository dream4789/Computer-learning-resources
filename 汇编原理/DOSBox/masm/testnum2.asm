; 输出16进制，原样输出AX里的
STACK SEGMENT STACK
    DW 64 DUP(?)
STACK ENDS

DATAS segment
    Temp db '0000H','$'
DATAS ends

CODES segment
    ASSUME CS:CODES, DS:DATAS, SS:STACK
START:
    mov AX,DATAS
    mov DS,AX

    ;mov AX,12ABH        ;设置需要显示的AX的值
    mov AX,5050          ;输出13BA
    
    
    ;call symoutput
    call dec_out1        ; 可以输出很大的数
    
    mov ah,4CH
    int 21H

; 可以输出很大十进制数
dec_out1 proc near
    push ax
    push bx
    push cx
    push dx

    
    mov bx,10
    mov cx,0

yazhan:
    mov dx,0
    div bx
    
    push dx
    inc cx
    
    cmp ax,0
    jz chuzhan
    
    jmp yazhan
    
chuzhan:
    pop dx
    add dl,30h
    mov ah,2            
    int 21h
           
    loop chuzhan
    
    pop dx
    pop cx
    pop bx
    pop ax
    
    ret
dec_out1 endp


;无符号十进制输出
symoutput proc
    mov si,offset Temp+3;保存存储结果的字符串的最后一个字符偏移地址
    xor cx,cx           ;对cX清零
    mov cl,4            ;设置循环次数为4次

MainPart:
    mov DH,AL           ;将Al的内容传送给DH

    shr AX,1
    shr AX,1
    shr AX,1
    shr AX,1
                ;上述4句为使AX逻辑右移4位 理论上可以写成 shr AX ,cl(cl设置为4)
                ;但这个地方cl要记录循环次数每次循环会是cl-1所以无法满足正常的移位需要
    and dh,0FH
    add dh,30H
    cmp dh,':'  ;':'的ASCII比9大1 而字母的ASCII码与数字的ASCII码中间隔了7个其它字符
    ja isLetter ;如果为字母则跳转
    jb No       ;如果不是

isLetter:
    add dh,7H   ;ASCII码加7变为字母
    
No:
    mov [si],dh ;将字符存入,待存放内容的字符串的对应位置
    dec si      ;待存放内容的内存地址自减1
    loop MainPart

print:
    mov dx,offset Temp  ;将带打印的字符串的偏移地址存放进dx中
    mov ah,09           ;设置DOS 09号功能
    int 21H         ;功能调用
    mov al,0
    
    ret
symoutput endp


CODES ends
    end START