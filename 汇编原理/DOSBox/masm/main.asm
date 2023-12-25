;----------------------------------------------------------------------------
;	              S E G M E N T  STARTS
;----------------------------------------------------------------------------
include mnmacro.asm
data segment
scrmm	db 100 dup(?)
;----------------------------------------------------------------------------
;	              mainmenu name
;----------------------------------------------------------------------------
mainmenu1	db 'File'
mainmenu2	db 'Tool'
mainmenu3	db 'R8042'
mainmenu4	db 'Other'
mainmenu5	db 'Extra'
mainmenu6 db 'Help'
;----------------------------------------------------------------------------
;	             file's submenu name
;----------------------------------------------------------------------------
submenu11	db 'Save'
submenu12	db 'Open'
submenu13	db 'Exit'
;----------------------------------------------------------------------------
;	             Tool's submenu name
;----------------------------------------------------------------------------
submenu21	db 'I O'
submenu22	db 'ISA '
submenu23	db 'Memory'
;----------------------------------------------------------------------------
;	             R8042's submenu name
;----------------------------------------------------------------------------
submenu31	db 'A20'
submenu32	db 'reboot'
submenu33	db 'LED '
;----------------------------------------------------------------------------
;	             other's submenu name
;----------------------------------------------------------------------------
submenu41	db 'PCI '
submenu42	db 'Beep'
submenu43	db 'e820  '
;----------------------------------------------------------------------------
;	             extra's submenu name
;----------------------------------------------------------------------------
submenu51	db 'CMOS '
submenu52	db 'int'
submenu53	db '=== '
;----------------------------------------------------------------------------
;                    help's submenu name
;----------------------------------------------------------------------------
submenu61 db 'about'
submenu62 db '     '
submenu63 db '     '
;----------------------------------------------------------------------------
;		Welcome window information
;----------------------------------------------------------------------------
msgtitle	db 'Assemble Design'
msg1      db 'Please press Alt+F,Alt+T,Alt+R,Alt+O,Alt+E,Alt+H or ',19h,' to open the submenu.'
msg2	    db 'Please press Enter (',11h,0c4h,0d9h,') to close the submenu.'
msg3   	  db 'Please press ',1bh,' or ',1ah,' to select the mainmenu.'
msg4	    db 'Please press ',18h,' or ',19h,' to select the submenu.'
msg5	    db 'Copyright 2012 keven.gao from KS.'
msg6	    db 'Press any key to continue...'
msg7	    db '                   '
;----------------------------------------------------------------------------
;		exit window information
;----------------------------------------------------------------------------
over	  db 'Thank you for using...Good bye!!!!'
;----------------------------------------------------------------------------
;		other information
;----------------------------------------------------------------------------
escape	db 'Press ESC to exit                    E-mail:gaokang321@gmail.com'
text1	  db 'This is a simple tool ru, there are io, memory, pci, isa, e820, '
text2	  db 'a20, keyboard led, reboot and beep, etc. You can use this gadget'
text3	  db 'to view their status, or to achieve a particular effect.'
text4   db '================================================================'
text5	  db 'Thank you very much.enjoy it!'
text6	  db '                                         ---powered by keven.gao'
sub11	  db 'Select Save'
sub12	  db 'Select Open'
sub13	  db 'Select Exit'
sub21	  db 'Select I O'
sub22	  db 'Select ISA '
sub23	  db 'Select Memory'
sub31	  db 'Select a20'
sub32	  db 'Select reboot'
sub33	  db 'Select LED'
sub41	  db 'Select PCI'
sub42	  db 'Select Beep'
sub43	  db 'Select e820'
sub51	  db 'Select CMOS'
sub52	  db 'Select int'
sub53	  db 'Select === '
sub61   db 'Select about'
sub62   db 'Select      '
sub63   db 'Select      '
;----------------------------------------------------------------------------
mainnum   db 1			;Main menu sequence number(主菜单序列号）
subnum	  db ?			;Sub menu sequence number（子菜单序列号)
subshow   db 0			;0 sub menu is not displayed(为0时子菜单不显示）
mainindex db ?			;Main menu character length（主菜单字符长度）
data ends
;----------------------------------------------------------------------------
code segment
assume cs:code,ds:data,es:data

	extern memory1:far
	extern io1:far
	extern pci1:far
	extern isa1:far
	extern beep1:far
	extern a201:far
	extern e8201:far
	extern key1:far
	extern reboot1:far
	extern cmos1:far
	extern int1:far
	extern about1:far
start:
	mov ax,data
	mov ds,ax
	mov es,ax
;----------------------------------------------------------------------------
;		Initializing screen start（初始化屏幕开始）
;----------------------------------------------------------------------------
	mov ah,0
	mov al,03h
	int 10h
;----------------------------------------------------------------------------
;               Initializing screen end（初始化屏幕结束）
;----------------------------------------------------------------------------
	showcur 1	;Hide cursor(隐藏光标)
;----------------------------------------------------------------------------
;		Start the main window drawing
;----------------------------------------------------------------------------
	drawwindow 1eh,0,0,24,79
	outputstr  msgtitle,15,10,30,1fh
	outputstr  msg1,73,15,5,17h
	changemenu 15,18,5,1eh
	changemenu 15,24,5,1eh
	changemenu 15,30,5,1eh
	changemenu 15,36,5,1eh
	changemenu 15,42,5,1eh
	changemenu 15,48,5,1eh
	changemenu 15,57,1,1eh
	outputstr  msg2,46,16,5,17h
	changemenu 16,18,11,1eh
	outputstr  msg3,43,17,5,17h
	changemenu 17,18,1,1eh
	changemenu 17,23,1,1eh
	outputstr  msg4,42,18,5,17h
	changemenu 18,18,1,1eh
	changemenu 18,23,1,1eh
	outputstr  msg5,33,13,5,1fh
	outputstr  msg6,28,20,40,9eh
	outputstr  msg7,19,9,28,93h
	outputstr  msg7,19,11,28,93h
	setpos 10,28
	outputchar ' ',93h,1
	setpos 10,46
	outputchar ' ',93h,1
	mov ah,07h
	int 21h
	drawwindow 1eh,0,0,24,79
	drawwindow 70h,0,0,0,79
	drawwindow 70h,24,0,24,79
	setpos 1,0
	windowtandb 0d5h,0cdh,0b8h,1,0,80,1eh			;Top and bottom border
	mov al,2
draw:
	windowlandr 0b3h,al,0,80,1eh
	inc al
	cmp al,17h
	jne draw
	windowtandb 0c0h,0c4h,0d9h,23,0,80,1eh
	outputstr escape,64,24,3,70h             ;宽度64,24行，颜色70h，
;----------------------------------------------------------------------------
;		Start menu drawing
;----------------------------------------------------------------------------
	setpos 0,3
	outputstr mainmenu1,4,0,3,0fh
	outputstr mainmenu2,4,0,13,70h
	changemenu 0,13,1,74h
	outputstr mainmenu3,5,0,23,70h
	changemenu 0,23,1,74h
	outputstr mainmenu4,5,0,33,70h
	changemenu 0,33,1,74h
	outputstr mainmenu5,5,0,43,70h
	changemenu 0,43,1,74h
  outputstr mainmenu6,4,0,53,70h
	changemenu 0,53,1,74h
	setpos 0,3
;----------------------------------------------------------------------------
;		End of the main window and menu drawing
;----------------------------------------------------------------------------
	outputstr msg1,73,15,5,17h
	changemenu 15,18,5,1eh
	changemenu 15,24,5,1eh
	changemenu 15,30,5,1eh
	changemenu 15,36,5,1eh
	changemenu 15,42,5,1eh
	changemenu 15,48,5,1eh
	changemenu 15,57,1,1eh
	outputstr msg2,46,16,5,17h
	changemenu 16,18,11,1eh
	outputstr msg3,43,17,5,17h
	changemenu 17,18,1,1eh
	changemenu 17,23,1,1eh
	outputstr msg4,42,18,5,17h
	changemenu 18,18,1,1eh
	changemenu 18,23,1,1eh
	outputstr text1,63,3,5,1ah
	outputstr text2,64,4,5,1ah
	outputstr text3,56,5,5,1ah
	outputstr text4,64,6,5,1ah
	outputstr text5,29,7,5,1ah
	outputstr text6,64,8,5,1ah ;字符个数64，行8，开始列5，颜色属性1ah
;----------------------------------------------------------------------------
;		;Message receiving cycle(接受消息循环）
;----------------------------------------------------------------------------
input:						
	mov	ah, 0
	int	16h             ;ah=字符的扫描码
	cmp	ah, 01h		;esc的扫描码是01h      
	jne	continue1
	call	exit
	jmp	input
continue1:
	cmp	ah, 4bh		;left的扫描码是4bh
	jne	continue2
	call	prsleft
	jmp	input
continue2:
	cmp	ah, 4dh		;right的扫描码是4dh
	jne	continue3
	call	prsright
	jmp	input
continue3:
	cmp	ah, 50h		;down的扫描码是50h    
	jne	continue4
	call	prsdown
	jmp	input
continue4:
	cmp	ah, 21h         ;key f
	jne	continue5       
	mov	ah, 02h
	int	16h
	and	al, 0fh
	cmp	al, 08h
	jne	continue5
	call	FAlt
	jmp	input
continue5:
	cmp	ah, 14h         ;key t
	jne	continue6
	mov	ah, 02h
	int	16h             ;取变换键当前状态,al=变换键当前状态
;-----------------------------------------------------------------------
	;前面我们已经提到Shift、Ctrl 、Alt、Num Lock、Scroll、Ins 和
	;Caps Lock这些键不具有ASCII码，但按动了它们能改变其它键所产生
	;的代码，那么如何能判断这些键按动与否呢？在键盘状态字节中高4位
	;指出各种键盘方式（Ins、Caps Lock、Num Lock、Scroll）是ON（1）
	;还是OFF（0）；低4位表示Alt、Ctrl、leftShift、rightshift键是否按动。
	;这8个键有
	;时又被称为变换键。使用INT 16H的AH=2的功能即可得到这些键状态
	;的信息。
;-----------------------------------------------------------------------
	and	al, 0fh         ;高4位清零
	cmp	al, 08h         ;检查alt键
	jne	continue6
	call	talt
	jmp	input
continue6:
	cmp	ah, 13h         ;key r
	jne	continue7
	mov	ah, 02h
	int	16h
	and	al, 0fh
	cmp	al, 08h
	jne	continue7
	call	RAlt
	jmp	input
continue7:
	cmp	ah, 18h         ;key o
	jne	continue8
	mov	ah, 02h
	int	16h
	and	al, 0fh
	cmp	al, 08h
	jne	continue8
	call	OAlt
	jmp	input
continue8:
	cmp	ah, 12h         ;key e
	jne	continue9
	mov	ah, 02h
	int	16h
	and	al, 0fh
	cmp	al, 08h
	jne	continue9
	call	ealt
	jmp	input
continue9:
	cmp	ah, 23h         ;key h
	jne	continue10
	mov	ah, 02h
	int	16h
	and	al, 0fh
	cmp	al, 08h
	jne	continue10
	call	halt
	jmp	input
continue10:
	cmp	ah, 48h		;up
	jne	continue11
	call	prsup
	jmp	input
continue11:
	cmp	ah, 1ch		;enter
	jne	continue12
	call	prsenter
	jmp	input
continue12:
	jmp	input
; ===========================================================================
prsenter proc near			;Press the ENTER key
	cmp	subshow, 0
	jne	enter1
	call	prsdown
	ret
enter1:
	mov	al,mainnum
	push	ax
	mov	cl, 0ah
	mul	cl
	sub	ax, 07h
	mov	mainnum,al
	dec	mainnum
	writescr mainnum,scrmm
	inc	mainnum
	setpos 0,mainnum
	pop	ax
	mov	mainnum,al
	drawwindow 13h,22,4,22,50
	cmp	mainnum, 1
	jne	prsenter1
	cmp	subnum, 2
	jne	entersub12
	outputstr sub11,11,22,5,13h
entersub12:
	cmp	subnum, 3
	jne	entersub13
	outputstr sub12,11,22,5,13h
entersub13:
	cmp	subnum, 4
	jne	prsenter1
	outputstr sub13,11,22,5,13h
	call	exit
prsenter1:
	cmp	mainnum, 2
	jne	prsenter2

	cmp	subnum, 2
	jne	entersub22
	call	io1
	jmp	start

entersub22:
	cmp	subnum, 3
	jne	entersub23
	call	isa1
	jmp	start

entersub23:
	cmp	subnum, 4
	jne	prsenter2
	call	memory1
	jmp	start

prsenter2:
	cmp	mainnum, 3
	jne	prsenter3
	cmp	subnum, 2
	jne	entersub32
	call	a201
	jmp	start

entersub32:
	cmp	subnum, 3
	jne	entersub33
	call	reboot1
	jmp	start

entersub33:
	cmp	subnum, 4
	jne	prsenter3
	call	key1
	jmp	start

prsenter3:
	cmp	mainnum, 4
	jne	prsenter4
	cmp	subnum, 2
	jne	entersub42
	call	pci1
	jmp	start

entersub42:
	cmp	subnum, 3
	jne	entersub43
	call	beep1
	jmp	start

entersub43:
	cmp	subnum, 4
	jne	prsenter4
	call	e8201
	jmp	start

prsenter4:
	cmp	mainnum, 5
	jne	prsenter5
	cmp	subnum, 2
	jne	entersub52
	call	cmos1
	jmp	start

entersub52:
	cmp	subnum, 3
	jne	entersub53
	call	int1
	jmp	start
entersub53:
	cmp	subnum, 4
	jne	prsenter5
	outputstr sub53,10,22,5,13h
prsenter5:
        cmp	mainnum, 6
	jne	prsenter6
	cmp	subnum, 2
	jne	entersub62
	call	cmos1
	jmp	start

entersub62:
	cmp	subnum, 3
	jne	entersub63
	call	int1
	jmp	start
entersub63:
	cmp	subnum, 4
	jne	prsenter6
	;outputstr sub53,10,22,5,13h
prsenter6:
	mov	subshow, 0
	ret
prsenter endp
; ===========================================================================
halt proc near					;H+Alt
	mov	al,mainnum
	mov	cl,0ah
	mul	cl
	sub	ax,07h
	mov	mainnum,al
	cmp	subshow, 1
	jne	hshow
	dec	mainnum
	writescr mainnum,scrmm
	inc	mainnum
hshow:
	readscr 52,scrmm
	submenu 52,submenu61,5,submenu62,5,submenu63,5,9
	changemenu 0,mainnum,5,70h
	changemenu 0,mainnum,1,74h
	mov	mainnum, 06h
	changemenu 0,53,4,0fh
	changemenu 2,54,6,0fh
	mov	subnum, 2
	mov	subshow, 1
	setpos 0,53
	ret
halt endp
; ===========================================================================
ealt proc near					;E+Alt
	mov	al,mainnum
	mov	cl,0ah
	mul	cl
	sub	ax,07h
	mov	mainnum,al
	cmp	subshow, 1
	jne	eshow
	dec	mainnum
	writescr mainnum,scrmm
	inc	mainnum
eshow:
	readscr 42,scrmm
	submenu 42,submenu51,5,submenu52,3,submenu53,3,9
	changemenu 0,mainnum,5,70h
	changemenu 0,mainnum,1,74h
	mov	mainnum, 05h
	changemenu 0,43,5,0fh
	changemenu 2,44,6,0fh
	mov	subnum, 2
	mov	subshow, 1
	setpos 0,43
	ret
ealt endp
; ===========================================================================
oalt proc near					;O+Alt
	mov	al,mainnum
	mov	cl,0ah
	mul	cl
	sub	ax,07h
	mov	mainnum,al
	cmp	subshow, 1
	jne	oshow
	dec	mainnum
	writescr mainnum,scrmm
	inc	mainnum
oshow:
	readscr 32,scrmm
	submenu 32,submenu41,4,submenu42,4,submenu43,6,9
	changemenu 0,mainnum,5,70h
	changemenu 0,mainnum,1,74h
	mov	mainnum, 04h
	changemenu 0,33,5,0fh
	changemenu 2,34,6,0fh
	mov	subnum, 2
	mov	subshow, 1
	setpos 0,33
	ret
oalt endp
; ===========================================================================
ralt proc near					;R+Alt
	mov	al,mainnum
	mov	cl,0ah
	mul	cl
	sub	ax,07h
	mov	mainnum,al
	cmp	subshow, 1
	jne	rshow
	dec	mainnum
	writescr mainnum,scrmm
	inc	mainnum
rshow:
	readscr 22,scrmm
	submenu 22,submenu31,3,submenu32,6,submenu33,4,9
	changemenu 0,mainnum,5,70h
	changemenu 0,mainnum,1,74h
	mov	mainnum, 03h
	changemenu 0,23,5,0fh
	changemenu 2,24,6,0fh
	mov	subnum, 2
	mov	subshow, 1
	setpos 0,23
	ret
ralt endp
; ===========================================================================
talt proc near					;T+Alt
	mov	al,mainnum
	mov	cl,0ah
	mul	cl
	sub	ax,07h
	mov	mainnum,al
	cmp	subshow, 1
	jne	tshow
	dec	mainnum
	writescr mainnum,scrmm
	inc	mainnum
tshow:
	readscr 12,scrmm
	submenu 12,submenu21,3,submenu22,4,submenu23,6,9
	changemenu 0,mainnum,5,70h
	changemenu 0,mainnum,1,74h
	mov	mainnum, 02h
	changemenu 0,13,4,0fh
	changemenu 2,14,6,0fh
	mov	subnum, 2
	mov	subshow, 1
	setpos 0,13
	ret
talt endp
; ===========================================================================
falt proc near					;F+Alt
	mov	al,mainnum
	mov	cl, 0ah
	mul	cl
	sub	ax, 07h
	mov	mainnum,al
	cmp	subshow, 1
	jne	fshow
	dec	mainnum
	writescr mainnum,scrmm
	inc	mainnum
fshow:
	readscr 2,scrmm
	submenu 2,submenu11,4,submenu12,4,submenu13,4,9
	changemenu 0,mainnum,5,70h
	changemenu 0,mainnum,1,74h
	mov	mainnum,01h
	changemenu 0,3,4,0fh
	changemenu 2,4,6,0fh
	mov	subnum, 2
	mov	subshow, 1
	setpos 0,3
	ret
falt endp
; ===========================================================================
prsup proc near					; Press the up arrow
	cmp	subshow,0
	jne	prsup2
	ret
prsup2:
	mov	al,mainnum
	push ax
	mov	cl,0ah
	mul	cl
	sub	ax,07h
	mov mainnum,al
	changemenu subnum,mainnum,8,70h
	inc	mainnum
	changemenu subnum,mainnum,1,74h
	pop ax
	mov	mainnum,al
	cmp	subnum,02h
	jne	prsuptop
	mov	subnum,04h
	jmp	prsup1
prsuptop:
	dec	subnum
prsup1:
	mov	al,mainnum
	push ax
	mov	cl, 0ah
	mul	cl
	sub	ax, 07h
	mov	mainnum, al
	changemenu subnum,mainnum,8,0fh
	pop ax
	mov	mainnum, al
	ret
prsup endp
; ===========================================================================
prsdown proc near				; Press the down arrow
	cmp	subshow,0
	jne	prsdown2
	cmp	mainnum,1
	jne	prsdown3
	call	falt
	jmp	prsdown8
prsdown3:
	cmp	mainnum,2
	jne	prsdown4
	call	talt
	jmp	prsdown8
prsdown4:
	cmp	mainnum,3
	jne	prsdown5
	call	ralt
	jmp	prsdown8
prsdown5:
	cmp	mainnum,4
	jne	prsdown6
	call	oalt
	jmp	prsdown8
prsdown6:
  cmp	mainnum,5   ;最坑爹的bug，这行代码自己手敲的和拷贝的效果竟然不一样!!!
	jne     prsdown7
	call    ealt
	jmp     prsdown8
prsdown7:
	call	halt
prsdown8:
	ret
prsdown2:
	mov	al,mainnum
	push	ax
	mov	cl, 0ah
	mul	cl
	sub	ax, 07h
	mov	mainnum, al
	changemenu subnum,mainnum,8,70h
	inc	mainnum
	changemenu subnum,mainnum,1,74h
	pop	ax
	mov	mainnum, al
	cmp	subnum, 04h
	jne	prsdownbot
	mov	subnum, 02h
	jmp	prsdown1
prsdownbot:
	inc	subnum
prsdown1:
	mov	al,mainnum
	push	ax
	mov	cl, 0ah
	mul	cl
	sub	ax, 07h
	mov	mainnum, al
	changemenu subnum,mainnum,8,0fh
	pop	ax
	mov	mainnum, al
	ret
prsdown endp
; ===========================================================================
prsright proc near				; Press the right arrow
	cmp	subshow,0
	je	prsright1
	call	prsrgtsub
	ret
prsright1:
	mov	al,mainnum
	push	ax
	mov	cl, 0ah ;00001010b
	mul	cl
	sub	ax, 07h ;00000111b
	mov	mainnum, al
	changemenu 0,mainnum,5,70h
	changemenu 0,mainnum,1,74h ;这里的1，代表一个字节的宽度，是主菜单的第一个红色的大写字母
	pop ax
	mov	mainnum, al
	cmp	mainnum, 06h  ;最后一个主菜单编号
	jne	prsright2
	mov	mainnum, 01h  ;第一个主菜单的编号
	jmp	prsright3
prsright2:
	inc	mainnum
prsright3:                    ;第二个主菜单
	cmp	mainnum, 1
	je	prsright4
	cmp	mainnum, 2
	je	prsright4
	cmp	mainnum, 5
	je	prsright5
	cmp	mainnum, 3
	je	prsright5
	cmp	mainnum, 4
	je	prsright5
	cmp     mainnum, 6
	je      prsright6
prsright4:
	mov	mainindex, 5
	jmp	prsright7
prsright5:
        mov     mainindex, 5
        jmp     prsright7
prsright6:
	mov	mainindex, 5
prsright7:
	mov	al,mainnum
	push	ax
	mov	cl, 0ah
	mul	cl
	sub	ax, 07h
	mov	mainnum, al
	changemenu 0,mainnum,mainindex,0fh ;当主菜单或者是子菜单被选中时，显示的黑底亮白的字体
	pop	ax
	mov	mainnum, al
	ret
prsright endp
; ===========================================================================
prsrgtsub proc near	;When the menu is opened to press the right arrow
	cmp	mainnum, 1
	jne	prsrgt1
	call	talt
	jmp	prsrgt6
prsrgt1:
	cmp	mainnum, 2
	jne	prsrgt2
	call	ralt
	jmp	prsrgt6
prsrgt2:
	cmp	mainnum, 3
	jne	prsrgt3
	call	oalt
	jmp	prsrgt6
prsrgt3:
	cmp	mainnum, 4
	jne	prsrgt4
	call	ealt
	jmp	prsrgt6
prsrgt4:
        cmp	mainnum, 5
	jne	prsrgt5
	call	halt
	jmp	prsrgt6
prsrgt5:
	call	falt
prsrgt6:
	ret
prsrgtsub endp
; ===========================================================================
prsleft proc near				;Press the left arrow
	cmp	subshow, 0
	je	prsleft1
	call	prslftsub
	ret
prsleft1:
	mov	al,mainnum
	push	ax
	mov	cl, 0ah
	mul	cl
	sub	ax, 07h
	mov	mainnum,al
	changemenu 0,mainnum,5,70h
	changemenu 0,mainnum,1,74h
	pop	ax
	mov	mainnum, al
	cmp	mainnum, 01h;第一个主菜单编号
	jne	prsleft2
	mov	mainnum, 06h;最后一个主菜单的编号，或者说是一共有6个主菜单
	jmp	prsleft3
prsleft2:
	dec	mainnum
prsleft3:
	cmp	mainnum, 1
	je	prsleft4
	cmp	mainnum, 2
	je	prsleft4
	cmp	mainnum, 5
	je	prsleft5
	cmp	mainnum, 3
	je	prsleft5
	cmp	mainnum, 4
	je	prsleft5
	cmp     mainnum, 6
	je      prsleft6
prsleft4:
	mov	mainindex, 5     ;E
	jmp	prsleft7
prsleft5:
	mov	mainindex, 5
	jmp	prsleft7
prsleft6:
	mov	mainindex, 5
prsleft7:
	mov	al,mainnum
	push	ax
	mov	cl, 0ah
	mul	cl
	sub	ax, 07h
	mov	mainnum, al
	changemenu 0,mainnum,mainindex,0fh
	pop	ax
	mov	mainnum, al
	ret
prsleft endp
; ===========================================================================
prslftsub proc near	;When the menu is opened by pressing the left arrow
;当菜单打开是按左箭头
      	cmp	mainnum, 1
	jne	prslft1
	call	halt
	jmp	prslft6
prslft1:
	cmp	mainnum, 2
	jne	prslft2
	call	falt
	jmp	prslft6
prslft2:
	cmp	mainnum, 3
	jne	prslft3
	call	talt
	jmp	prslft6
prslft3:
	cmp	mainnum, 4
	jne	prslft4
	call	ralt
	jmp	prslft6
prslft4:
        cmp     mainnum, 5
	jne     prslft5
	call    oalt
	jmp     prslft6
prslft5:
	call	ealt
prslft6:
	ret
prslftsub endp
; ===========================================================================
exit proc near				;Exit subpoc退出子程序
	drawwindow 1eh,0,0,24,79
	outputstr msgtitle,15,10,30,1fh
	outputstr over,34,15,21,1ch
	outputstr msg7,19,9,28,93h
	outputstr msg7,19,11,28,93h  ;总字数19，行11，颜色93h
	setpos 10,28
	outputchar ' ',93h,1
	setpos 10,46
	outputchar ' ',93h,1
	mov	ah, 07h
	int	21h
	mov	ah, 0
	mov	al, 03h
	int	10h
	mov	ah, 4ch
	int	21h
	ret
exit endp
; ===========================================================================
code ends

     end start
