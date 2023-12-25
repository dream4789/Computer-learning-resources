;��notepad++�鿴���ĵ��ȽϺ�~~
.model small				;small������ֻ����һ������κ�һ�����ݶ�
.stack 200h					;��ջ���� stack��Ĭ�ϴ�С 1024 �ֽڣ������� 200h �ֽ�
.data						;���ݶ���_data

student struc			;ѧ�������ݽṹ,32 �ֽڣ�2^5�����ڼ����ַ
    xname db 14 dup('$')
    class db 14 dup('$')
    num   dw 0
    score dw 0			;Ϊ�˱���1λС������10��ֵ����
student ends
	
    stu_size equ 32			;32=2^5
   
  	stu_db student 100 dup(<'x','y',6,500>)		;����100 ��ѧ���Ŀռ�Ľṹ��stu_db
  	stu_num db 0								;�ѱ����ѧ������
  	stu_seq db 100 dup('$')						;������Ϣ����������������н��У�������������������

    welcome db '-----Student Information Mannagement System-----',0dh,0ah ;��ӡ�˵�
        		db '------------------------------------------------',0dh,0ah;
        		db '0. Add Information.',0dh,0ah				;0. ¼��ѧ���ɼ���ʮ������ʽ)
        		db '------------------------------------------------',0dh,0ah;
        		db '1. Sort by the numbers of students.',0dh,0ah;1.��ѧ��������ʾ
        		db '------------------------------------------------',0dh,0ah;
        		db '2. Sort by the scores of students.',0dh,0ah	;2.���ɼ�������ʾ
        		db '------------------------------------------------',0dh,0ah;
        		db '3. Statistic the Average score',0dh,0ah		;3.ͳ��ƽ���ɼ�
        		db '------------------------------------------------',0dh,0ah;
        		db '4. Show Statistics of each kind.',0dh,0ah	;4.ͳ�Ƹ�����������
        		db '------------------------------------------------',0dh,0ah;
        		db '5. Exit.',0dh,0ah							;5.�˳�
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
    buflen 	db 	100									;���뻺������С 100
    aclen		db 	? 									;ʵ�����볤��
    buf    	db	100 dup(0),'$'						;ʵ�ʻ�����
    bufrear	equ offset buf+100						;������β
    
        ns6 db 0				;ͳ�Ƹ�����������
        n67 db 0
        n78 db 0
        n89 db 0
        n91 db 0
        
        ms6 db '(Not Pass)0 ~ 60:','$'	;��ʾ������������
        m67 db '(Pass)   60 ~ 70:','$'
        m78 db '(Normal) 70 ~ 80:','$'
        m89 db '(Good)   80 ~ 90:','$'
        m91 db '(Great) 90 ~ 100:','$'

    .CODE					;�������_text
START:

ps macro str 			;��ӡ�ַ�����Ҫ����'$'��β
    push ax
    push dx
  	lea dx,str
  	mov ah,9
  	int 21h
  	
  	pop dx	
  	pop ax
endm

pc macro ch				;��ӡ�ַ�
    push ax
    push dx
  	mov dl,ch
  	mov ah,2
  	int 21h
  	pop dx
  	pop ax
endm

endl macro 				;��ӡ'\n'
  	pc 0dh
  	pc 0ah
endm

scs macro 				    ;�Ӽ��������ַ�����������buf�У�����aclen
  	lea dx,buflen
  	mov ah,10
  	int 21h
endm

scc macro 				    ;�Ӽ��������ַ���������al
  	mov ah,1
  	int 21h
endm

memcpy macro dest,src,len   ;������ڴ濽��
	push ax
  	push cx
  	push si
  	push di
  	mov ax,ds
  	mov es,ax 				;������diҪ�õ����Ӷ�
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

;ʹbxָ����Ϊax��ѧ����Ԫ
;�Ĵ�����ax,bx,cx
GET_STU macro
	push ax
	push cx
	lea bx,stu_db
	mov cl,5			
	shl ax,cl			;?????????
	add bx,ax 			;bxָ�����ѧ���Ĵ洢��Ԫ
	pop cx
	pop ax
endm
	
	mov ax,@data
	mov ds,ax
WELC:					;����ps������ӡwelcome���ݶ�
	endl
	ps welcome
	pc ':'
	
	;����ѡ��
	scc 				;ascii�뱣����al
	endl
	endl
	mov ah,0
	mov bx,ax
	sub bx,'0'			;?????????
	cmp bx,5
	jbe CASE0TO5		;bx�Ĵ���������5��ת�Ƶ�CASE0T05
	jmp WELC
CASE0TO5:
	shl bx,1			;?????????
	jmp table[bx] 		;��ַѰַ
CASE0: 					;¼��ѧ���ɼ���ʮ������ʽ��
	call  ins_stu
	jmp WELC
CASE1: 					;��ѧ��������ʾ
	call num_sort
	call print_seq
	jmp WELC
CASE2: 					;���ɼ�������ʾ
	call score_sort
	call print_seq
	jmp WELC
CASE3: 					;ͳ��ƽ���ɼ�
	call get_average
	jmp WELC
CASE4: 					;ͳ�Ƹ�����������
	call get_sat
	jmp WELC
CASE5:
	mov ah,4ch      	;����
	int 21h
	
	

;ins_stu:����ѧ����Ϣ
;��ڣ�stu_num����ѧ�������������¿հױ��
;���ڣ�stu_db
;�洢��Ԫ��stu_db,stu_num
ins_stu proc near
  	push ax
  	push bx
  	push cx
  	push dx
  	
  	mov al,stu_num
  	mov ah,0
  	;ȷ������ڵڼ���λ��
  	lea bx,stu_db
  	mov cl,5
  	shl ax,cl
  	add bx,ax 			;bxָ��հ׵�Ԫ
input_name:
  	ps  m_str_l			;m_str_l db 0dh,0ah,'(Length < 14 bytes) ','$'
  	ps  msg1			;msg1 db 'name:','$'
  	scs
  	cmp aclen,14
  	jae input_name		;���ڵ�����ת����������name
  	memcpy [bx].xname,buf,aclen;���򿽱�buf����Ϊaclen���ַ�����stu_db�ṹ���µ�xname
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
  	call str2num		;����str2num:���������ַ���ת����ֵ
  	mov [bx].num,ax
  	endl
  
  	ps m_num_l
  	ps msg4
  	scs
  	call score_fmt		;����score_fmt����������ʽ�洢
  	mov [bx].score,ax
  	endl
	
	  inc stu_num 		;����ѧ����¼
  	pop dx
  	pop cx
  	pop bx
  	pop ax
	  ret
ins_stu endp


;pnum:��ʮ������ʽ���һ���޷�����
;��ڣ�ax��Ҫ���������
;���ڣ�
;�洢��Ԫ��
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
	jz OUTLOOPFIN ;axΪ��
	mov dx,0
	mov cx,10
	div cx
	add dl,'0'
	dec bx
	mov byte ptr [bx],dl
	jmp OUTLOOP
OUTLOOPFIN:
	cmp bx,offset bufrear-1 ;���0
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




;pscore:��ʮ������ʽ�����һλС���ķ���
;��ڣ�ax��Ҫ���������
;���ڣ�
;�洢��Ԫ��
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
	cmp bx,offset bufrear-1 ;xҪ�ĳ�0x���Ա�С����ʽ���
	je S0X
	cmp bx,offset bufrear ;��Ҫ�ĳ�00���Ա�С����ʽ���
	jne PRINT_SCORE
S00:
	;==��Ϊ��
	dec bx
	mov BYTE ptr [bx],'0'
S0X:
	dec bx
	mov BYTE ptr [bx],'0'
PRINT_SCORE:
  	mov dx,bx
  	mov bx,bufrear
  	dec bx
  	mov cl,[bx] ;�ݴ�С��
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



;pstu:���ѧ����Ϣ
;��ڣ�ax�洢���
;���ڣ�
;�洢��Ԫ��
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



;str2num�����������ַ���ת����ֵ
;��ڣ�buf
;���ڣ�ax
;�洢��Ԫ��buf��������aclen���������ݳ���
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
	mul  bl ;��ǰ����*10���˷�ָ�������ax
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



;score_fmt����������ʽ�洢
;��ڣ�buf
;���ڣ�ax
;�洢��Ԫ��buf��������aclen���������ݳ���
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
	cmp BYTE ptr [si],'.' ;������ͺ���Ҫ
	jnz MUL_DEX ;����С����
	mov dx,1 ;����С����
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

	;get_average����ƽ���ֲ����
	;��ڣ�stu_db
	;����
	;�洢��Ԫ��stu_db,stu_num
get_average proc near
	push ax
	push bx
	push cx
	push dx
	
	mov cx,0 ;ѧ�����
	mov ax,0 ;�ݴ�ƽ���ɼ���8λ
	mov dx,0 ;�ݴ�ƽ���ɼ���8λ
REPERT:
	cmp cl,stu_num
	jae OUT_PUT ;�ܷ��Ѿ�������
	;�ҵ����Ϊcx��ѧ��
	push ax
	push cx
	mov ax,cx
	GET_STU
	pop cx
	pop ax
	
	add ax,[bx].score ;32λ�ӷ�
	adc dx,0
	inc cl
	jmp REPERT
OUT_PUT:
	mov cl,stu_num
	mov ch,0
	or cl,0 ;����ѧ������������255��
	jnz END_AVE ;û��ѧ�������ܳ�0
	inc cx
END_AVE:
	div cx ;��չΪ16λ�������̱�����ax��
	endl
	call pscore
	endl
	
	pop dx
	pop cx
	pop bx
	pop ax
	ret
get_average endp

	;get_sat:ͳ�Ƹ����������������
	;��ڣ�stu_db
	;����
	;�洢��Ԫ��ns6,n67,n78,n89,n91,stu_db,stu_num
get_sat proc near
	push ax
	push bx
	push cx
	
	mov ns6,0
	mov n67,0
	mov n78,0
	mov n89,0
	mov n91,0
	mov cx,0 ;ѧ�����(����-1)
	
SAT_IN:
	cmp cl,stu_num
	jae SAT_OUT ;�Ѿ�����
	
	;�ҵ����Ϊcx��ѧ��
	push ax
	push cx
	mov ax,cx
	GET_STU
	pop cx
	pop ax
	
	inc cl
	
	mov ax,[bx].score
	cmp ax,600			;��������10��ֵ���д洢����������600�Ƚ�
	jb IS6				;С����ת
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
	
	;print_seq:��������stu_seq����б�
	;���룺stu_seq
	;�����
	;�洢��Ԫ��stu_seq
print_seq proc near
	push ax
	push bx
	;stu_seq�����˱�����У���'$'����
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

	;num_sort:��ѧ������
	;���룺stu_seq
	;�����stu_seq
	;�洢��Ԫ��
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
	;stu_seq�����˰�����˳������У���'$'����

	cmp stu_num,1 ;ѧ����С�ڵ���1��û��Ҫ����
	jle NON_NUM

	mov cl,stu_num ;ѭ���������ڴ�������ֱ�Ӽ�
	dec cl
	mov ch,0
LOOP1:
	mov di,cx ;�ݴ���ѭ��cx
	lea bx,stu_seq ;ָ���һ�����
LOOP2:
	mov al,BYTE ptr [bx]
	mov ah,0
	
	push bx
GET_STU
	mov dx,[bx].num ;dxǰһ�����кŶ�Ӧ��ѧ��
	pop bx

	mov al,BYTE ptr [bx+1]   
	push bx
	GET_STU
	cmp dx,[bx].num ;[bx].num��һ�����кŶ�Ӧ��ѧ��
	pop bx
jae CONTI
	mov al,BYTE ptr [bx] ;С���򽻻��������к�
	;call pnum
	;endl
	xchg al,BYTE ptr [bx+1]
	;call pnum
	;endl
	mov BYTE ptr [bx],al
CONTI:
	inc bx ;��һ�����к�
	loop LOOP2
	mov cx,di ;�ָ���ѭ��
	loop LOOP1
	
NON_NUM:
	pop dx
	pop bx
	ret
num_sort endp

	;score_sort:���ɼ�����
	;���룺stu_seq
	;�����stu_seq
	;�洢��Ԫ��
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
	;stu_seq�����˰�����˳������У���'$'����
	
	cmp stu_num,1 ;ѧ����С�ڵ���1��û��Ҫ����
	jle NON_SCORE
	mov cl,stu_num ;ѭ���������ڴ�������ֱ�Ӽ�
	dec cl
	mov ch,0
SLOOP1:
	mov di,cx ;�ݴ���ѭ��cx
	lea bx,stu_seq ;ָ���һ�����
SLOOP2:
	mov al,BYTE ptr [bx]
	mov ah,0
	
	push bx
	GET_STU
	mov dx,[bx].score ;dxǰһ�����кŶ�Ӧ��ѧ��
	pop bx
	
	mov al,BYTE ptr [bx+1]
	push bx
	GET_STU
	cmp dx,[bx].score ;[bx].num��һ�����кŶ�Ӧ��ѧ��
	pop bx
	
	jae SCONTI
	mov al,BYTE ptr [bx] ;С���򽻻��������к�
	;call pnum
	;endl
	xchg al,BYTE ptr [bx+1]
	;call pnum
	;endl
	mov BYTE ptr [bx],al
SCONTI:
	inc bx ;��һ�����к�
	loop SLOOP2
	mov cx,di ;�ָ���ѭ��
	loop SLOOP1
NON_SCORE:
	pop dx
	pop bx
	ret
	score_sort endp
END START