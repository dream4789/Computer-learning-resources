;默认采用ML6.11汇编程序
DATAS SEGMENT
    pro18 db "*******************************************************************************$"
    buf0  db "*                              MENU                                           *$"
    buf1  db "*                 1 Results entry and output.                                 *$"    ;;;成绩录入并输出
    buf3  db "*                 2 Sort by grade point average.                              *$"    ;;;;按平均分排序
    buf4  db "*                 3 Counting the number of people in each score band.         *",10,13,
             "*                 4 Bar chart display.                                        *$"
    buf5  db "*                 5 Exit                                                      *",10,13,  ;;;;退出
    		     "*******************************************************************************$"
    pro22 db "********************************************************************************"
          db "*                              MENU                                            *"
          db "*                 1 Results entry and output.                                  *"    ;;;成绩录入并输出
          db "*                 2 Sort by grade point average.                               *"    ;;;;按平均分排序
          db "*                 3 Counting the number of people in each score band.          *"
    	    db "*                 4 Bar chart display.                                         *"
          db "*                 5 Exit                                                       *"    ;;;;退出
    	    db "********************************************************************************"
    len equ $-pro22
    
    buf   db 10,13,"$"
    pro1  db "Please enter the number before the command you want to do:$"
    pro2  db "Please enter a number between 1 and 3.$"
    pro3  db "---------------------------Ranking-----------------------------------",10,13,
    		     "name     number    Chinese  Maths    English  Total  Average  Ranking$"
    pro21 db "---------------------------------------------------------------------$"
    pro4  db "Please enter the number of students:$"
    pro5  db "Please enter the name of the student which $"
    pro6  db "Please enter the number of the student which $"
    pro7  db "Please enter the Chinese/Maths/Einglish results of the student which $"
    pro8  db "Please enter a number between 0 and 9.$"
    pro9  db "Please enter a number between 0 and 100.$"
    pro10 db "----------------------Information----------------------------"         ,10,13,
    		     "name     number    Chinese  Maths    English  Total  Average$"
    pro11 db "Please enter 8 digits:$"
    pro12 db "Please enter the number of students up to ten:$"
    pro20 db "-------------------------------------------------------------$"
    pro17 db "----------------------Statistics----------------------------|$"
    pro13 db 20h,20h,20h,20h,20h,20h,20h,20h,20h,"|0    10   20   30   40   50   60   70   80   90   |",10,13,
             20h,20h,20h,20h,20h,20h,20h,20h,20h,"||     |    |    |    |    |    |    |    |    |   |",10,13,
             20h,20h,20h,20h,20h,20h,20h,20h,20h,"|10   20   30   40   50   60   70   80   90  100   |",10,13,
             "---------","|--------------------------------------------------|$"
    pro19 db "------------------------------------------------------------|$"
    pro14 db "Chinese",20h,20h        ,"|","$"
    pro15 db "Maths"  ,20h,20h,20h,20h,"|","$"
    pro16 db "English",20h,20h        ,"|","$"
    
    num      db ?        ;;;学生人数
    x        dw ?
    y        db ?
    z        dw ?
    cxl      db ?
    cxh      db ?
    ten      db 10
    TEN_1    DW 10
    change_a dw ?
    change_b dw ?
    panking  db 0
    m        db 21
    n        db 21
    q        db 8
    p        db 11
    k        db 6
    thirty   db 30
    
    name_arr   db 20,?, 21 dup ("$")           ;;;;;数据输入
    number_arr db 20,?,21 dup ("$")
    score_arr  db 8 dup ("$")            ;;;语 数 英 总 平均 排名
    ;score_len_arr db 8 dup ("$")
    
    name_total      db 10 dup (21 dup ("$"))       ;;;;;数据保存
    number_total    db 10 dup (21 dup ("$"))
    score_total     db 10 dup (8 dup ("$"))
    remainder_total db 10 dup ("$")          ;;;余数
    
    name_1   db 21 dup ("$")       ;;;交换
    number_1 db 21 dup ("$")
    score_1  db  8 dup ("$")
    
    name_length db 10 dup ("$")              ;;;姓名长度
    Statistics  db 3 dup (11 dup (0))       ;;;各段人数
    ;Statistics_2    db 3 dup (6 dup (0))       ;;;各段人数
    ;score_len_total db 10 dup (8 dup ("$"))
    ;score_length    db 10 dup("$") 
DATAS ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES, DS:DATAS, SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    mov es,ax
    
STR_TIP macro n      ;;;;宏-输出提示-9号
    mov ah,9
    mov dx,offset n
    int 21h
    call spr
endm

STR_TIP_N macro n      ;;;;宏-输出提示-无回车换行-9号
  	mov ah,9
  	mov dx,offset n
  	int 21h
endm

INPUT_10 macro marker   ;;;;宏-输入-10号
  	mov ah,10
  	lea dx,marker
  	int 21h
endm

OUTPUT_2 macro marker    ;;;;宏-输出-2号
  	mov ah,2
  	mov dl,marker
  	int 21h
endm
    
;########画细点宏########
;参数：页面、Y坐标、X坐标、颜色，通过将AH放入0CH,通过10H中断来描点
;0黑色 1蓝色 2绿色 3青色 4红色 5紫色 6橙色 7白色 8灰色
POINT_THIN MACRO PAGE,ROW,COLUMN,COLOR            ;;;宏-画点
		PUSH AX
		PUSH BX
		PUSH CX
		PUSH DX
		MOV AH,0CH
		MOV AL,COLOR
		MOV BH,PAGE
		MOV DX,ROW
		MOV CX,COLUMN
		INT 10H
		POP DX
		POP CX
		POP BX
		POP AX
ENDM 
    
;########画横线宏，参数：X坐标、Y坐标、长度、颜色
DRAWLINE1 MACRO COLUMN,ROW,FREE_LENGTH,COLOR             ;;;宏-横线
		LOCAL LIN1 
		PUSH CX            ;;;保护cx,si
		PUSH SI
		MOV  CX,FREE_LENGTH
		MOV  SI,COLUMN
LIN1:
    POINT_THIN 0,ROW,SI,COLOR
		INC  SI
		LOOP LIN1
		POP  SI
		POP  CX
endm
    
    ;画任意两点间线宏。参数：起点X、起点Y、终点X、终点Y、颜色
LINE MACRO X1,Y1,X2,Y2,COLOR                         ;;;宏-任意两点间直线
       	LOCAL EXIT
       	LOCAL LINEZHENG,LINEFUN
       	LOCAL LINEZHENGZHENG,LINEZHENGFUN
       	LOCAL LINEFUNZHENG,LINEFUNFUN
       	LOCAL LINE1,LINE2,LINE3
       	LOCAL LINE11,LINE12,LINE13
       	LOCAL LINE21,LINE22,LINE23
       	LOCAL LINE31,LINE32,LINE33
       	PUSH AX
       	PUSH BX
       	PUSH CX
       	PUSH DX
       	PUSH SI
       	PUSH DI
       	MOV SI,0
       	MOV DI,0
       	MOV AX,X1
       	MOV BX,X2
       	MOV CX,Y1
       	MOV DX,Y2
       	CMP AX,BX
       	JA LINEFUN
LINEZHENG:
       	CMP CX,DX
       	JA  LINEZHENGFUN
LINEZHENGZHENG:
       	MOV AH,0CH
       	MOV AL,COLOR
       	MOV BH,0
       	MOV CX,X1
       	MOV DX,Y1
LINE1:	ADD SI,(Y2-Y1)
      	CMP SI,(X2-X1)
      	JBE LINE2
      	SUB SI,(X2-X1)
      	INC DX
LINE2:	ADD DI,(X2-X1)
      	CMP DI,(Y2-Y1)
      	JBE LINE3
      	SUB DI,(Y2-Y1)
      	INC CX
LINE3:  INT 10H
      	CMP CX,X2
      	JB LINE1
      	LEA BX,EXIT
      	JMP BX
LINEZHENGFUN:	
        MOV AH,0CH
       	MOV AL,COLOR
       	MOV BH,0
       	MOV CX,X1
       	MOV DX,Y1
LINE11:	ADD SI,(Y1-Y2)
      	CMP SI,(X2-X1)
      	JBE LINE12
      	SUB SI,(X2-X1)
   	    DEC DX
LINE12:	ADD DI,(X2-X1)
      	CMP DI,(Y1-Y2)
      	JBE LINE13
      	SUB DI,(Y1-Y2)
      	INC CX
LINE13:	INT 10H
      	CMP CX,X2
      	JB LINE11
      	LEA BX,EXIT
      	JMP BX
LINEFUN:MOV CX,Y1
       	MOV DX,Y2
       	CMP CX,DX
       	JA LINEFUNFUN
LINEFUNZHENG:	
        MOV AH,0CH
       	MOV AL,COLOR
       	MOV BH,0
       	MOV CX,X1
       	MOV DX,Y1
LINE21:	ADD SI,(Y2-Y1)
       	CMP SI,(X1-X2)
       	JBE LINE22
       	SUB SI,(X1-X2)
       	INC DX
LINE22:	ADD DI,(X1-X2)
       	CMP DI,(Y2-Y1)
       	JBE LINE23
       	SUB DI,(Y2-Y1)
       	DEC CX
LINE23:	INT 10H
       	CMP CX,X2
       	JA LINE21
       	JMP EXIT
LINEFUNFUN:	
        MOV CX,X1
       	MOV DX,Y1
       	MOV AH,0CH
       	MOV AL,COLOR
       	MOV BH,0
LINE31:	ADD SI,(Y1-Y2)
       	CMP SI,(X1-X2)
       	JBE LINE32
       	SUB SI,(X1-X2)
       	DEC DX
LINE32:	ADD DI,(X1-X2)
       	CMP DI,(Y1-Y2)
       	JBE LINE33
       	SUB DI,(Y1-Y2)
       	DEC CX
LINE33:	INT 10H
       	CMP CX,X2
       	JA LINE31
EXIT:	  POP DI
       	POP SI
       	POP DX
       	POP CX
       	POP BX
       	POP AX
ENDM
	
;;;;;;;;;参数：30，31，40，41
HISTOGRAM macro para1,para2,para3,para4,para5   ;;;;;;;画柱状图;;;;;;;;;;;;;;;;;;;;;;;
	.if al==1
		LINE para1,400,para2,370,para5
		DRAWLINE1 para2,370,10,para5
		LINE para3,400,para4,370,para5
	.elseif al==2
		LINE para1,400,para2,340,para5
		DRAWLINE1 para2,340,10,para5
		LINE para3,400,para4,340,para5
	.elseif al==3
		LINE para1,400,para2,310,para5
		DRAWLINE1 para2,310,10,para5
		LINE para3,400,para4,310,para5
	.elseif al==4
		LINE para1,400,para2,280,para5
		DRAWLINE1 para2,280,10,para5
		LINE para3,400,para4,280,para5
	.elseif al==5
		LINE para1,400,para2,250,para5
		DRAWLINE1 para2,250,10,para5
		LINE para3,400,para4,250,para5
	.elseif al==6
		LINE para1,400,para2,220,para5
		DRAWLINE1 para2,220,10,para5
		LINE para3,400,para4,220,para5
	.elseif al==7
		LINE para1,400,para2,190,para5
		DRAWLINE1 para2,190,10,para5
		LINE para3,400,para4,190,para5
	.elseif al==8
		LINE para1,400,para2,160,para5
		DRAWLINE1 para2,160,10,para5
		LINE para3,400,para4,160,para5
	.elseif al==9
		LINE para1,400,para2,130,para5
		DRAWLINE1 para2,130,10,para5
		LINE para3,400,para4,130,para5
	.elseif al==10
		LINE para1,400,para2,100,para5
		DRAWLINE1 para2,100,10,para5
		LINE para3,400,para4,100,para5
	.endif
endm
  	
HISTOGRAM_HONG_1 macro
  .if bx==0     
		HISTOGRAM 30,31,40,41,1
	.elseif bx==1
		HISTOGRAM 80,81,90,91,1
	.elseif bx==2
		HISTOGRAM 130,131,140,141,1
	.elseif bx==3
		HISTOGRAM 180,181,190,191,1
	.elseif bx==4
		HISTOGRAM 230,231,240,241,1
	.elseif bx==5
		HISTOGRAM 280,281,290,291,1
	.elseif bx==6
		HISTOGRAM 330,331,340,341,1
	.elseif bx==7
		HISTOGRAM 380,381,390,391,1
	.elseif bx==8
		HISTOGRAM 430,431,440,441,1
	.elseif bx==9
		HISTOGRAM 480,481,490,491,1
	.endif
endm
  
HISTOGRAM_HONG_2 macro
  .if bx==11     
		HISTOGRAM 40,41,50,51,5
	.elseif bx==12
		HISTOGRAM 90,91,100,101,5
	.elseif bx==13
		HISTOGRAM 140,141,150,151,5
	.elseif bx==14
		HISTOGRAM 190,191,200,201,5
	.elseif bx==15
		HISTOGRAM 240,241,250,251,5
	.elseif bx==16
		HISTOGRAM 290,291,300,301,5
	.elseif bx==17
		HISTOGRAM 340,341,350,351,5
	.elseif bx==18
		HISTOGRAM 390,391,400,401,5
	.elseif bx==19
		HISTOGRAM 440,441,450,451,5
	.elseif bx==20
		HISTOGRAM 490,491,500,501,5
	.endif
endm
  
HISTOGRAM_HONG_3 macro
  .if bx==22    
		HISTOGRAM 50,51,60,61,6
	.elseif bx==23
		HISTOGRAM 100,101,110,111,6
	.elseif bx==24
		HISTOGRAM 150,151,160,161,6
	.elseif bx==25
		HISTOGRAM 200,201,210,211,6
	.elseif bx==26
		HISTOGRAM 250,251,260,261,6
	.elseif bx==27
		HISTOGRAM 300,301,310,311,6
	.elseif bx==28
		HISTOGRAM 350,351,360,361,6
	.elseif bx==29
		HISTOGRAM 400,401,410,411,6
	.elseif bx==30
		HISTOGRAM 450,451,460,461,6
	.elseif bx==31
		HISTOGRAM 500,501,510,511,6
	.endif
endm
  
;;;;;;;;;;;;;;;;;;;;;;主程序;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
call menu   ;;;输出菜单
call spr    ;;;回车换行
;call spr
;call spr
;call spr
;call spr
;call spr
;call spr
;call spr
;call spr
	
lp1:	
    STR_TIP_N pro1   ;;;;选择菜单
  	mov ah,1
  	int 21h
  	sub al,30h
  	call spr
  	call spr
	
  	.if al<1||al>5    ;;;容错判断
    		STR_TIP pro2
    		jmp lp1
  	.elseif al==1
    		call Subroutine1
    		jmp lp1
  	.elseif al==2
    		call Subroutine3
    		jmp lp1
  	.elseif al==3
  	  	call Statistics2
  		  jmp lp1
  	.elseif al==4
  	  	call Statistics4
  		  jmp lp1
  	.elseif al==5
  		  jmp exit
  	.endif
  	
  	call spr
    
exit:    
    MOV AH,4CH
    INT 21H



;;;;;;;;;;;;;;;;;;;;;;;;子程序;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
spr proc near    ;;;;;;子程序-空格回车
    mov ah,9
    mov dx,offset buf
    int 21h
    ret
spr endp




sprr proc near    ;;;;;;子程序-空格
    mov ah,2
    mov dx," "
    int 21h
    ret
sprr endp




input_1 proc near ;;;;;;;子程序-输入-1号-没有减30h
    mov ah,1
    int 21h
    ret
input_1 endp




menu proc near    ;;;;;;;;子程序——菜单输出
    ;push ax
    ;push si
    ;push di
    ;push cx
    ;mov ax,0b800h
    ;mov es,ax             ;;;将显存给es
    ;mov si,offset pro22
    ;mov di,0 
    ;mov cx,len
;s1:    
    ;mov al,ds:[si]    ;源字符
    ;mov es:[di],al    ;显示目标字符体

    ;mov al,73h        ;颜色
    ;mov es:[di+1],al;设置目标字符颜色

    ;inc si                  ;db 一个字符一个字节
    ;add di,2          ;显存 一个字符两个字节:偶字符体，奇字符颜色
    ;loop s1
    ;pop cx
    ;pop di
    ;pop si
    ;pop ax
    STR_TIP pro18
    STR_TIP buf0
    STR_TIP buf1
    STR_TIP buf3
    STR_TIP buf4
    STR_TIP buf5
    ret
menu endp
    
Subroutine1 proc near   ;;;子程序--成绩录入并输出
;;;;;;;;;;;;;;;;;输入
STR_TIP_N pro4          ;;;输入学生数量
su1_0:    
    call input_1            ;;;1号功能输入
  	sub al,30h
  	mov y,al
    .if al<=0||al>9
      	call spr
      	STR_TIP_N pro12
      	jmp su1_0
    .endif
    mov al,y
      
    mov num,al              ;;;学生数量存入num
    call spr
    
    mov bx,1                     
su1_1:    
    mov x,bx   ;;;;保护bx数据 
  	STR_TIP_N pro5   ;;;输入提示-姓名
  	mov cl,bl     ;;;cl---1/2/3
  	add cl,30h
    OUTPUT_2 cl
    OUTPUT_2 ":"
    INPUT_10 name_arr
    call spr
    mov bl,name_arr+1
    mov bh,0
    mov bp,x
    dec bp
    mov name_length[bp],bl      ;;;;;收集输入姓名的长度
    mov name_arr[bx+2],0
    
    STR_TIP_N pro6   ;;;输入提示-学号
    OUTPUT_2 cl
    OUTPUT_2 ":"
su1_19:    
    INPUT_10 number_arr
    mov al,number_arr+1
    .if al!=8
      	call spr
      	STR_TIP_N pro11
      	jmp su1_19
    .endif
    call spr
    mov bl,number_arr+1
    mov bh,0
    mov number_arr[bx+2],0
    
    STR_TIP_N pro7   ;;;输入提示-成绩
    OUTPUT_2 cl
    OUTPUT_2 ":"
    ;mov si,0
    mov cx,3
    mov si,0
su1_5:
    mov bx,0            ;;;;;;;三个数  语数英成绩
su1_2:    
    call input_1   ;;;循环输入成绩（（（0*10）+1）*10+2）*10+3...  ;;;;;;;;一个数
  	cmp al,20h
  	je exit_1
  	cmp al,0Dh
  	je exit_1
  	sub al,30h
  	.if al<0||al>9
  		  jmp su1_3
  	.endif
  	mov ah,0
  	xchg bx,ax
  	mul ten
  	add ax,bx
  	mov bx,ax
  	cmp bx,100
  	ja su1_4
    jmp su1_2
su1_3:	
    STR_TIP pro8
		jmp su1_5
su1_4:	
    STR_TIP	pro9
    jmp su1_5
exit_1:	
    mov score_arr[si],bl
  	inc si
  	call Circulation
  	loop su1_5

    mov bx,0   
    mov al,score_arr[bx]
    add al,score_arr[bx+1]
    mov cl,score_arr[bx+2]
    mov ah,0
    mov ch,0
    add ax,cx
    mov word ptr score_arr[bx+3],ax          ;;;;总分
    
    mov dx,0
    mov cx,3
    idiv cx
    mov score_arr[bx+5],al          ;;;;平均分 
    mov bx,x
    dec bx
    .if dl==1
    	  mov dl,3
    .elseif dl==2
      	mov dl,7
    .endif 
    mov remainder_total[bx],dl         ;;;;余数
    	  	
    ;;;;;;将数据存入total当中
    mov bx,x
    sub bx,1
    mov cl,name_arr+1
    mov ax,bx
    mul m     ;;;bx*21
    mov bx,ax
    lea di,name_total[bx]     ;;;目的
    lea si,name_arr+2        ;;;源
    cld
    rep movsb
    
    mov bx,x
    sub bx,1
    mov cl,number_arr+1
    mov ax,bx
    mul n     ;;;bx*9
    mov bx,ax
    lea di,number_total[bx]          ;;;学号
    lea si,number_arr+2
    cld
    rep movsb
    
    mov cx,7
    mov bx,x
    sub bx,1
    mov ax,bx
    mul q     ;;;bx*7
    mov bx,ax
    lea di,score_total[bx]          ;;;成绩    
    lea si,score_arr
    cld
    rep movsb
    
    mov bx,x
    inc bx
    cmp bl,num
    jbe su1_1
    STR_TIP pro10
    call print
    ret
Subroutine1 endp





Circulation proc near     ;;;;;;;;;;;;;;;;;;;子程序-循环;;;;;;;;;;;;;;;;;;;;;;;;;;
    .if bx>=0 && bx<10
			mov z,0
			;mov z,ax
			call Statistics1
		.elseif bx>=10 && bx<20
			mov ax,1
			mov z,ax
			call Statistics1
		.elseif bx>=20 && bx<30
			mov ax,2
			mov z,ax
			call Statistics1
		.elseif bx>=30 && bx<40
			mov ax,3
			mov z,ax
			call Statistics1
		.elseif bx>=40 && bx<50
			mov ax,4
			mov z,ax
			call Statistics1
		.elseif bx>=50 && bx<60
			mov ax,5
			mov z,ax
			call Statistics1
		.elseif bx>=60 && bx<70
			mov ax,6
			mov z,ax
			call Statistics1
		.elseif bx>=70 && bx<80
			mov ax,7
			mov z,ax
			call Statistics1
		.elseif bx>=80 && bx<90
			mov ax,8
			mov z,ax
			call Statistics1
		.elseif bx>=90 && bx<=100
			mov ax,9
			mov z,ax
			call Statistics1
		.endif	
		;mov ax,10
		;mov z,ax
		;mov bp,cx
		;dec bp
		;mov ax,bp
		;mul p
		;mov bp,ax
		;mov Statistics[bp+si],"$"
    ret
Circulation endp




 
Statistics1 proc near    ;;;;;;;;;;;子程序-统计人数;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov bp,si
    ;mov ah,2
    ;mov dx,bp
    ;add dl,30h
    ;int 21h
    dec bp
    mov ax,bp
    mul p
    add ax,z     ;;;可以正确输出z
    ;mov ah,2
    ;mov dx,z
    ;add dl,30h
    ;int 21h
    mov bp,ax
    
    inc Statistics[bp]
    ret
Statistics1 endp




print proc near     ;;;;;;;;;;;;;;;;子程序-输出;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	  mov bx,0
su1_6:	
    mov x,bx	
  	mov ax,bx
  	mul m
  	mov bx,ax
  	mov ah,9
  	lea dx,name_total   ;;;;姓名
  	add dx,bx
  	int 21h
  	
  	mov cx,9            ;;;;;;;;;;;;;;;;;对齐位置
  	mov bx,x            ;;;x从0开始
  	sub cl,name_length[bx]    
  	;add cl,30h
  	;OUTPUT_2 cl
su11:	
    call sprr
  	loop su11
  	
  	mov bx,x
  	mov ax,bx
  	mul n
  	mov bx,ax
  	mov ah,9
  	lea dx,number_total   ;;;;学号
  	add dx,bx
  	int 21h
  	
  	mov cx,2            ;;;;;;;;;;;;;;;;;对齐位置
su12:	
    call sprr
  	loop su12
  	
  	;;;;;;;;;;;;;;;;语数英
  	
  	mov bx,x            ;;;;bx=0
  	mov ax,bx           ;;;;ax=0
  	mul q               ;;;;ax*q=0
  	mov bx,ax           ;;;;bx=0
  	mov cx,3            ;;;;cx=3
su1_9:	
    mov z,cx                ;;;z=6       
		mov al,score_total[bx]        ;;;al=score_total+0
		mov y,0                       ;;;判断位数     y=0    
su1_7:	
    mov ah,0
		mov dx,0         
		idiv TEN_1                      ;;;dx:ax/10    
		push dx                       ;;;dx=8
		inc y                         ;;;y=1
		cmp ax,10                     ;;;ax>10?
		jge su1_7
		cmp ax,0                      ;;;判断是否是一位数，是的话ax=0,则y不增加，0不入栈
		je su1_15
		push ax
		inc y
su1_15:	
    mov dh,y           ;;;保存位数
su1_8:	
		mov ax,0	           ;;;;输出语数英三科成绩
		pop ax
		dec y
		add al,30h
		OUTPUT_2 al
		cmp y,0
		ja su1_8
		
		mov cx,9
		sub cl,dh   ;;;;;;;;;;;;;;;;;对齐位置
su13:	
    call sprr
		loop su13
		
		inc bx
		mov cx,z
		loop su1_9
		
  	;;;;;;;;;;;;;;;总成绩
  	mov bx,x            ;;;;bx=0
  	mov ax,bx           ;;;;ax=0
  	mul q               ;;;;ax*q=0
  	mov bx,ax           ;;;;bx=0
  	add bx,3
  	mov ax,word ptr score_total[bx]          
  	mov y,0             ;;;判断位数     y=0    
su1_10:	
    mov dx,0         
  	idiv TEN_1                         
  	push dx                       
  	inc y                         
  	cmp ax,10                     
  	jge su1_10
  	cmp ax,0                      ;;;判断是否是一位数，是的话ax=0,则y不增加，0不入栈
  	je su1_16
  	push ax
  	inc y
su1_16:	
    mov dh,y
su1_11:	
  	mov ax,0	           ;;;;输出总成绩
  	pop ax
  	dec y
  	add al,30h
  	OUTPUT_2 al
  	cmp y,0
  	ja su1_11
  	
  	mov cx,7            ;;;;;;;;;;;;;;;;;对齐位置
  	sub cl,dh
su14:	
    call sprr
	  loop su14
	
  	;;;;;;;;;;;;;;;平均成绩
  	mov bx,x            ;;;;bx=0
  	mov ax,bx           ;;;;ax=0
  	mul q               ;;;;ax*q=0
  	mov bx,ax           ;;;;bx=0
  	add bx,5
  	mov al,score_total[bx]          
  	mov y,0           ;;;判断位数     y=0    
su1_12:	
    mov ah,0
  	mov dx,0         
  	idiv TEN_1                         
  	push dx                       
  	inc y                         
  	cmp ax,10                     
  	jge su1_12
  	cmp ax,0                      ;;;判断是否是一位数，是的话ax=0,则y不增加，0不入栈
  	je su1_17
  	push ax
  	inc y
su1_17:   
    mov dh,y 		
su1_13:	  
    mov ax,0	           ;;;;输出平均成绩
  	pop ax
  	dec y
  	add al,30h
  	OUTPUT_2 al
  	cmp y,0
  	ja su1_13
  	OUTPUT_2 "."
  	mov bx,x
  	mov cl,remainder_total[bx]
  	add cl,30h
  	OUTPUT_2 cl
	
  	mov cx,7            ;;;;;;;;;;;;;;;;;对齐位置
  	sub cl,dh
su18:	
    call sprr
  	loop su18
  	
  	cmp panking,0          ;;;;判断是否要输出排名
  	je pr_exit
  	
  	mov bx,x            ;;;;bx=0
  	mov ax,bx           ;;;;ax=0
  	mul q               ;;;;ax*q=0
  	mov bx,ax           ;;;;bx=0
  	add bx,6
  	mov al,score_total[bx]          
  	mov y,0                       ;;;判断位数     y=0    
prr_1:	
    mov ah,0
  	mov dx,0         
  	idiv TEN_1                         
  	push dx                       
  	inc y                         
  	cmp ax,10                     
  	jge prr_1
  	cmp ax,0                      ;;;判断是否是一位数，是的话ax=0,则y不增加，0不入栈
  	je prr_2
  	push ax
  	inc y
  		
prr_2:	
    mov ax,0	           ;;;;输出排名
  	pop ax
  	dec y
  	add al,30h
  	OUTPUT_2 al
  	cmp y,0
  	ja prr_2
	
pr_exit:
  	call spr
  	
  	mov bx,x
  	inc bx
  	cmp bl,num
  	jb su1_6
  	cmp panking,0
  	je prr_3
  	STR_TIP pro21
  	jmp exit_prr
prr_3:	
    STR_TIP pro20
exit_prr:
    ret
print endp




Subroutine3 proc near   ;;;子程序--按总成绩排序;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    cmp num,1
    je su3_exit
    mov bx,0       ;;;;内循环标志   bx=0
    mov cl,num       ;;;;;内循环    cl=3
    mov y,cl     ;;;y=3
    mov ch,num      ;;;;;外循环  
    dec ch          ;;;;  ch=2
    mov cxh,ch       ;;;cxh=2
    
su3_3:   
    mov bx,0    ;;;bx=0 
	  mov bp,bx         ;;;bp=0   
    mov ax,bx         
    mul q
    mov bx,ax      ;;;bx=0*9
    
    dec y          ;;;y=2
    mov cl,y       ;;;cl=2 
    mov cxl,cl     ;;;cxl=2
su3_2:	
    mov ax,word ptr score_total[bx+3]      ;;;ax=3   ax=3
	  ;add al,30h
  	;OUTPUT_2 al
		mov change_a,ax      ;;;保存上一个数  change=3  change=3
		mov z,bp      ;;;保存上一个数的地址  ;;;bx=0 z=0   bx=1 z=1
		
		inc bp     ;;;bp=1  bp=2
		mov bx,bp   ;;;bx=1   bx=2
		mov ax,bx
  	mul q
  	mov bx,ax   ;;;;bx=1*9=9   bx=2*9=18
  	
  	mov change_b,bx      ;;;保存当前数的地址
  	mov ax,change_a     ;;;ax=3     ax=3
  	cmp ax,word ptr score_total[bx+3]       ;;;;;比较第一个数和第二个数   3&6   3&9   
  	
  	jge su3_1          ;;;;;如果大的话跳到su3_1  不交换
  	
  	;;;;;;;;;;;;;;;;;交换;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  	;;;;;;;;;;;;;;;;;姓名;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		mov bx,bp   ;;;bx=1   
		mov ax,bx
  	mul m
  	mov bx,ax   ;;;;bx=1*21=9   
    mov change_b,bx
         
  	mov cx,21
  	lea di,name_1              ;;;hou->1  
  	lea si,name_total[bx]
  	cld
  	rep movsb
  	
  	mov cx,21
  	mov bx,change_b
  	lea di,name_total[bx]              ;;;qian->hou
  	mov bx,z 
  	mov ax,bx
  	mul m
  	mov bx,ax   ;;;;bx=1*21 
  	lea si,name_total[bx]
  	cld
  	rep movsb
  	
  	mov cx,21
  	lea di,name_total[bx]      ;;;1->qian
  	lea si,name_1
  	cld
  	rep movsb 
  	
  	;;;;;;;;;;;;;;;;;;;;;学号;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  	mov bx,bp   ;;;bx=1   
		mov ax,bx
  	mul n
  	mov bx,ax   ;;;;bx=1*21=9   
    mov change_b,bx
         
  	mov cx,10
  	lea di,number_1              ;;;hou->1  
  	lea si,number_total[bx]
  	cld
  	rep movsb
  	
  	mov cx,10
  	mov bx,change_b
  	lea di,number_total[bx]              ;;;qian->hou
  	mov bx,z 
  	mov ax,bx
  	mul n
  	mov bx,ax   ;;;;bx=1*21 
  	lea si,number_total[bx]
  	cld
  	rep movsb
  	
  	mov cx,10
  	lea di,number_total[bx]      ;;;1->qian
  	lea si,number_1
  	cld
  	rep movsb
  	
  	;;;;;;;;;;;;;;;;;;;;成绩;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  	mov bx,bp   ;;;bx=1   
		mov ax,bx
  	mul q
  	mov bx,ax   ;;;;bx=1*21=9   
    mov change_b,bx
         
  	mov cx,8
  	lea di,score_1              ;;;hou->1  
  	lea si,score_total[bx]
  	cld
  	rep movsb
  	
  	mov cx,8
  	mov bx,change_b
  	lea di,score_total[bx]              ;;;qian->hou
  	mov bx,z 
  	mov ax,bx
  	mul q
  	mov bx,ax   ;;;;bx=1*21 
  	lea si,score_total[bx]
  	cld
  	rep movsb
  	
  	mov cx,8
  	lea di,score_total[bx]      ;;;1->qian
  	lea si,score_1
  	cld
  	rep movsb
    	
    	
  	;;;;;;;;;;;;;;;;;;;;;;;余数;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  	mov bx,z       ;;;qian->al
  	mov al,remainder_total[bx]    
		mov ah,remainder_total[bx+1]    ;;;qian->ah            
		mov remainder_total[bx],ah               
		mov remainder_total[bx+1],al
		
		;;;;;;;;;;;;;;;;;;;;;;;空格;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		mov bx,z       ;;;qian->al
    mov al,name_length[bx]    
		mov ah,name_length[bx+1]    ;;;qian->ah            
		mov name_length[bx],ah               
		mov name_length[bx+1],al
		
		mov bx,bp  ;;;bp=1  bp=2
		mov ax,bx
  	mul q
  	mov bx,ax   ;;;;bx=1*9 

su3_1:	
    dec cxl            ;;;cl=1 
		mov cl,cxl         
		cmp cl,0           ;;;;比较内循环是否完成
		jg su3_2 
		
    dec cxh		                    
    mov ch,cxh         ;;;;ch=1
    cmp ch,0           ;;;;;比较外循环是否完成
    jg su3_3
	
su3_exit:
  	call print_panking
    ret
Subroutine3 endp




print_panking proc near        ;;;;;;;;;;;;;;;;;;子程序-输出排名;;;;;;;;;;;;;;;;;;;;;;;;;;;
    STR_TIP pro3
    mov bp,0
    mov bx,bp
  	mov ax,bx           ;;;;ax=0
  	mul q               ;;;;ax*q=0
  	mov bx,ax           ;;;;bx=0
  	
  	mov cl,0
pr_1:	
    inc cl
  	mov score_total[bx+6],cl
  	inc bp
  	mov bx,bp
  	mov ax,bx           ;;;;ax=0
  	mul q               ;;;;ax*q=0
  	mov bx,ax           ;;;;bx=0
  	cmp cl,num
  	jb pr_1
  	
  	mov al,1
  	mov panking,al
  	call print
  	mov al,0
  	mov panking,al
    ret
print_panking endp



statistics2 proc near        ;;;;;;;;;;;;;;表格输出;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    STR_TIP pro17
    STR_TIP pro13
    mov bx,0
    mov bp,bx
st_3:	
  	.if bp==0
  		STR_TIP_N pro14
  	.elseif bp==1
  		STR_TIP_N pro15
  	.elseif bp==2
  		STR_TIP_N pro16
  	.endif	  
  	mov ax,bx
    mul p
    mov bx,ax
    ;mov bp,bx
    mov cx,10
st_2:	
    mov al,Statistics[bx]
    mov dx,0
    mov ah,0
    idiv TEN_1
    push dx
    push ax
    
    pop ax
    cmp ax,0
    je st_1
  	mov ah,2
    add al,30h
    mov dl,al
    int 21h
    
st_1:    
    pop ax
    mov ah,2
    add al,30h
    mov dl,al
    int 21h
    inc bx
    mov si,4         ;;;空格数
st_4:    
    call sprr
    dec si
    cmp si,0
    ja st_4
    loop st_2
    
    inc bp
    mov bx,bp
    OUTPUT_2 "|"
    call spr
    cmp bp,3
    jb st_3
    
    STR_TIP pro19
    
    ret
Statistics2 endp
    
    
;Statistics3 proc near       ;;;;;;;;;;;;;;;;;;子程序-将数据改为五段;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;mov bp,0
    ;statis_2:    mov ax,bp
    ;mul q
    ;mov bx,ax
    ;mov cx,6
    ;mov al,Statistics[bx]
;statis_1:    
    ;inc bx
    ;add al,Statistics[bx]
    ;loop statis_1
    ;mov Statistics_2[0],al
    ;
    ;mov cx,4
    ;add bx,1
    ;lea di,Statistics_2[1]
    ;lea si,Statistics1[bx]
    ;cld
    ;rep movsb
    
    ;inc bp
    ;cmp bp,3
    ;jb statis_2
    ;ret
;Statistics3 endp
    
Statistics4 proc near        
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;子程序-画图;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;call Statistics3
    MOV AH,0
  	MOV AL,12H  ;640*480*16
  	INT 10H
  
  	LINE 10,400,600,400,1      ;;;坐标线
  	LINE 10,400,11,100,1
  	
  	call print_ln1             ;;;标点
  	
  	mov bx,0
    mov bp,bx  ;;bp=0
statis4_1:	 
  	mov ax,bx  ;;ax=0
    mul p  ;;ax=0
    mov bx,ax   ;;ax=0
    mov cx,10   ;;cx=10
statis4_2:	
    mov al,Statistics[bx]
    .if bp==0
    	;;;;;;	一科成绩
    	Histogram_hong_1
    .elseif bp==1
    	;Histogram_hong_2
    .elseif bp==2
    	;Histogram_hong_3
    .endif
  	dec cx
  	inc bx
  	cmp cx,0
  	jne statis4_2	
    inc bp
    mov bx,bp
    cmp bp,3
    jb statis4_1
	
    ret
Statistics4 endp



print_ln1 proc near 
    ;;;;;;;;;;;;;;;;;;;;;;;子程序-画标点;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    DRAWLINE1 10,100,5,1
  	DRAWLINE1 10,130,5,1
  	DRAWLINE1 10,160,5,1
  	DRAWLINE1 10,190,5,1
  	DRAWLINE1 10,220,5,1
  	DRAWLINE1 10,250,5,1
  	DRAWLINE1 10,280,5,1
  	DRAWLINE1 10,310,5,1
  	DRAWLINE1 10,340,5,1
  	DRAWLINE1 10,370,5,1
  	DRAWLINE1 10,400,5,1
  	;
  	;LINE 30,400,31,395,1          ;;;0-10
  	;LINE 40,400,41,395,1
  	;LINE 50,400,51,395,1
  	;LINE 60,400,61,395,1
  	;
  	;LINE 80,400,81,395,1          ;;;10-20
  	;LINE 90,400,91,395,1
  	;LINE 100,400,101,395,1
  	;LINE 110,400,111,395,1
  	;;
  	;LINE 130,400,131,395,1        ;;;20-30
  	;LINE 140,400,141,395,1
  	;LINE 150,400,151,395,1
  	;LINE 160,400,161,395,1
  	;
  	;LINE 180,400,181,395,1        ;;;30-40
  	;LINE 190,400,191,395,1
  	;LINE 200,400,201,395,1
  	;LINE 210,400,211,395,1
  	;
  	;LINE 230,400,231,395,1        ;;;40-50
  	;LINE 240,400,241,395,1
  	;LINE 250,400,251,395,1
  	;LINE 260,400,261,395,1
  	;
  	;LINE 280,400,281,395,1        ;;;50-60
  	;LINE 290,400,291,395,1
  	;LINE 300,400,301,395,1
  	;LINE 310,400,311,395,1
  	;
  	;LINE 330,400,331,395,1        ;;;60-70
  	;LINE 340,400,341,395,1
  	;LINE 350,400,351,395,1
  	;LINE 360,400,361,395,1
  	;
  	;LINE 380,400,381,395,1        ;;;70-80
  	;LINE 390,400,391,395,1
  	;LINE 400,400,401,395,1
  	;LINE 410,400,411,395,1
  	;
  	;LINE 430,400,431,395,1        ;;;80-90
  	;LINE 440,400,441,395,1
  	;LINE 450,400,451,395,1
  	;LINE 460,400,461,395,1
  	;
  	;LINE 480,400,481,395,1        ;;;90-100
  	;LINE 490,400,491,395,1
  	;LINE 500,400,501,395,1
  	;LINE 510,400,511,395,1
    ret
print_ln1 endp
    
CODES ENDS
    END START
