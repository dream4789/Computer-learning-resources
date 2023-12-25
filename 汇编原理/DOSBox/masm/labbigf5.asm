;------------------------------------------------------------------------------
; 常用的常量定义.
;------------------------------------------------------------------------------
INSERT_STUD			equ	'i'			; 插入学生信息.
DELETE_STUD			equ	'd'			; 删除学生.
MODIFY_STUD			equ	'm'			; 修改学生信息.
QUERY_STUD			equ	'q'			; 查找学生.
COUNT_STUD			equ	'c'			; 计算学生数量.
PRINT_STUD			equ	'p'			; 打印输出学生信息.
LIST_STUD			  equ 'l'			; 列出所有学生.
EXIT_SYSTEM			equ	'e'			; 退出管理系统.

NAME_MAXLEN			equ	20			; 学生姓名的最大长度.
INT_DATA_LEN		equ	3			  ; 一项整数的长度.
STUD_STRUCT_LEN	equ	NAME_MAXLEN + 3 * INT_DATA_LEN + 6				; 一个学生占的内存长度.

CREATE_OPEN_FILE	equ	716ch		; 打开或创建文件.
CLOSE_FILE_HANDLE	equ	3eh			; 关闭文件句柄.
READ_ONLY		   	  equ 0			  ; 只读文件.
WRITE_ONLY			  equ	1			  ; 只写文件.
READ_AND_WRITE		equ	2			  ; 读写文件.
MOVE_FILE_POINTER	equ	42h			; 移动文件指针.

TRUE				equ	1			; 真值.
FALSE				equ	0			; 假值.


;------------------------------------------------------------------------------
; 键盘缓冲区结构.
;------------------------------------------------------------------------------
KeyboardInfo struc
  	m_iMaxInput		db		NAME_MAXLEN				  	; 最大输入的字符数.
  	m_iInputCnt		db		0							        ; 实际输入的字符数.
  	m_szBuffer		db		NAME_MAXLEN dup('$')  ; 最终输入的缓冲.
KeyboardInfo ends


;------------------------------------------------------------------------------
; 学生结构.
;------------------------------------------------------------------------------
Student struc
  	m_szName		db		NAME_MAXLEN  dup ('$'), '$'		; 学生姓名.
  	m_iAge			db		INT_DATA_LEN dup ('$'), '$'		; 学生年龄.
  	m_iMath			db		INT_DATA_LEN dup ('$'), '$'		; 数学成绩.
  	m_iEnglish	db		INT_DATA_LEN dup ('$'), '$'		; 英语成绩.
  	__ENDL_CH		db		0dh, 0ah						; 换行占位符.
Student ends


;------------------------------------------------------------------------------
; 数据段.
;------------------------------------------------------------------------------
__Data segment
  	szInputInfo		db	0dh, 0ah
      						db '========================================', 0dh, 0ah
      						db '        Student Management System       ', 0dh, 0ah
      						db '        Software 0801 ZhangYaFeng       ', 0dh, 0ah
      						db '----------------------------------------', 0dh, 0ah
      						db '        1. Insert Student.    [I]       ', 0dh, 0ah
      						db '        2. Delete Student.    [D]       ', 0dh, 0ah
      						db '        3. Modify Student.    [M]       ', 0dh, 0ah
      						db '        4. Query Information. [Q]       ', 0dh, 0ah
      						db '        5. Count Students.    [C]       ', 0dh, 0ah
      						db '        6. Print Students.    [P]       ', 0dh, 0ah
      						db '        7. List Students.     [L]       ', 0dh, 0ah
      						db '        8. Exit System.       [E]       ', 0dh, 0ah
      						db '========================================', 0dh, 0ah
      						db 'Please enter your choice:', '$'
  	szInputStud		db 0dh, 0ah, 'Please enter student information:[name age math english]', 0dh, 0ah, '$'
  	szInputName		db 0dh, 0ah, '[Name]   : ', '$'
  	szInputAge		db 0dh, 0ah, '[Age]    : ', '$'
  	szInputMath		db 0dh, 0ah, '[Math]   : ', '$'
   szInputEnglish db 0dh, 0ah, '[English]: ', '$'
  	szEndl			  db 0dh, 0ah, '$'
  	szStudInfo		db 0dh, 0ah, 'Information of Student as follows:', 0dh, 0ah, '$'
  	szCountInfo		db 0dh, 0ah, 'Student count is: ', '$'
  	szQueryInfo		db 0dh, 0ah, 'Please enter the name of Student for query:', '$'
  	szNotFound		db 0dh, 0ah, 'Student not found!', '$'
  	szFileName		db 'StudInfo.txt', 0				; 文件名.
  	szTempFile		db 'StudTemp.txt', 0				; 临时文件名.
  	hFileHandle		dw	0								        ; 文件句柄.
  	
  	szQueryName		db NAME_MAXLEN dup('$'), '$'	; 查找学生的姓名存放区.
  	g_Keyboard		KeyboardInfo <>					; 全局的键盘缓冲结构.
  	g_Student		  Student	<>						  ; 全局的学生结构.
__Data ends



;------------------------------------------------------------------------------
; 堆栈段.
;------------------------------------------------------------------------------
__Stack segment stack
	  stack_elements dd 1024 dup(0)
__Stack ends



;------------------------------------------------------------------------------
; 代码段.
;------------------------------------------------------------------------------
__Code segment
	  assume CS:__Code, DS:__Data, SS:__Stack


; 界面及输入.返回后ah存放用户的输入.
PrintInteface proc
  	push	dx
  	push	cx
  	
  	lea	dx,	szInputInfo
  	mov	ah,	9h
  	int	21h
  	
  	mov	ah,	1
  	int	21h
  	mov	ah,	al
  	
  	pop	cx
  	pop	dx
  	ret
PrintInteface endp


; 输出换行符.
PrintEndl proc
  	push	ax
  	push	dx
  	
  	lea	dx,	szEndl
  	mov	ah,	9h
  	int	21h
  	
  	pop	dx
  	pop	ax
  	ret
PrintEndl endp



; 输出一个字符串.字符串地址在DS:DX中.
PrintStr proc
  	push	ax
  	
  	mov	ah,	9h
  	int	21h
  	
  	pop	ax
  	ret
PrintStr endp


; 输入一个学生信息.
InputStud proc
  	push	ax
  	push	bx
  	push	cx
  	push	dx
  	push	si
  	push	di
  	
  	; 显示输入提示信息.
  	lea	dx,	szInputStud
  	mov	ah,	9h
  	int	21h
  	
  	mov	ax,	__Data
  	mov	es,	ax
  	
  	; 输入姓名.
  	lea	dx,	szInputName
  	mov	ah,	9h
  	int	21h
  	
  	mov	ah,	0ah
  	lea	dx,	g_Keyboard
  	int	21h
  	
  	; 拷贝姓名.
  	mov	cl,	g_Keyboard.m_iInputCnt
  	mov	ch,	0
  	mov	bx,	cx
  	lea	si,	g_Keyboard.m_szBuffer
  	lea	di,	g_Student.m_szName
  	cld
  	rep	movsb
  	
  	; 保证字符串最后位置正常截断.
  	mov	g_Student.m_szName[bx], '$'
  	
  	; 输入年龄.
  	lea	dx,	szInputAge
  	mov	ah,	9h
  	int	21h
  	
  	mov	ah,	0ah
  	lea	dx,	g_Keyboard
  	int	21h
  	
  	; 拷贝年龄.
  	mov	cl,	g_Keyboard.m_iInputCnt
  	mov	ch,	0
  	mov	bx,	cx
  	lea	si,	g_Keyboard.m_szBuffer
  	lea	di,	g_Student.m_iAge
  	cld
  	rep	movsb
  	
  	mov	g_Student.m_iAge[bx], '$'
  	
  	; 输入数学成绩.
  	lea	dx,	szInputMath
  	mov	ah,	9h
  	int	21h
  	
  	mov	ah,	0ah
  	lea	dx,	g_Keyboard
  	int	21h
  	
  	mov	cl,	g_Keyboard.m_iInputCnt
  	mov	ch,	0
  	mov	bx,	cx
  	lea	si,	g_Keyboard.m_szBuffer
  	lea	di,	g_Student.m_iMath
  	cld
  	rep	movsb
  	
  	mov	g_Student.m_iMath[bx], '$'
  	
  	; 输入英语成绩.
  	lea	dx,	szInputEnglish
  	mov	ah,	9h
  	int	21h
  	
  	mov	ah,	0ah
  	lea	dx,	g_Keyboard
  	int	21h
  	
  	mov	cl,	g_Keyboard.m_iInputCnt
  	mov	ch,	0
  	mov	bx,	cx
  	lea	si,	g_Keyboard.m_szBuffer
  	lea	di,	g_Student.m_iEnglish
  	cld
  	rep	movsb
  	
  	mov	g_Student.m_iEnglish[bx], '$'
  	
  	pop	di
  	pop	si
  	pop	dx
  	pop	cx
  	pop	bx
  	pop	ax
  	ret
InputStud endp


; 插入一个学生信息.
InsertStud proc
  	; 输入学生信息.
  	call	InputStud
  	; 学生信息写入文件.
  	call	WriteStud
  	ret
InsertStud endp



; 读取一个学生信息.
; [in]  ax表示要读取的学生在文件中的索引.
; [out] ax为TRUE表示读取成功,为FALSE表示到文件尾或读取失败.
ReadStud proc
	push	bx
	push	cx
	push	dx
	push	si
	push	di
	
	; 打开并移动文件指针. ax存放偏移量.
	call	SeekFile
	
	; 读取文件.
	mov	ah,	3fh
	mov	bx,	hFileHandle
	mov	cx,	STUD_STRUCT_LEN
	lea	dx,	g_Student
	int	21h
	jc		__FailedRet
	
	; 保存读取的字节数.
	mov	di,	ax
	
	; 关闭文件.
	mov	ah,	CLOSE_FILE_HANDLE
	mov	bx,	hFileHandle
	int	21h
	jc		__FailedRet
	
	; 看是否到达文件尾.
	cmp	di,	STUD_STRUCT_LEN
	jne	__FailedRet
	
	mov	ax,	TRUE
	jmp	__SuccessRet

	__FailedRet:
		mov	ax,	FALSE
		
	__SuccessRet:
		pop	di
		pop	si
		pop	dx
		pop	cx
		pop	bx
		ret
ReadStud endp


; 移动文件指针.ax存放偏移.
; 先打开文件,hFileHandle 存放打开的文件指针.
; 结束后并不关闭文件.ax中返回代码.
SeekFile proc
	push	bx
	push	cx
	push	dx
	push	si
	push	di
	
	mov	di,	ax
	
	; 打开文件.
	mov	ax,	CREATE_OPEN_FILE
	mov	bx,	READ_AND_WRITE
	mov	cx,	0
	mov	dx, 	1
	lea	si,	szFileName
	int	21h
	jc		__FailedSeek
	
	; 取得文件句柄.
	mov	hFileHandle,	ax
	
	; 取得偏移量. DX:AX
	mov	ax,	di
	mov	dx,	STUD_STRUCT_LEN
	mul	dx
	
	; 移动到文件偏移位置. CX:DX
	mov	cx,	dx
	mov	dx,	ax
	mov	ah,	MOVE_FILE_POINTER
	mov	al,	0
	mov	bx,	hFileHandle
	int	21h
	jc		__FailedSeek
	
	mov	ax,	TRUE
	jmp	__SuccessSeek

	__FailedSeek:
		mov	ax,	FALSE
		
	__SuccessSeek:
		pop	di
		pop	si
		pop	dx
		pop	cx
		pop	bx
		ret
SeekFile endp


; 将学生信息写入文件.
; [in] g_Student
WriteStud proc
	push	ax
	push	bx
	push	cx
	push	dx
	push	si
	
	; 打开文件.
	mov	ax,	CREATE_OPEN_FILE
	mov	bx,	WRITE_ONLY
	mov	cx,	0
	mov	dx,	1
	lea	si,	szFileName
	int	21h
	jc		__Failed
	mov	hFileHandle,	ax
	
	; 移动到文件尾.
	mov	ah,	MOVE_FILE_POINTER
	mov	al,	2
	mov	bx,	hFileHandle
	mov	dx,	0
	mov	cx,	0
	int	21h
	
	; 写入文件.
	mov	ah,	40h
	mov	bx,	hFileHandle
	mov	cx,	STUD_STRUCT_LEN
	lea	dx,	g_Student
	int	21h
	jc		__Failed
	
	; 关闭文件.
	mov	ah,	CLOSE_FILE_HANDLE
	mov	bx,	hFileHandle
	int	21h
	
	__Failed:
		pop	si
		pop	dx
		pop	cx
		pop	bx
		pop	ax
		ret
WriteStud endp


; 删除一个学生信息.
; 建立一个临时文件(szTempFile),将不删除的学生信息写入.
; 最终删除原来的文件(szFileName),将临时文件重命名为原来的文件即可.
DeleteStud proc
  	push	ax
  	push	bx
  	push	cx
  	push	dx
  	push	si
  	push	di
  	
  	; 先查找要删除的学生是存在.
  	call	QueryStud
  	cmp	ax,	-1
  	je		__DeleteFailed
  	
  	; 保存查找到的学生索引.
  	; inc si 是必要的！见下面[1]
  	mov	si,	ax
  	inc	si
  	
  	; 创建一个临时文件.
  	mov	ah,	3ch
  	mov	cx,	0
  	lea	dx,	szTempFile
  	int	21h
  	
  	; 保存文件句柄.
  	mov	di,	ax
  	
  	mov	cx,	0
__ReadStud:
		mov	ax,	cx
		call	ReadStud
		cmp	ax,	FALSE
		je		__DeleteComplete
		
		; 如果索引相同则不必写入,直接读取下一个.
		; [1] inc cx 必须在 cmp命令之前,否则会影响je的跳转.
		inc	cx
		cmp	cx,	si
		je		__ReadStud
		
		push	cx
		; 将信息写入临时文件.
		mov	ah,	40h
		mov	bx,	di
		mov	cx,	STUD_STRUCT_LEN
		lea	dx,	g_Student
		int	21h
		pop	cx
		
		jmp	__ReadStud
	
__DeleteComplete:
		; 关闭临时文件.
		mov	ah,	CLOSE_FILE_HANDLE
		mov	bx,	di
		int	21h
		
		; 删除原来的文件.
		lea	dx,	szFileName
		mov	ah,	41h
		int	21h
		
		; 重命名临时文件为原来的文件.
		lea	dx,	szTempFile
		mov	ax,	__Data
		mov	es,	ax
		lea	di,	szFileName
		mov	ah,	56h
		int	21h
	
__DeleteFailed:
		pop	di
		pop	si
		pop	dx
		pop	cx
		pop	bx
		pop	ax
		ret
DeleteStud endp



; 查找一个学生.如果查找到,则ax中存放在文件中的索引.
; 否则ax中存放-1.
QueryStud proc
  	push	bx
  	push	cx
  	push	dx
  	push	si
  	push	di
  	
  	; 输入查询姓名.
  	lea	dx,	szQueryInfo
  	mov	ah,	9h
  	int	21h
  	
  	mov	ah,	0ah
  	lea	dx,	g_Keyboard
  	int	21h
  	
  	; 拷贝查询姓名.
  	mov	ax,	__Data
  	mov	es,	ax
  	
  	mov	cl,	g_Keyboard.m_iInputCnt
  	mov	ch,	0
  	mov	bx,	cx
  	lea	si,	g_Keyboard.m_szBuffer
  	lea	di,	szQueryName
  	cld
  	rep	movsb
  	
  	mov	szQueryName[bx],	'$'
  	
  	; cx存放字符串的比较长度.
  	; dx存放已经查找的人数计数.
  	mov	bx,	0

__Query_loop:
		mov	ax,	bx
		call	ReadStud
		cmp	ax,	FALSE
		je		__QueryFailed
		inc	bx
		
		mov	cl,	g_Keyboard.m_iInputCnt
		mov	ch,	0
		
		; 如果查找到的名字后不为结束符'$',则还是没有找到.
		mov	si,	cx
		mov	ah,	g_Student.m_szName[si]
		cmp	ah,	'$'
		jne	__Query_loop
		
		; 正式比较姓名是否一致.
		lea	si,	g_Student.m_szName
		lea	di,	szQueryName
		repe	cmpsb
		jne	__Query_loop
		
		
  	; 如果执行到这儿,说明找到了学生.则将他的信息显示出来.
  	; 将索引保存到ax中.
  	mov	ax,	bx
  	dec	ax
  	call	PrintStud
  	jmp	__Ret

__QueryFailed:
		lea	dx,	szNotFound
		call	PrintStr
		mov	ax,	-1
	
__Ret:
		pop	di
		pop	si
		pop	dx
		pop	cx
		pop	bx
		ret
QueryStud endp



; 修改学生信息.
ModifyStud proc
  	push	ax
  	push	bx
  	push	cx
  	
  	call	QueryStud
  	cmp	ax,	-1
  	je		__ModifyFailed
  	
  	push	ax
  	; 重新输入学生信息.
  	call	InputStud
  	pop	ax
  	
  	; 移动文件指针.
  	call	SeekFile
  	
  	; 将信息写入文件.
  	mov	ah,	40h
  	mov	bx,	hFileHandle
  	mov	cx,	STUD_STRUCT_LEN
  	lea	dx,	g_Student
  	int	21h
  	jc		__ModifyFailed
  	
  	; 关闭文件.
  	mov	ah,	CLOSE_FILE_HANDLE
  	mov	bx,	hFileHandle
  	int	21h
  	
__ModifyFailed:
		pop	cx
		pop	bx
		pop	ax
		ret
ModifyStud endp



; 计算学生人数.
CountStud proc
  	push	cx
  	push	ax
  	push	dx
  	
  	; 学生人数初始化.
  	mov	cx,	0
  	
  	; 统计学生人数.
__count_loop:
		mov	ax,	cx
		call	ReadStud
		cmp	ax,	FALSE
		je		__CountOK
		inc	cx
		jmp	__count_loop

__CountOK:
		lea	dx,	szCountInfo
		call	PrintStr
		
		mov	ah,	2
		mov	dl,	cl
		add	dl,	48
		int	21h
	
  	pop	dx
  	pop	ax
  	pop	cx
  	ret
CountStud endp



; 打印学生信息.
PrintStud proc
  	push	dx
  	
  	lea	dx,	szStudInfo
  	call	PrintStr
  	
  	; 输出姓名.
  	lea	dx,	szInputName
  	call	PrintStr
  	lea	dx,	g_Student.m_szName
  	call	PrintStr
  	
  	; 输出年龄.
  	lea	dx,	szInputAge
  	call	PrintStr
  	lea	dx,	g_Student.m_iAge
  	call	PrintStr
  	
  	; 输出数学成绩.
  	lea	dx,	szInputMath
  	call	PrintStr
  	lea	dx,	g_Student.m_iMath
  	call	PrintStr
  	
  	; 输出英语成绩.
  	lea	dx,	szInputEnglish
  	call	PrintStr
  	lea	dx,	g_Student.m_iEnglish
  	call	PrintStr
  	
  	call	PrintEndl
  	pop	dx
  	ret
PrintStud endp


; 列出所有学生信息.
ListStud proc
  	push	ax
  	push	cx
  	
  	mov	cx,	0
__List_loop:
		mov	ax,	cx
		call	ReadStud
		cmp	ax,	FALSE
		je		__List_Complete
		inc	cx
		call	PrintStud
		jmp	__List_loop
	
__List_Complete:
		pop	cx
		pop	ax
		ret
ListStud endp



; 程序入口函数.
__Main proc
  	mov	ax,	__Data
  	mov	ds,	ax
  	
  	mov	ax,	__Stack
  	mov	ss,	ax
  	
  	; 读取第0个学生数据.
  	mov	ax,	0
  	call	ReadStud
  	cmp	ax,	TRUE
  	je		__loop
  	
  	; 如果读取成功则直接开始.否则先建立一个文件.
  	mov	ah,	3ch
  	mov	cx,	0
  	lea	dx,	szFileName
  	int	21h
  	
  	; 关闭创建的文件.
  	mov	bx,	ax
  	mov	ah,	CLOSE_FILE_HANDLE
  	int	21h

__loop:
		call	PrintInteface
		cmp	ah,	EXIT_SYSTEM
		je		__Exit
		
		cmp	ah,	INSERT_STUD
		je		_call_InsertStud
		
		cmp	ah,	DELETE_STUD
		je		_call_DeleteStud
		
		cmp	ah,	QUERY_STUD
		je		_call_QueryStud
		
		cmp	ah,	COUNT_STUD
		je		_call_CountStud
		
		cmp	ah,	MODIFY_STUD
		je		_call_ModifyStud
		
		cmp	ah,	PRINT_STUD
		je		_call_PrintStud
		
		cmp	ah,	LIST_STUD
		je		_call_ListStud
		jmp	__NextInput
		
_call_InsertStud:
		call	InsertStud
		jmp	__NextInput
		
_call_DeleteStud:
		call	DeleteStud
		jmp	__NextInput
		
_call_ModifyStud:
		call	ModifyStud
		jmp	__NextInput
		
_call_QueryStud:
		call	QueryStud
		jmp	__NextInput
		
_call_CountStud:
		call	CountStud
		jmp	__NextInput
		
_call_PrintStud:
		call	PrintStud
		jmp	__NextInput
	
_call_ListStud:
		call	ListStud
		jmp	__NextInput
	
; 等待用户的下一次选择命令.
__NextInput:
		jmp	__loop
	
; 退出程序.
__Exit:
		mov	ax,	4c00h
		int	21h

__Main endp


__Code ends

	end __Main
