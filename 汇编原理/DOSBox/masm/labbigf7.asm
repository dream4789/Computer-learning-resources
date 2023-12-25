;------------------------------------------------
;---     输入字母c实现画圆，有两种选择模式    ---
;---  1、输入圆心与半径 2、输入两点坐标为直径 ---
;------------------------------------------------
data segment
    shuc db 'please input C,I will draw a yuan for you: $'
    xuan db 'select moshi input 1 or 2: $'
    hua1 db 'input yuanxin and banjing(Must like:310,220 200): $'
    hua2 db 'input two point as zhijing(Must like:120,170 500,340): $'
    ero  db 'input error! please restart! $'
    zifu db 20 dup(0) ;此段用以临时存放输入字符
    shu  db 20 dup(0) ;再次存放输入数字的ASCII码转换华为的数字
    suan db 24 dup(0) ;用来存放计算圆过程中产生的临时数据
data ends

stack segment stack
    stk db 16 dup(0)
stack ends

code segment
    assume cs:code, ds:data, ss:stack
start:
    mov ax,data
    mov ds,ax
    ;mov ax,stack
    ;mov ss,ax
    mov dx,offset shuc ;显示输入C的提示字符
    call showmsg
        
    call input         ;输入字符c的处理
    mov al,ds:[si]
    and al,11011111b   ;便于大小写都识别，将字符转换成大写
    cmp al,43h
    jnz showero        ;如果不是C跳转到ero
        
    mov dx,offset xuan ;提示输入1或2的画圆方式
    call showmsg
            
    call input
    mov al,ds:[si]     ;比较选择画圆的方式
    cmp al,31h
    jz draw1
    cmp al,32h
    jz draw2
    call showero

;-----------------------------------------------------------
showero: ;输入错误提示
    mov dx,offset ero
    mov ah,9h
    int 21h
    mov ax,4c00h
    int 21h


draw1: ;第一种画圆方式，圆心坐标+半径
    mov dx,offset hua1
    call showmsg
    call input
    call zhuanshu
    call moshi
    mov bx,offset shu
    mov ax,ds:[bx]
    mov si,ax
    mov ax,ds:[bx+2]
    mov di,ax
    mov ax,ds:[bx+4]
    call drawyuan
    mov ax,4c00h
    int 21h

draw2: ;第二中画圆方式，两点坐标为直径
    mov dx,offset hua2
    call showmsg
    call input
    call zhuanshu
    call moshi
    mov bx,offset shu
    mov bp,offset zifu
    mov ax,ds:[bx]
    add ax,ds:[bx+4]
    shr ax,1
    mov si,ax ;圆心横坐标
    mov ax,ds:[bx+2]
    add ax,ds:[bx+6]
    shr ax,1
    mov di,ax ;圆心纵坐标
    mov ax,ds:[bx]
    sub ax,ds:[bx+4]
    shr ax,1
    xor dx,dx
    imul ax
    mov word ptr ds:[bp],ax
    mov word ptr ds:[bp+2],dx
    mov ax,ds:[bx+2]
    sub ax,ds:[bx+6]
    shr ax,1
    xor dx,dx
    imul ax
    add ax,word ptr ds:[bp]
    adc dx,word ptr ds:[bp+2]
    mov word ptr ds:[bp+4],ax ;保存半径的平方
    mov word ptr ds:[bp+6],dx
    mov cx,1000h ;用来找出半径值
    mov bx,0

zhao:
    mov ax,bx
    xor dx,dx
    mul ax
    cmp dx,word ptr ds:[bp+6]
    jnb ok
    cmp ax,word ptr ds:[bp+4]
    jnb ok
    inc bx
    loop zhao
ok:
    mov ax,bx
    call drawyuan
    mov ax,4c00h
    int 21h

;---------------------------------------------------------
input: ;实现键盘输入字符 
    mov bx,0
    mov cx,20
re: mov ah,1h ;DOS中断 键盘键入回显，al为字符
    int 21h
    cmp al,0dh ;0dh为回车的ASCII码
    jz scx
    mov si,offset zifu
    mov [bx][si],al ;将输入的字符放到zifu区
    inc bx
    loop re
    ret


;---------------------------------------------------------
scx: ;条件跳转时对cx设置
    mov cx,0
    ret
;----------------------------------------------------------
showmsg: ;用来显示提示字符
    mov ah,9h
    int 21h
    ret
    
;-----------------------------------------------------------
moshi: ;屏幕显示模式
    mov al,12h
    mov ah,0
    int 10h
    ret
;----------------------------------------------------------
zhuanshu: ;将输入的ascII码转为数字
    mov bx,offset zifu
    mov bp,offset shu
    mov cx,16
    mov si,0
    mov di,0
lei: ;此段代码比较啰嗦，但是达到目的就行！
    mov al,ds:[bx][si]
    cmp al,0
    jz scx
    sub al,30h
    mov dl,100
    mul dl
    mov word ptr ds:[bp][di],ax
    mov ax,0
    mov al,ds:[bx][si+1]
    sub al,30h
    mov dl,10
    mul dl
    add ax,word ptr ds:[bp][di]
    mov word ptr ds:[bp][di],ax
    mov ax,0
    mov al,ds:[bx][si+2]
    sub al,30h
    add ax,word ptr ds:[bp][di]
    mov word ptr ds:[bp][di],ax
    add si,4
    add di,2
    loop lei
    ret
;-----------------------------------------------------------
drawyuan: ;传入参数 ax半径，si，di圆心的横纵坐标
    mov bx,offset suan
    mov word ptr ds:[bx],si ;保存圆心横坐标
    mov word ptr ds:[bx+2],di ;保存圆心纵坐标
    sub si,ax
    mov word ptr ds:[bx+4],si ;保存起始点横坐标
    sub di,ax
    mov word ptr ds:[bx+6],di ;保存起始点纵坐标
    shl ax,1 ;直径
    mov cx,ax
    mov word ptr ds:[bx+10],ax ;保存直径
    shr ax,1
    xor dx,dx
    mul ax
    mov word ptr ds:[bx+12],ax
    mov word ptr ds:[bx+14],dx ;保存半径的平方
;-----------------此时 ax直径，bx计算过程的偏移地址，cx未用
;-----------------dx未用，si起始点横坐标，di起始点纵坐标
hang:
    push cx ;写像素的行与列分别是DX跟CX
    mov cx,ds:[bx+10]
    mov dx,di
    mov si,ds:[bx+4] ;每次循环前把横坐标放正
lie:
    push cx ;所以这个就比较蛋疼要压栈2次
    push dx
    xor dx,dx
    mov cx,si
    mov ax,si
    sub ax,ds:[bx]
    xor dx,dx ;乘之前将其清零
    imul ax
    mov word ptr ds:[bx+16],ax
    mov word ptr ds:[bx+18],dx
    mov ax,di
    sub ax,ds:[bx+2]
    xor dx,dx
    imul ax
    add ax,ds:[bx+16]
    adc dx,ds:[bx+18]
    mov word ptr ds:[bx+20],ax
    mov word ptr ds:[bx+22],dx
    pop dx
    mov ax,ds:[bx+22]
    cmp ax,ds:[bx+14]
    jne kong
    mov ax,ds:[bx+12]
    sub ax,ds:[bx+20]
    cmp ax,500 ;保留一定的像素误差范围
    ja kong ;若换成
    ; cmp ax,ds:[bx+20]
    ; jb kong
    ;则画实心圆
    mov ah,0ch
    mov al,5h ;1蓝，2绿，3浅蓝，4红、、、就不一个一个试了
    int 10h
kong:
    pop cx
    inc si
    loop lie
    pop cx
    inc di
    loop hang
    ret
;-------------------------------------------------
code ends
    end start