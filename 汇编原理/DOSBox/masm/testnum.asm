DATAS SEGMENT
    CRLF    db 0AH, 0DH                     ,"$"  ;回车换行
    string  db "The original value was:"    ,"$"  ;原本数值输出提示
    string1 db "The binary form is:"        ,"$"  ;二进制输出提示
    string2 db "The octal number system is:","$"  ;八进制输出提示
    string3 db "The hexadecimal form is:"   ,"$"  ;十六进制输出提示
DATAS ENDS
 
STACKS SEGMENT stack
    ;此处输入堆栈段代码
STACKS ENDS
 
CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
  
  	;原来有符号数形式的输出
  	lea dx,string    ;原本数据的输出提示
  	mov ah,9
  	int 21h
   
    mov AX,123	
  	mov ax,-123
  	call symoutput
  	
  	lea dx,crlf
  	mov ah,9
  	int 21h
  	
  	;二进制形式的输出
  	lea dx,string1;二进制的输出提示                                       
    mov ah,9							 
    int 21h
	
  	mov ax,-123
  	call binaryoutput
  	
  	lea dx,crlf
  	mov ah,9
  	int 21h
  	
  	;八进制形式的输出
  	lea dx,string2;八进制的输出提示
  	mov ah,9
  	int 21h
   
  	mov ax,-123
  	call octaloutput
  	
  	lea dx,crlf
  	mov ah,9
  	int 21h
  	
  	;十六进制形式的输出
  	lea dx,string3;十六进制的输出提示
  	mov ah,9
  	int 21h
  	
  	mov ax,-123
  	call hexadecimaloutput
  	
  	lea dx,crlf
  	mov ah,9
  	int 21h	
	
    MOV AH,4CH
    INT 21H  


  
;二进制形式的输出,入口参数为ax
binaryoutput proc
  	push bx     ;数据入栈，保留数值
  	push dx	
   
  	mov dh,0    ;用于计数，总共16次
	
binaryagain:	
	  cmp dh,16
		je binaryover  ;输出结束，到达函数末端
  	rol ax,1       ;移动一位
  	mov bx,ax      ;数值保留
  	and ax,0001h   ;剥离出最后一位
  	mov dl,al      ;用于输出
  	add dl,48
  	mov ah,2
  	int 21h
  	inc dh         ;计数加一
  	mov ax,bx      ;数值恢复
		jmp binaryagain;再来一次		
	
binaryover:
  	pop dx         ;数据出栈，数值还原
  	pop bx
  	ret

binaryoutput endp


;八进制形式的输出，入口参数为ax
octaloutput proc
  	push bx;数据入栈，数值保留
  	push cx
  	push dx
  	
  	;最高一位单独输出处理
  	rol ax,1;移动一位
  	mov bx,ax;保留数值
  	and al,01h;剥离最后一位数据
  	mov dl,al;准备输出
  	add dl,48
  	mov ah,2
  	int 21h	
  	mov ax,bx;恢复数值
  	
  	;对后续的15位进行处理，15除3等于5
  	mov dh,0;计数5次，留下最后一位单独处理

octalagain:
	  cmp dh,5
		je octalover;循环结束，进入收尾工作
		inc dh;计数加一
  	mov cl,3;作为移位位数
  	rol ax,cl;移动最高三位
  	mov bx,ax;保留ax的值防止修改
  	and al,07h;剥离后三位数据
  	mov dl,al;准备输出
  	add dl,48
  	mov ah,2
  	int 21h
  	mov ax,bx;恢复ax的保留数值
		jmp octalagain;loop
 
octalover:	
  	pop dx;数据出栈，数值还原
  	pop cx
  	pop bx
  	ret

octaloutput endp


;十六进制形式的输出,入口参数为ax
hexadecimaloutput proc
  	push bx;数据入栈，数值保留
  	push cx
  	push dx
  	
  	mov dh,0;用于计数，总共4次
	
hexadecimalagain:
	  cmp dh,4
		je hexadecimalover;循环结束，进行收尾工作
		inc dh;计数加一
  	mov cl,4
  	rol ax,cl
  	mov cx,ax;数值保留
  	and ax,0fh;数据剥离后四位
  	mov dl,al
  	cmp dl,9;区分需要输出数字还是字母
		ja alphabet;作为字母输出
  	add dl,48;作为数字形式的输出
  	mov ah,2
  	int 21h	
  	mov ax,cx;数据恢复
		jmp hexadecimalagain
		
alphabet:;作为字母形式的输出
  	add dl,55
  	mov ah,2
  	int 21h
  	mov ax,cx;数据恢复
		jmp hexadecimalagain
 
hexadecimalover:		
  	pop dx;数据出栈，数值保留
  	pop cx
  	pop bx
  	ret

hexadecimaloutput endp
 
    
;有符号数的输出,入口参数为ax
symoutput proc
  	push bx;入栈保存
  	push dx
  	
  	mov bx,ax;保存数据防止后续修改,可直接调用函数
  	
  	cmp ax,0;比较ax中数字的正负
		js negative;负数的输出
		jmp positive;正数的输出
		
negative:
  	mov dl,'-';输出负号
  	mov ah,2
  	int 21h
  	
  	neg bx;求补数
  	call output
		jmp symoutputover 
	
positive:
	  call output
	
symoutputover:
  	pop dx;出栈复原
  	pop bx
  	ret

symoutput endp
 
    
;多位输出函数，入口参数为bx
output proc
  	push ax      ;数据入栈区
  	push cx
  	push dx
  	
  	;初始化变量
  	mov ax,bx    ;数据放入准备除法
  	mov cl,10    ;作为除数
  	mov ch,0     ;用于计数便于后续出栈输出
	
divagain:        ;除法数字剥离部分
	  cmp ax,0     ;判断是否已经除尽
		je divover
  	inc ch       ;计数器加1
  	div cl
  	push ax      ;入栈，提取的时候取用ah部分,存储余数（低位优先）
  	mov ah,0     ;调整ax
		jmp divagain ;再次除法剥离数字
		
divover:       ;出栈输出部分
	  cmp ch,0   ;判断数字是否已经出尽
		je outputover
  	pop ax     ;取用ah部分
  	mov dl,ah  ;输出部分
  	add dl,48
  	mov ah,2
  	int 21h
  	dec ch
		jmp divover 
		
outputover:     ;收尾部分
  	pop dx
  	pop cx
  	pop ax      ;数据出栈区
  	ret
output endp


CODES ENDS
    END START
 
 