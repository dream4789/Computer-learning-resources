;------------------------------------------------------------------------------
; ���õĳ�������.
;------------------------------------------------------------------------------
INSERT_STUD			equ	'i'			; ����ѧ����Ϣ.
DELETE_STUD			equ	'd'			; ɾ��ѧ��.
MODIFY_STUD			equ	'm'			; �޸�ѧ����Ϣ.
QUERY_STUD			equ	'q'			; ����ѧ��.
COUNT_STUD			equ	'c'			; ����ѧ������.
PRINT_STUD			equ	'p'			; ��ӡ���ѧ����Ϣ.
LIST_STUD			  equ 'l'			; �г�����ѧ��.
EXIT_SYSTEM			equ	'e'			; �˳�����ϵͳ.

NAME_MAXLEN			equ	20			; ѧ����������󳤶�.
INT_DATA_LEN		equ	3			  ; һ�������ĳ���.
STUD_STRUCT_LEN	equ	NAME_MAXLEN + 3 * INT_DATA_LEN + 6				; һ��ѧ��ռ���ڴ泤��.

CREATE_OPEN_FILE	equ	716ch		; �򿪻򴴽��ļ�.
CLOSE_FILE_HANDLE	equ	3eh			; �ر��ļ����.
READ_ONLY		   	  equ 0			  ; ֻ���ļ�.
WRITE_ONLY			  equ	1			  ; ֻд�ļ�.
READ_AND_WRITE		equ	2			  ; ��д�ļ�.
MOVE_FILE_POINTER	equ	42h			; �ƶ��ļ�ָ��.

TRUE				equ	1			; ��ֵ.
FALSE				equ	0			; ��ֵ.


;------------------------------------------------------------------------------
; ���̻������ṹ.
;------------------------------------------------------------------------------
KeyboardInfo struc
  	m_iMaxInput		db		NAME_MAXLEN				  	; ���������ַ���.
  	m_iInputCnt		db		0							        ; ʵ��������ַ���.
  	m_szBuffer		db		NAME_MAXLEN dup('$')  ; ��������Ļ���.
KeyboardInfo ends


;------------------------------------------------------------------------------
; ѧ���ṹ.
;------------------------------------------------------------------------------
Student struc
  	m_szName		db		NAME_MAXLEN  dup ('$'), '$'		; ѧ������.
  	m_iAge			db		INT_DATA_LEN dup ('$'), '$'		; ѧ������.
  	m_iMath			db		INT_DATA_LEN dup ('$'), '$'		; ��ѧ�ɼ�.
  	m_iEnglish	db		INT_DATA_LEN dup ('$'), '$'		; Ӣ��ɼ�.
  	__ENDL_CH		db		0dh, 0ah						; ����ռλ��.
Student ends


;------------------------------------------------------------------------------
; ���ݶ�.
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
  	szFileName		db 'StudInfo.txt', 0				; �ļ���.
  	szTempFile		db 'StudTemp.txt', 0				; ��ʱ�ļ���.
  	hFileHandle		dw	0								        ; �ļ����.
  	
  	szQueryName		db NAME_MAXLEN dup('$'), '$'	; ����ѧ�������������.
  	g_Keyboard		KeyboardInfo <>					; ȫ�ֵļ��̻���ṹ.
  	g_Student		  Student	<>						  ; ȫ�ֵ�ѧ���ṹ.
__Data ends



;------------------------------------------------------------------------------
; ��ջ��.
;------------------------------------------------------------------------------
__Stack segment stack
	  stack_elements dd 1024 dup(0)
__Stack ends



;------------------------------------------------------------------------------
; �����.
;------------------------------------------------------------------------------
__Code segment
	  assume CS:__Code, DS:__Data, SS:__Stack


; ���漰����.���غ�ah����û�������.
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


; ������з�.
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



; ���һ���ַ���.�ַ�����ַ��DS:DX��.
PrintStr proc
  	push	ax
  	
  	mov	ah,	9h
  	int	21h
  	
  	pop	ax
  	ret
PrintStr endp


; ����һ��ѧ����Ϣ.
InputStud proc
  	push	ax
  	push	bx
  	push	cx
  	push	dx
  	push	si
  	push	di
  	
  	; ��ʾ������ʾ��Ϣ.
  	lea	dx,	szInputStud
  	mov	ah,	9h
  	int	21h
  	
  	mov	ax,	__Data
  	mov	es,	ax
  	
  	; ��������.
  	lea	dx,	szInputName
  	mov	ah,	9h
  	int	21h
  	
  	mov	ah,	0ah
  	lea	dx,	g_Keyboard
  	int	21h
  	
  	; ��������.
  	mov	cl,	g_Keyboard.m_iInputCnt
  	mov	ch,	0
  	mov	bx,	cx
  	lea	si,	g_Keyboard.m_szBuffer
  	lea	di,	g_Student.m_szName
  	cld
  	rep	movsb
  	
  	; ��֤�ַ������λ�������ض�.
  	mov	g_Student.m_szName[bx], '$'
  	
  	; ��������.
  	lea	dx,	szInputAge
  	mov	ah,	9h
  	int	21h
  	
  	mov	ah,	0ah
  	lea	dx,	g_Keyboard
  	int	21h
  	
  	; ��������.
  	mov	cl,	g_Keyboard.m_iInputCnt
  	mov	ch,	0
  	mov	bx,	cx
  	lea	si,	g_Keyboard.m_szBuffer
  	lea	di,	g_Student.m_iAge
  	cld
  	rep	movsb
  	
  	mov	g_Student.m_iAge[bx], '$'
  	
  	; ������ѧ�ɼ�.
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
  	
  	; ����Ӣ��ɼ�.
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


; ����һ��ѧ����Ϣ.
InsertStud proc
  	; ����ѧ����Ϣ.
  	call	InputStud
  	; ѧ����Ϣд���ļ�.
  	call	WriteStud
  	ret
InsertStud endp



; ��ȡһ��ѧ����Ϣ.
; [in]  ax��ʾҪ��ȡ��ѧ�����ļ��е�����.
; [out] axΪTRUE��ʾ��ȡ�ɹ�,ΪFALSE��ʾ���ļ�β���ȡʧ��.
ReadStud proc
	push	bx
	push	cx
	push	dx
	push	si
	push	di
	
	; �򿪲��ƶ��ļ�ָ��. ax���ƫ����.
	call	SeekFile
	
	; ��ȡ�ļ�.
	mov	ah,	3fh
	mov	bx,	hFileHandle
	mov	cx,	STUD_STRUCT_LEN
	lea	dx,	g_Student
	int	21h
	jc		__FailedRet
	
	; �����ȡ���ֽ���.
	mov	di,	ax
	
	; �ر��ļ�.
	mov	ah,	CLOSE_FILE_HANDLE
	mov	bx,	hFileHandle
	int	21h
	jc		__FailedRet
	
	; ���Ƿ񵽴��ļ�β.
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


; �ƶ��ļ�ָ��.ax���ƫ��.
; �ȴ��ļ�,hFileHandle ��Ŵ򿪵��ļ�ָ��.
; �����󲢲��ر��ļ�.ax�з��ش���.
SeekFile proc
	push	bx
	push	cx
	push	dx
	push	si
	push	di
	
	mov	di,	ax
	
	; ���ļ�.
	mov	ax,	CREATE_OPEN_FILE
	mov	bx,	READ_AND_WRITE
	mov	cx,	0
	mov	dx, 	1
	lea	si,	szFileName
	int	21h
	jc		__FailedSeek
	
	; ȡ���ļ����.
	mov	hFileHandle,	ax
	
	; ȡ��ƫ����. DX:AX
	mov	ax,	di
	mov	dx,	STUD_STRUCT_LEN
	mul	dx
	
	; �ƶ����ļ�ƫ��λ��. CX:DX
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


; ��ѧ����Ϣд���ļ�.
; [in] g_Student
WriteStud proc
	push	ax
	push	bx
	push	cx
	push	dx
	push	si
	
	; ���ļ�.
	mov	ax,	CREATE_OPEN_FILE
	mov	bx,	WRITE_ONLY
	mov	cx,	0
	mov	dx,	1
	lea	si,	szFileName
	int	21h
	jc		__Failed
	mov	hFileHandle,	ax
	
	; �ƶ����ļ�β.
	mov	ah,	MOVE_FILE_POINTER
	mov	al,	2
	mov	bx,	hFileHandle
	mov	dx,	0
	mov	cx,	0
	int	21h
	
	; д���ļ�.
	mov	ah,	40h
	mov	bx,	hFileHandle
	mov	cx,	STUD_STRUCT_LEN
	lea	dx,	g_Student
	int	21h
	jc		__Failed
	
	; �ر��ļ�.
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


; ɾ��һ��ѧ����Ϣ.
; ����һ����ʱ�ļ�(szTempFile),����ɾ����ѧ����Ϣд��.
; ����ɾ��ԭ�����ļ�(szFileName),����ʱ�ļ�������Ϊԭ�����ļ�����.
DeleteStud proc
  	push	ax
  	push	bx
  	push	cx
  	push	dx
  	push	si
  	push	di
  	
  	; �Ȳ���Ҫɾ����ѧ���Ǵ���.
  	call	QueryStud
  	cmp	ax,	-1
  	je		__DeleteFailed
  	
  	; ������ҵ���ѧ������.
  	; inc si �Ǳ�Ҫ�ģ�������[1]
  	mov	si,	ax
  	inc	si
  	
  	; ����һ����ʱ�ļ�.
  	mov	ah,	3ch
  	mov	cx,	0
  	lea	dx,	szTempFile
  	int	21h
  	
  	; �����ļ����.
  	mov	di,	ax
  	
  	mov	cx,	0
__ReadStud:
		mov	ax,	cx
		call	ReadStud
		cmp	ax,	FALSE
		je		__DeleteComplete
		
		; ���������ͬ�򲻱�д��,ֱ�Ӷ�ȡ��һ��.
		; [1] inc cx ������ cmp����֮ǰ,�����Ӱ��je����ת.
		inc	cx
		cmp	cx,	si
		je		__ReadStud
		
		push	cx
		; ����Ϣд����ʱ�ļ�.
		mov	ah,	40h
		mov	bx,	di
		mov	cx,	STUD_STRUCT_LEN
		lea	dx,	g_Student
		int	21h
		pop	cx
		
		jmp	__ReadStud
	
__DeleteComplete:
		; �ر���ʱ�ļ�.
		mov	ah,	CLOSE_FILE_HANDLE
		mov	bx,	di
		int	21h
		
		; ɾ��ԭ�����ļ�.
		lea	dx,	szFileName
		mov	ah,	41h
		int	21h
		
		; ��������ʱ�ļ�Ϊԭ�����ļ�.
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



; ����һ��ѧ��.������ҵ�,��ax�д�����ļ��е�����.
; ����ax�д��-1.
QueryStud proc
  	push	bx
  	push	cx
  	push	dx
  	push	si
  	push	di
  	
  	; �����ѯ����.
  	lea	dx,	szQueryInfo
  	mov	ah,	9h
  	int	21h
  	
  	mov	ah,	0ah
  	lea	dx,	g_Keyboard
  	int	21h
  	
  	; ������ѯ����.
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
  	
  	; cx����ַ����ıȽϳ���.
  	; dx����Ѿ����ҵ���������.
  	mov	bx,	0

__Query_loop:
		mov	ax,	bx
		call	ReadStud
		cmp	ax,	FALSE
		je		__QueryFailed
		inc	bx
		
		mov	cl,	g_Keyboard.m_iInputCnt
		mov	ch,	0
		
		; ������ҵ������ֺ�Ϊ������'$',����û���ҵ�.
		mov	si,	cx
		mov	ah,	g_Student.m_szName[si]
		cmp	ah,	'$'
		jne	__Query_loop
		
		; ��ʽ�Ƚ������Ƿ�һ��.
		lea	si,	g_Student.m_szName
		lea	di,	szQueryName
		repe	cmpsb
		jne	__Query_loop
		
		
  	; ���ִ�е����,˵���ҵ���ѧ��.��������Ϣ��ʾ����.
  	; ���������浽ax��.
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



; �޸�ѧ����Ϣ.
ModifyStud proc
  	push	ax
  	push	bx
  	push	cx
  	
  	call	QueryStud
  	cmp	ax,	-1
  	je		__ModifyFailed
  	
  	push	ax
  	; ��������ѧ����Ϣ.
  	call	InputStud
  	pop	ax
  	
  	; �ƶ��ļ�ָ��.
  	call	SeekFile
  	
  	; ����Ϣд���ļ�.
  	mov	ah,	40h
  	mov	bx,	hFileHandle
  	mov	cx,	STUD_STRUCT_LEN
  	lea	dx,	g_Student
  	int	21h
  	jc		__ModifyFailed
  	
  	; �ر��ļ�.
  	mov	ah,	CLOSE_FILE_HANDLE
  	mov	bx,	hFileHandle
  	int	21h
  	
__ModifyFailed:
		pop	cx
		pop	bx
		pop	ax
		ret
ModifyStud endp



; ����ѧ������.
CountStud proc
  	push	cx
  	push	ax
  	push	dx
  	
  	; ѧ��������ʼ��.
  	mov	cx,	0
  	
  	; ͳ��ѧ������.
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



; ��ӡѧ����Ϣ.
PrintStud proc
  	push	dx
  	
  	lea	dx,	szStudInfo
  	call	PrintStr
  	
  	; �������.
  	lea	dx,	szInputName
  	call	PrintStr
  	lea	dx,	g_Student.m_szName
  	call	PrintStr
  	
  	; �������.
  	lea	dx,	szInputAge
  	call	PrintStr
  	lea	dx,	g_Student.m_iAge
  	call	PrintStr
  	
  	; �����ѧ�ɼ�.
  	lea	dx,	szInputMath
  	call	PrintStr
  	lea	dx,	g_Student.m_iMath
  	call	PrintStr
  	
  	; ���Ӣ��ɼ�.
  	lea	dx,	szInputEnglish
  	call	PrintStr
  	lea	dx,	g_Student.m_iEnglish
  	call	PrintStr
  	
  	call	PrintEndl
  	pop	dx
  	ret
PrintStud endp


; �г�����ѧ����Ϣ.
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



; ������ں���.
__Main proc
  	mov	ax,	__Data
  	mov	ds,	ax
  	
  	mov	ax,	__Stack
  	mov	ss,	ax
  	
  	; ��ȡ��0��ѧ������.
  	mov	ax,	0
  	call	ReadStud
  	cmp	ax,	TRUE
  	je		__loop
  	
  	; �����ȡ�ɹ���ֱ�ӿ�ʼ.�����Ƚ���һ���ļ�.
  	mov	ah,	3ch
  	mov	cx,	0
  	lea	dx,	szFileName
  	int	21h
  	
  	; �رմ������ļ�.
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
	
; �ȴ��û�����һ��ѡ������.
__NextInput:
		jmp	__loop
	
; �˳�����.
__Exit:
		mov	ax,	4c00h
		int	21h

__Main endp


__Code ends

	end __Main
