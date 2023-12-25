;用notepad++查看此文档比较好~~
.model small				;small，程序只能有一个代码段和一个数据段
.stack 200h					;堆栈段名 stack，默认大小 1024 字节，这里是 200h 字节
.data						;数据段名_data

student struc			;学生的数据结构,32 字节，2^5，便于计算地址
    xname db 14 dup('$')
    class db 14 dup('$')
    num   dw 0
    score dw 0			;为了保存1位小数，以10倍值保存
student ends
	
    stu_size equ 32			;32=2^5
   
  	stu_db student 100 dup(<'x','y',6,500>)		;声明100 名学生的空间的结构体stu_db
  	stu_num db 0								;已保存的学生人数
  	stu_seq db 100 dup('$')						;排序信息，排序操作在序列中进行，排序结果体现在序列中

    welcome db '-----Student Information Mannagement System-----',0dh,0ah ;打印菜单
        		db '------------------------------------------------',0dh,0ah;
        		db '0. Add Information.',0dh,0ah				;0. 录入学生成绩（十进制形式)
        		db '------------------------------------------------',0dh,0ah;
        		db '1. Sort by the numbers of students.',0dh,0ah;1.按学号排序显示
        		db '------------------------------------------------',0dh,0ah;
        		db '2. Sort by the scores of students.',0dh,0ah	;2.按成绩排序显示
        		db '------------------------------------------------',0dh,0ah;
        		db '3. Statistic the Average score',0dh,0ah		;3.统计平均成绩
        		db '------------------------------------------------',0dh,0ah;
        		db '4. Show Statistics of each kind.',0dh,0ah	;4.统计各分数段人数
        		db '------------------------------------------------',0dh,0ah;
        		db '5. Exit.',0dh,0ah							;5.退出
        		db '------------------------------------------------',0dh,0ah;
        	 	db 'please select one'
        	 	db '$'	 	
       msg1 db 'name:','$'
       msg2 db 'class:','$'
       msg3 db 'number:','$'
       msg4 db 'score:','$'
    m_str_l db 0dh,0ah,'please input your ','$'
    m_num_l db 0dh,0ah,'please input your ','$'
    
    
    table		dw CASE0,CASE1,CASE2,CASE3,CASE4,CASE5
    buflen 	db 	100									;输入缓冲区大小 100
    aclen		db 	? 									;实际输入长度
    buf    	db	100 dup(0),'$'						;实际缓冲区
    bufrear	equ offset buf+100						;缓冲区尾
    
        ns6 db 0				;统计各分数段人数
        n67 db 0
        n78 db 0
        n89 db 0
        n91 db 0
        
        ms6 db '(Not Pass)0 ~ 60:','$'	;显示各分数段人数
        m67 db '(Pass)   60 ~ 70:','$'
        m78 db '(Normal) 70 ~ 80:','$'
        m89 db '(Good)   80 ~ 90:','$'
        m91 db '(Great) 90 ~ 100:','$'

    .CODE					;代码段名_text
START:

ps macro str 			;打印字符串，要求以'$'结尾
    push ax
    push dx
  	lea dx,str
  	mov ah,9
  	int 21h
  	
  	pop dx	
  	pop ax
endm

pc macro ch				;打印字符
    push ax
    push dx
  	mov dl,ch
  	mov ah,2
  	int 21h
  	pop dx
  	pop ax
endm

endl macro 				;打印'\n'
  	pc 0dh
  	pc 0ah
endm

scs macro 				    ;从键盘输入字符串，保存在buf中，串长aclen
  	lea dx,buflen
  	mov ah,10
  	int 21h
endm

scc macro 				    ;从键盘输入字符，保存在al
  	mov ah,1
  	int 21h
endm

memcpy macro dest,src,len   ;经典的内存拷贝
	push ax
  	push cx
  	push si
  	push di
  	mov ax,ds
  	mov es,ax 				;串操作di要用到附加段
  	mov cl,len
  	mov ch,0
  	lea si,src
  	lea di,dest
  	cld
  	rep movsb
  	;mov [di],'
  	pop di
  	pop si
  	pop cx
  	pop ax
endm

;使bx指向编号为ax的学生单元
;寄存器：ax,bx,cx
GET_STU macro
	push ax
	push cx
	lea bx,stu_db
	mov cl,5			
	shl ax,cl			;?????????
	add bx,ax 			;bx指向这个学生的存储单元
	pop cx
	pop ax
endm
	
	mov ax,@data
	mov ds,ax
WELC:					;调用ps函数打印welcome数据段
	endl
	ps welcome
	pc ':'
	
	;输入选项
	scc 				;ascii码保存在al
	endl
	endl
	mov ah,0
	mov bx,ax
	sub bx,'0'			;?????????
	cmp bx,5
	jbe CASE0TO5		;bx寄存器不高于5则转移到CASE0T05
	jmp WELC
CASE0TO5:
	shl bx,1			;?????????
	jmp table[bx] 		;基址寻址
CASE0: 					;录入学生成绩（十进制形式）
	call  ins_stu
	jmp WELC
CASE1: 					;按学号排序显示
	call num_sort
	call print_seq
	jmp WELC
CASE2: 					;按成绩排序显示
	call score_sort
	call print_seq
	jmp WELC
CASE3: 					;统计平均成绩
	call get_average
	jmp WELC
CASE4: 					;统计各分数段人数
	call get_sat
	jmp WELC
CASE5:
	mov ah,4ch      	;结束
	int 21h
	
	

;ins_stu:输入学生信息
;入口：stu_num已有学生人数，即最新空白编号
;出口：stu_db
;存储单元：stu_db,stu_num
ins_stu proc near
  	push ax
  	push bx
  	push cx
  	push dx
  	
  	mov al,stu_num
  	mov ah,0
  	;确定存放在第几个位置
  	lea bx,stu_db
  	mov cl,5
  	shl ax,cl
  	add bx,ax 			;bx指向空白单元
input_name:
  	ps  m_str_l			;m_str_l db 0dh,0ah,'(Length < 14 bytes) ','$'
  	ps  msg1			;msg1 db 'name:','$'
  	scs
  	cmp aclen,14
  	jae input_name		;大于等于跳转至重新输入name
  	memcpy [bx].xname,buf,aclen;否则拷贝buf长度为aclen的字符串到stu_db结构体下的xname
  	endl
input_class:
  	ps  m_str_l
  	ps  msg2
  	scs
  	cmp aclen,14
  	jae input_class
  	memcpy [bx].class,buf,aclen
  	endl
  
  	ps m_num_l
  	ps msg3
  	scs
  	call str2num		;调用str2num:将数字由字符串转成数值
  	mov [bx].num,ax
  	endl
  
  	ps m_num_l
  	ps msg4
  	scs
  	call score_fmt		;调用score_fmt：将分数格式存储
  	mov [bx].score,ax
  	endl
	
	  inc stu_num 		;增加学生记录
  	pop dx
  	pop cx
  	pop bx
  	pop ax
	  ret
ins_stu endp


;pnum:以十进制形式输出一个无符号数
;入口：ax需要输出的正数
;出口：
;存储单元：
pnum proc near
	push ax
	push bx
	push cx
	push dx
	
	mov bx,bufrear
	dec bx	
	mov [bx],'$'
	
OUTLOOP:
	or ax,ax
	jz OUTLOOPFIN ;ax为零
	mov dx,0
	mov cx,10
	div cx
	add dl,'0'
	dec bx
	mov byte ptr [bx],dl
	jmp OUTLOOP
OUTLOOPFIN:
	cmp bx,offset bufrear-1 ;输出0
	jne PRINT_NUM
	dec bx
	mov BYTE ptr [bx],'0'
PRINT_NUM:
	mov dx,bx
	mov ah,9
	int 21h
	pop dx
	pop cx
	pop bx
	pop ax
	ret
pnum endp




;pscore:以十进制形式输出带一位小数的分数
;入口：ax需要输出的正数
;出口：
;存储单元：
pscore proc near
	push ax
	push bx
	push cx
	push dx
	
	mov bx,bufrear
OUTLOOP2:
	or ax,ax
	jz OUTLOOPFIN2
	mov dx,0
	mov cx,10
	div cx
	add dl,'0'
	dec bx
	mov byte ptr [bx],dl
	jmp OUTLOOP2
OUTLOOPFIN2:
	cmp bx,offset bufrear-1 ;x要改成0x，以便小数格式输出
	je S0X
	cmp bx,offset bufrear ;空要改成00，以便小数格式输出
	jne PRINT_SCORE
S00:
	;==，为空
	dec bx
	mov BYTE ptr [bx],'0'
S0X:
	dec bx
	mov BYTE ptr [bx],'0'
PRINT_SCORE:
  	mov dx,bx
  	mov bx,bufrear
  	dec bx
  	mov cl,[bx] ;暂存小数
  	mov [bx],'$'
  	;mov dx,bx
  	mov ah,9
  	int 21h
  	
  	pc '.'
  	pc cl
  	
  	pop dx
  	pop cx
  	pop bx
  	pop ax
  	ret
pscore endp



;pstu:输出学生信息
;入口：ax存储编号
;出口：
;存储单元：
pstu proc near
	push  ax
	push bx
	push cx
	GET_STU
	ps msg1
	ps [bx].xname;
	pc ' '
	ps msg2
	ps [bx].class
	pc ' '
	ps msg3
	mov ax,[bx].num
	call pnum 
	pc ' '
	ps msg4
	mov ax,[bx].score
	call pscore
	endl
	pop cx
	pop bx
	pop  ax
	ret
pstu endp



;str2num：将数字由字符串转成数值
;入口：buf
;出口：ax
;存储单元：buf缓冲区，aclen缓冲区内容长度
str2num proc
	push bx
	push cx
	push si
	mov  ax,0
	mov  cl,aclen
	mov  ch,0
	lea  si,buf
GET_NUM:
	;mov ax,dest ;add dest,dest*10 + [si]-'0'
	mov bl,10
	mul  bl ;以前的数*10，乘法指令必须用ax
	mov  bl,[si]
	mov  bh,0
	add  ax,bx
	sub  ax,'0'
	inc  si
	loop  GET_NUM
	
	pop si
	pop cx
	pop bx
	ret
str2num endp



;score_fmt：将分数格式存储
;入口：buf
;出口：ax
;存储单元：buf缓冲区，aclen缓冲区内容长度
score_fmt proc
	push bx
	push cx
	push dx
	push si
	
	mov ax,0
	mov cl,aclen
	mov ch,0
	mov dx,0
	lea si,buf
GET_SCORE:
	cmp BYTE ptr [si],'.' ;这个类型很重要
	jnz MUL_DEX ;不是小数点
	mov dx,1 ;发现小数点
	inc si
	loop GET_SCORE
	
MUL_DEX:
	mov bl,10
	mul bl
	mov bl,[si]
	mov bh,0
	add ax,bx
	sub ax,'0'
	
	inc si
	loop GET_SCORE
	
	cmp dx,0
	jnz END_SCORE
	mov bl,10
	mul bl
END_SCORE:
	pop si
	pop dx
	pop cx9
 
	pop bx
	ret
score_fmt endp

	;get_average：算平均分并输出
	;入口：stu_db
	;出口
	;存储单元：stu_db,stu_num
get_average proc near
	push ax
	push bx
	push cx
	push dx
	
	mov cx,0 ;学生编号
	mov ax,0 ;暂存平均成绩低8位
	mov dx,0 ;暂存平均成绩高8位
REPERT:
	cmp cl,stu_num
	jae OUT_PUT ;总分已经加完了
	;找到编号为cx的学生
	push ax
	push cx
	mov ax,cx
	GET_STU
	pop cx
	pop ax
	
	add ax,[bx].score ;32位加法
	adc dx,0
	inc cl
	jmp REPERT
OUT_PUT:
	mov cl,stu_num
	mov ch,0
	or cl,0 ;假设学生人数不多于255人
	jnz END_AVE ;没有学生，不能除0
	inc cx
END_AVE:
	div cx ;扩展为16位除法，商保存在ax中
	endl
	call pscore
	endl
	
	pop dx
	pop cx
	pop bx
	pop ax
	ret
get_average endp

	;get_sat:统计各分数段人数并输出
	;入口：stu_db
	;出口
	;存储单元：ns6,n67,n78,n89,n91,stu_db,stu_num
get_sat proc near
	push ax
	push bx
	push cx
	
	mov ns6,0
	mov n67,0
	mov n78,0
	mov n89,0
	mov n91,0
	mov cx,0 ;学生编号(人数-1)
	
SAT_IN:
	cmp cl,stu_num
	jae SAT_OUT ;已经完了
	
	;找到编号为cx的学生
	push ax
	push cx
	mov ax,cx
	GET_STU
	pop cx
	pop ax
	
	inc cl
	
	mov ax,[bx].score
	cmp ax,600			;由于是以10倍值进行存储的所以是与600比较
	jb IS6				;小于跳转
	cmp ax,700
	jb I67
	cmp ax,800
	jb I78
	cmp ax,900
	jb I89
	;>=90
	inc n91
	jmp SAT_IN
IS6:
	inc ns6
	jmp SAT_IN
I67:
	inc n67
	jmp SAT_IN
I78:
	inc n78
	jmp SAT_IN
I89:
	inc n89
	jmp SAT_IN

SAT_OUT:
	mov ah,0
	
	ps ms6
	mov al,ns6
	call pnum
	endl
	
	ps m67
	mov al,n67
	call pnum
	endl

	ps m78
	mov al,n78
	call pnum
	endl

	ps m89
	mov al,n89
	call pnum
	endl

	ps m91
	mov al,n91
	call pnum
	endl

	pop cx
	pop bx
	pop ax
	ret
get_sat endp
	
	;print_seq:根据序列stu_seq输出列表
	;输入：stu_seq
	;输出：
	;存储单元：stu_seq
print_seq proc near
	push ax
	push bx
	;stu_seq保存了编号序列，以'$'结束
	lea bx,stu_seq
PRINT_SEQ_BEGIN:
	mov al,[bx]
	cmp al,'$'
	jz PRINT_SEQ_END
	mov ah,0
	call pstu
	inc bx
	jmp PRINT_SEQ_BEGIN
PRINT_SEQ_END:
	pop bx
	pop ax
	ret
print_seq endp

	;num_sort:按学号排序
	;输入：stu_seq
	;输出：stu_seq
	;存储单元：
num_sort proc near
	push bx
	push dx

	mov dl,0
	lea bx,stu_seq
SORT_BEGIN:
	cmp dl,stu_num
	jae SORT_END
	mov BYTE ptr [bx],dl
	inc bx
	inc dl
	jmp SORT_BEGIN
SORT_END:
	mov BYTE ptr [bx],'$'
	;stu_seq保存了按输入顺序的序列，以'$'结束

	cmp stu_num,1 ;学生数小于等于1，没必要排序
	jle NON_NUM

	mov cl,stu_num ;循环次数，内存量不能直接减
	dec cl
	mov ch,0
LOOP1:
	mov di,cx ;暂存外循环cx
	lea bx,stu_seq ;指向第一个序号
LOOP2:
	mov al,BYTE ptr [bx]
	mov ah,0
	
	push bx
GET_STU
	mov dx,[bx].num ;dx前一个序列号对应的学号
	pop bx

	mov al,BYTE ptr [bx+1]   
	push bx
	GET_STU
	cmp dx,[bx].num ;[bx].num后一个序列号对应的学号
	pop bx
jae CONTI
	mov al,BYTE ptr [bx] ;小于则交换两个序列号
	;call pnum
	;endl
	xchg al,BYTE ptr [bx+1]
	;call pnum
	;endl
	mov BYTE ptr [bx],al
CONTI:
	inc bx ;下一个序列号
	loop LOOP2
	mov cx,di ;恢复外循环
	loop LOOP1
	
NON_NUM:
	pop dx
	pop bx
	ret
num_sort endp

	;score_sort:按成绩排序
	;输入：stu_seq
	;输出：stu_seq
	;存储单元：
score_sort proc near
	push bx
	push dx
	
	mov dl,0
	lea bx,stu_seq
SCORE_BEGIN:		
	cmp dl,stu_num
	jae SCORE_END
	mov BYTE ptr [bx],dl
	inc bx
	inc dl
	jmp SCORE_BEGIN
SCORE_END:
	mov BYTE ptr [bx],'$'
	;stu_seq保存了按输入顺序的序列，以'$'结束
	
	cmp stu_num,1 ;学生数小于等于1，没必要排序
	jle NON_SCORE
	mov cl,stu_num ;循环次数，内存量不能直接减
	dec cl
	mov ch,0
SLOOP1:
	mov di,cx ;暂存外循环cx
	lea bx,stu_seq ;指向第一个序号
SLOOP2:
	mov al,BYTE ptr [bx]
	mov ah,0
	
	push bx
	GET_STU
	mov dx,[bx].score ;dx前一个序列号对应的学号
	pop bx
	
	mov al,BYTE ptr [bx+1]
	push bx
	GET_STU
	cmp dx,[bx].score ;[bx].num后一个序列号对应的学号
	pop bx
	
	jae SCONTI
	mov al,BYTE ptr [bx] ;小于则交换两个序列号
	;call pnum
	;endl
	xchg al,BYTE ptr [bx+1]
	;call pnum
	;endl
	mov BYTE ptr [bx],al
SCONTI:
	inc bx ;下一个序列号
	loop SLOOP2
	mov cx,di ;恢复外循环
	loop SLOOP1
NON_SCORE:
	pop dx
	pop bx
	ret
	score_sort endp
END START