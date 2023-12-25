; 成绩统计程序
; 输入：89 32 35 21 34 12

data segment
    string1 db  ' please input score: $'
    string2 db  ' output score  : $'
    string3 db  ' | max score      | $'
    string4 db  ' | min score      | $'
    string5 db  ' | Passers-by     | $'
    string6 db  ' | Not Passer-by  | $'
    string7 db  ' | Average score  | $'
    string8 db  ' +----------------+-------+$' 
    string9 db  '  | $' 
    string0 db  'Press any key to continue...$'
       kong db  ' $' 
        pas dw  0000H
        npa dw  0000H
        avg dw  0000H
        num dw  0000H
       avg2 dw  0000H
      score dw  60 dup(0)
data ends

stack segment stack
    dw 64 dup(0)
stack ends

code segment
	  assume cs:code,ds:data,ss:stack

main proc far
start:

t:
  	call	ready
  	call	input
  	call	sort
  	call	count
  	call	output 
  	jmp   t

main endp

;========================ready=============================
ready:
    mov ax,data
    mov ds,ax               ;ds数据段寄存器
    
    mov ax,stack
    mov ss,ax               ;ss段寄存器
    
    mov dx,offset string1
    mov ah,09h
    int 21h
        
    ; bx,cx,si,di 清零
    xor bx,bx
    xor cx,cx
    xor si,si
    xor di,di
    ret

;==========================input==========================
input:
  	mov ah,1    ; 输入一个字符到AL（ascll码存储）ax=0100 -> 输入2 -> ax=0132
  	int 21h
   
  	cmp al,0dh  ; 如果是‘回车’ 跳转
  	jz  over
   
  	cmp al,20h  ; 如果是‘空格’ 跳转，数据存入score[si]中，bx清零
  	jz  save
   
  	sub al,30h  ; 是数字，ascll码减30h   -> ax=0102
  	mov cl,4    ;                        -> cx=0004
  	shl bx,cl   ; BX左移二进制4位(BX*16) -> bx=0000
  	add bl,al   ;                        -> bx=0002
  	jmp input

save:
  	mov score[si],bx ; 存入 score 中
  	add si,2         ; 指针+2
  	inc di
  	xor bx,bx        ; bx 清零
  	jmp input

over:
    mov score[si],bx 
    inc di
    
    mov dl,0ah
    mov ah,02h  ; 输出DL里的字符
    int 21h
    
    mov cx,di
    dec cx                 
    xor bx,bx 
    ret
;===========================sort=========================
sort:                           ;bx=0，用冒泡排序,bx为要改变的哪一位的坐标
  	mov si,2 
  	mov dx,cx

cmp2:
  	mov ax,score[bx]
  	cmp ax,score[bx+si]
  	jnc cmp3                    ;大于或相等时转
  	xchg ax,score[bx+si]     
  	mov score[bx],ax

cmp3:
  	add si,2 
  	dec dx                   
  	jnz cmp2
  	add bx,2
  	loop sort
  	mov dx,offset string2
   
  	mov ah,09h
  	int 21h
  	sub si,si                    ;si清零
  	ret

;==========================count==============================
count:                          ;si=0 
    mov num,di

count1:
    mov bx,score[si]
    xor ax,ax
    clc                         ;cf=0
    mov ax,avg
    add al,bl
    daa                     
    jc  avg1

y:            
    add ah,bh
    mov avg,ax 
    clc                         ;cf=0
    cmp bx,60H
    jl  NPass                   ;有符号，jl小于跳转
    jge Pass                    ;有符号，jgl大于等于跳转
    
avg1:                           ;高位加一
    add ah,1H
    daa
    jmp  y

x:
    add si,2 
  	dec di 
  	cmp di,0                   
  	jnz count1       
  	sub si,si                   
  	mov di,num                  
  	ret
   
NPass:  
    inc npa                     ;npa++
    jmp x
    
Pass:
    inc pas
    jmp x
    
;===========================output================================
output:                         ;si=0,di为输入的个数
    mov cx,di
output3:  ;-------sort output---------
  	mov bx,score[si] 
  	call    outputh1         
  	mov dl,20h                 
  	mov ah,02h
  	int 21h 
  	add si,2                   
  	dec di                  
  	cmp di,0 
  	jnz output3                
	
output2:
  	call    line_feed
  	; --------------max,min,pass,not pass output----- 
  	call hang
  	mov dx,offset string4
  	mov ah,09h
  	int 21h                     ;显示string4
  	mov bx,score[si-2] 
  	call    outputh1            ;输出score中最后一个数
  	call    hou                 ;格子封口
  	call    line_feed           ;回车换行
  	call    hang                ;输出+---------------+---------+
  	 
  	mov dx,offset string3
  	mov ah,09h
  	int 21h 
  	mov bx,score[0] 
  	call    outputh1
  	call    hou
  	call    line_feed
  	call    hang
  	
  	mov dx,offset string5
  	mov ah,09h
  	int 21h
  	mov bx,pas 
  	call    outputh1
  	call    hou
  	call    line_feed
  	call    hang
  	    
  	mov dx,offset string6
  	mov ah,09h
  	int 21h
  	mov bx,npa 
  	call    outputh1
  	call    hou
  	call    line_feed  
  	call    hang
  	
  	mov dx,offset string7
  	mov ah,09h
  	int 21h    
  	;---------10 to 16----------avg中是输入值的总和，以10进制保存，但计算是以16进制计算，
    mov bx,avg                  ;个位
    mov ah,0
    mov al,bl
    and al,0fh                  ;保留al低四位(个位)的值
    mov avg2,ax
    
    mov al,bl                   
    mov cl,4                    ;十位
    shr al,cl                 
    mov cl,10
    mul cl                      ;ax=al*cl 
    mov dx,0
    add avg2,ax                 
    
    mov al,bh                   ;百位
    and al,0fh                  ;保留ah低四位(百位)的值
    mov cx,100                  ;同上
    mul cx
    mov dx,0
    add avg2,ax 
    ;----------average-----------
    mov cx,num
    mov ax,avg2
    cwd                         
    div cx                      ;商放在ax中
    ;-------16 to 10-----------除完了，就恢复10进制保存，方便以后输出          ;
    mov bh,0
    mov cl,10
    div cl
    mov bl,ah                   ;余数(个位)给bl
    cmp al,0h                   
    jz  z
    cbw
    div cl
    mov dl,ah                   ;余数(十位)给dl
    mov cl,4
    shl dl,cl
    add bl,dl                   ;个位和十位放在一起,
    cmp al,0h
    jz  z
    mov cl,10
    cbw
    div cl
    mov bh,ah                   ;将百位放入bh前
z:
    call outputh1
    call    hou
    call line_feed 
    call hang
    call line_feed
    mov dx,offset string0
  	mov ah,09h
  	int 21h
    mov ah,01h
    int 21h
    
    mov avg,0
    mov avg2,0
    mov npa,0
    mov pas,0
         
    mov al,0 
    mov bh,07
    mov cx,0 
    mov dh,40 
    mov dl,60
    mov ah,06h 
    int 10h 
    mov bh,0 
    mov dh,0 
    mov dl,0
    mov ah,02h 
    int 10h
    ret
    
  	mov ah,4ch
  	int 21h	
;--------------------输出-------------------	
outputh1:
    mov ch,1                ;用于判断前面是否全为0
  	mov dl,bh
  	mov cl,4 
  	shr dl,cl               ;千位，
  	cmp dl,0                ;dl为零，不输出
  	jz  out01
  	mov ch,0
  	add dl,30h
  	mov ah,02h
  	int 21h
  	jmp outputh2            ;为了跳过out01
out01:                      
  	mov dx,offset kong
  	mov ah,09h
  	int 21h
outputh2: 
  	mov dl,bh 
  	and dl,0fh              ;百位
  	cmp ch,0                
  	jz  outputh21
  	cmp dl,0                
  	jz  out02

outputh21:
    mov ch,0
  	add dl,30h
  	mov ah,02h
  	int 21h
  	jmp outputl1
out02:
  	mov dx,offset kong
  	mov ah,09h
  	int 21h
outputl1:
  	mov dl,bl
  	mov cl,4 
  	shr dl,cl               ;十位
  	cmp ch,0
  	jz  outputl11           ;同上
  	cmp dl,0
  	jz  out03
outputl11: 
  	add dl,30h
  	mov ah,02h
  	int 21h
  	jmp outputl2
out03:
  	mov dx,offset kong
  	mov ah,09h
  	int 21h
outputl2: 
  	mov dl,bl 
  	and dl,0fh              ;个位
  	add dl,30h
  	mov ah,02h
  	int 21h
  	ret
line_feed: ;--------------换行-----------
    mov dl,0ah
  	mov ah,02h
  	int 21h
  	mov	dl,0dh
    mov	ah,02h
    int	21h
    ret
hang:                       ;输出|----------------+----------
    mov dx,offset string8
  	mov ah,09h
  	int 21h
  	call line_feed 
  	ret
hou:                       ;显示      |
    mov dx,offset string9
  	mov ah,09h
  	int 21h
  	ret
code 	ends
	  end	start
