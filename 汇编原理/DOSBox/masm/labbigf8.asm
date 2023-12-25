; �ɼ�ͳ�Ƴ���
; ���룺89 32 35 21 34 12

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
    mov ds,ax               ;ds���ݶμĴ���
    
    mov ax,stack
    mov ss,ax               ;ss�μĴ���
    
    mov dx,offset string1
    mov ah,09h
    int 21h
        
    ; bx,cx,si,di ����
    xor bx,bx
    xor cx,cx
    xor si,si
    xor di,di
    ret

;==========================input==========================
input:
  	mov ah,1    ; ����һ���ַ���AL��ascll��洢��ax=0100 -> ����2 -> ax=0132
  	int 21h
   
  	cmp al,0dh  ; ����ǡ��س��� ��ת
  	jz  over
   
  	cmp al,20h  ; ����ǡ��ո� ��ת�����ݴ���score[si]�У�bx����
  	jz  save
   
  	sub al,30h  ; �����֣�ascll���30h   -> ax=0102
  	mov cl,4    ;                        -> cx=0004
  	shl bx,cl   ; BX���ƶ�����4λ(BX*16) -> bx=0000
  	add bl,al   ;                        -> bx=0002
  	jmp input

save:
  	mov score[si],bx ; ���� score ��
  	add si,2         ; ָ��+2
  	inc di
  	xor bx,bx        ; bx ����
  	jmp input

over:
    mov score[si],bx 
    inc di
    
    mov dl,0ah
    mov ah,02h  ; ���DL����ַ�
    int 21h
    
    mov cx,di
    dec cx                 
    xor bx,bx 
    ret
;===========================sort=========================
sort:                           ;bx=0����ð������,bxΪҪ�ı����һλ������
  	mov si,2 
  	mov dx,cx

cmp2:
  	mov ax,score[bx]
  	cmp ax,score[bx+si]
  	jnc cmp3                    ;���ڻ����ʱת
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
  	sub si,si                    ;si����
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
    jl  NPass                   ;�з��ţ�jlС����ת
    jge Pass                    ;�з��ţ�jgl���ڵ�����ת
    
avg1:                           ;��λ��һ
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
output:                         ;si=0,diΪ����ĸ���
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
  	int 21h                     ;��ʾstring4
  	mov bx,score[si-2] 
  	call    outputh1            ;���score�����һ����
  	call    hou                 ;���ӷ��
  	call    line_feed           ;�س�����
  	call    hang                ;���+---------------+---------+
  	 
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
  	;---------10 to 16----------avg��������ֵ���ܺͣ���10���Ʊ��棬����������16���Ƽ��㣬
    mov bx,avg                  ;��λ
    mov ah,0
    mov al,bl
    and al,0fh                  ;����al����λ(��λ)��ֵ
    mov avg2,ax
    
    mov al,bl                   
    mov cl,4                    ;ʮλ
    shr al,cl                 
    mov cl,10
    mul cl                      ;ax=al*cl 
    mov dx,0
    add avg2,ax                 
    
    mov al,bh                   ;��λ
    and al,0fh                  ;����ah����λ(��λ)��ֵ
    mov cx,100                  ;ͬ��
    mul cx
    mov dx,0
    add avg2,ax 
    ;----------average-----------
    mov cx,num
    mov ax,avg2
    cwd                         
    div cx                      ;�̷���ax��
    ;-------16 to 10-----------�����ˣ��ͻָ�10���Ʊ��棬�����Ժ����          ;
    mov bh,0
    mov cl,10
    div cl
    mov bl,ah                   ;����(��λ)��bl
    cmp al,0h                   
    jz  z
    cbw
    div cl
    mov dl,ah                   ;����(ʮλ)��dl
    mov cl,4
    shl dl,cl
    add bl,dl                   ;��λ��ʮλ����һ��,
    cmp al,0h
    jz  z
    mov cl,10
    cbw
    div cl
    mov bh,ah                   ;����λ����bhǰ
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
;--------------------���-------------------	
outputh1:
    mov ch,1                ;�����ж�ǰ���Ƿ�ȫΪ0
  	mov dl,bh
  	mov cl,4 
  	shr dl,cl               ;ǧλ��
  	cmp dl,0                ;dlΪ�㣬�����
  	jz  out01
  	mov ch,0
  	add dl,30h
  	mov ah,02h
  	int 21h
  	jmp outputh2            ;Ϊ������out01
out01:                      
  	mov dx,offset kong
  	mov ah,09h
  	int 21h
outputh2: 
  	mov dl,bh 
  	and dl,0fh              ;��λ
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
  	shr dl,cl               ;ʮλ
  	cmp ch,0
  	jz  outputl11           ;ͬ��
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
  	and dl,0fh              ;��λ
  	add dl,30h
  	mov ah,02h
  	int 21h
  	ret
line_feed: ;--------------����-----------
    mov dl,0ah
  	mov ah,02h
  	int 21h
  	mov	dl,0dh
    mov	ah,02h
    int	21h
    ret
hang:                       ;���|----------------+----------
    mov dx,offset string8
  	mov ah,09h
  	int 21h
  	call line_feed 
  	ret
hou:                       ;��ʾ      |
    mov dx,offset string9
  	mov ah,09h
  	int 21h
  	ret
code 	ends
	  end	start
