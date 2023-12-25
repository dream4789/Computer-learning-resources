;设置光标位置
setpos macro top,left
    mov ah,02h
    mov bx,0
    mov dh,top
    mov dl,left
    int 10h
endm

;修改菜单属性
changemenu macro top,left,width,attr
    local chg
    mov dl,left
chg:
    setpos top,dl
    mov bh,0
    mov ah,08h
    int 10h
    mov bl,attr
    mov cx,1
    mov ah,09h
    int 10h
    inc dl
    mov al,left
    add al,width
    cmp dl,al
    jne chg
    setpos top,left
endm

;绘制窗口
drawwindow macro attr,top,left,bottom,right
    push ax
    push bx
    push cx
    push dx
    mov ah,06h
    mov al,0
    mov bh,attr
    mov ch,top
    mov cl,left
    mov dh,bottom
    mov dl,right
    int 10h
    pop dx
    pop cx
    pop bx
    pop ax
endm

;绘制窗口上下边框
windowtandb macro l,m,r,top,left,width,attr
    setpos top,left
    outputchar l,attr,1
    setpos top,left+1
    outputchar m,attr,width-2
    setpos top,left+width-1
    outputchar r,attr,1
endm

;绘制窗口左右边框
windowlandr macro char,top,left,width,attr
    setpos top,left
    outputchar char,attr,1
    setpos top,left+width-1
    outputchar char,attr,1
endm

;输出字符
outputchar macro char,attr,num
    push ax
    mov bh,0
    mov ah,09h
    mov al,char
    mov bl,attr
    mov cx,num
    int 10h
    pop ax
endm

;输出字符串
outputstr macro str,num,top,left,attr
    push ax
    push bx
    push bp
    push cx
    push dx
    mov ah,13h
    lea bp,str
    mov cx,num
    mov dh,top
    mov dl,left
    mov bh,0
    mov al,1
    mov bl,attr
    int 10h
    pop dx
    pop cx
    pop bp
    pop bx
    pop ax
endm

;绘制子菜单
submenu macro left,menu1,num1,menu2,num2,menu3,num3,width
    local menu
    drawwindow 70h,1,left,5,left+width
    windowtandb 0dah,0c4h,0bfh,1,left,width+1,70h
    mov al,2
menu:
    windowlandr 0b3h,al,left,width+1,70h
    inc al
    cmp al,5;==================
    jne menu
    windowtandb 0c0h,0c4h,0d9h,5,left,width+1,70h
    outputstr menu1,num1,2,left+2,0fh
    changemenu 2,left+1,8,0fh
    outputstr menu2,num2,3,left+2,70h
    changemenu 3,left+2,1,74h
    outputstr menu3,num3,4,left+2,70h
    changemenu 4,left+2,1,74h
    setpos 2,left+2
endm

;读取屏幕内容
readscr macro left,memory
    local read
    sub ax,ax
    mov si,ax
read:
    add ah,left
    inc al
    inc si
    mov ch,ah
    setpos al,ch
    mov ah,08h
    mov bh,0
    int 10h
    mov memory[si],al
    mov memory[si+50],ah
    mov ax,si
    mov bl,10
    div bl
    cmp si,50
    jne read
endm

;写入屏幕
writescr macro left,memory
    local read
    sub ax,ax
    mov si,ax
read:
    add ah,left
    inc al
    inc si
    mov ch,ah
    setpos al,ch
    mov al,memory[si]
    mov ah,memory[si+50]
    mov dl,al
    mov dh,ah
    outputchar dl,dh,1
    mov ax,si
    mov bl,10
    div bl
    cmp si,50
    jne read
endm

;设置光标属性
showcur macro show
    push ax
    push cx
    mov ah,1
    mov cl,0
    mov ch,show
    int 10h
    pop cx
    pop ax
endm