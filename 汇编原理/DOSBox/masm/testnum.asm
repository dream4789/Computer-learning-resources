DATAS SEGMENT
    CRLF    db 0AH, 0DH                     ,"$"  ;�س�����
    string  db "The original value was:"    ,"$"  ;ԭ����ֵ�����ʾ
    string1 db "The binary form is:"        ,"$"  ;�����������ʾ
    string2 db "The octal number system is:","$"  ;�˽��������ʾ
    string3 db "The hexadecimal form is:"   ,"$"  ;ʮ�����������ʾ
DATAS ENDS
 
STACKS SEGMENT stack
    ;�˴������ջ�δ���
STACKS ENDS
 
CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
  
  	;ԭ���з�������ʽ�����
  	lea dx,string    ;ԭ�����ݵ������ʾ
  	mov ah,9
  	int 21h
   
    mov AX,123	
  	mov ax,-123
  	call symoutput
  	
  	lea dx,crlf
  	mov ah,9
  	int 21h
  	
  	;��������ʽ�����
  	lea dx,string1;�����Ƶ������ʾ                                       
    mov ah,9							 
    int 21h
	
  	mov ax,-123
  	call binaryoutput
  	
  	lea dx,crlf
  	mov ah,9
  	int 21h
  	
  	;�˽�����ʽ�����
  	lea dx,string2;�˽��Ƶ������ʾ
  	mov ah,9
  	int 21h
   
  	mov ax,-123
  	call octaloutput
  	
  	lea dx,crlf
  	mov ah,9
  	int 21h
  	
  	;ʮ��������ʽ�����
  	lea dx,string3;ʮ�����Ƶ������ʾ
  	mov ah,9
  	int 21h
  	
  	mov ax,-123
  	call hexadecimaloutput
  	
  	lea dx,crlf
  	mov ah,9
  	int 21h	
	
    MOV AH,4CH
    INT 21H  


  
;��������ʽ�����,��ڲ���Ϊax
binaryoutput proc
  	push bx     ;������ջ��������ֵ
  	push dx	
   
  	mov dh,0    ;���ڼ������ܹ�16��
	
binaryagain:	
	  cmp dh,16
		je binaryover  ;������������ﺯ��ĩ��
  	rol ax,1       ;�ƶ�һλ
  	mov bx,ax      ;��ֵ����
  	and ax,0001h   ;��������һλ
  	mov dl,al      ;�������
  	add dl,48
  	mov ah,2
  	int 21h
  	inc dh         ;������һ
  	mov ax,bx      ;��ֵ�ָ�
		jmp binaryagain;����һ��		
	
binaryover:
  	pop dx         ;���ݳ�ջ����ֵ��ԭ
  	pop bx
  	ret

binaryoutput endp


;�˽�����ʽ���������ڲ���Ϊax
octaloutput proc
  	push bx;������ջ����ֵ����
  	push cx
  	push dx
  	
  	;���һλ�����������
  	rol ax,1;�ƶ�һλ
  	mov bx,ax;������ֵ
  	and al,01h;�������һλ����
  	mov dl,al;׼�����
  	add dl,48
  	mov ah,2
  	int 21h	
  	mov ax,bx;�ָ���ֵ
  	
  	;�Ժ�����15λ���д���15��3����5
  	mov dh,0;����5�Σ��������һλ��������

octalagain:
	  cmp dh,5
		je octalover;ѭ��������������β����
		inc dh;������һ
  	mov cl,3;��Ϊ��λλ��
  	rol ax,cl;�ƶ������λ
  	mov bx,ax;����ax��ֵ��ֹ�޸�
  	and al,07h;�������λ����
  	mov dl,al;׼�����
  	add dl,48
  	mov ah,2
  	int 21h
  	mov ax,bx;�ָ�ax�ı�����ֵ
		jmp octalagain;loop
 
octalover:	
  	pop dx;���ݳ�ջ����ֵ��ԭ
  	pop cx
  	pop bx
  	ret

octaloutput endp


;ʮ��������ʽ�����,��ڲ���Ϊax
hexadecimaloutput proc
  	push bx;������ջ����ֵ����
  	push cx
  	push dx
  	
  	mov dh,0;���ڼ������ܹ�4��
	
hexadecimalagain:
	  cmp dh,4
		je hexadecimalover;ѭ��������������β����
		inc dh;������һ
  	mov cl,4
  	rol ax,cl
  	mov cx,ax;��ֵ����
  	and ax,0fh;���ݰ������λ
  	mov dl,al
  	cmp dl,9;������Ҫ������ֻ�����ĸ
		ja alphabet;��Ϊ��ĸ���
  	add dl,48;��Ϊ������ʽ�����
  	mov ah,2
  	int 21h	
  	mov ax,cx;���ݻָ�
		jmp hexadecimalagain
		
alphabet:;��Ϊ��ĸ��ʽ�����
  	add dl,55
  	mov ah,2
  	int 21h
  	mov ax,cx;���ݻָ�
		jmp hexadecimalagain
 
hexadecimalover:		
  	pop dx;���ݳ�ջ����ֵ����
  	pop cx
  	pop bx
  	ret

hexadecimaloutput endp
 
    
;�з����������,��ڲ���Ϊax
symoutput proc
  	push bx;��ջ����
  	push dx
  	
  	mov bx,ax;�������ݷ�ֹ�����޸�,��ֱ�ӵ��ú���
  	
  	cmp ax,0;�Ƚ�ax�����ֵ�����
		js negative;���������
		jmp positive;���������
		
negative:
  	mov dl,'-';�������
  	mov ah,2
  	int 21h
  	
  	neg bx;����
  	call output
		jmp symoutputover 
	
positive:
	  call output
	
symoutputover:
  	pop dx;��ջ��ԭ
  	pop bx
  	ret

symoutput endp
 
    
;��λ�����������ڲ���Ϊbx
output proc
  	push ax      ;������ջ��
  	push cx
  	push dx
  	
  	;��ʼ������
  	mov ax,bx    ;���ݷ���׼������
  	mov cl,10    ;��Ϊ����
  	mov ch,0     ;���ڼ������ں�����ջ���
	
divagain:        ;�������ְ��벿��
	  cmp ax,0     ;�ж��Ƿ��Ѿ�����
		je divover
  	inc ch       ;��������1
  	div cl
  	push ax      ;��ջ����ȡ��ʱ��ȡ��ah����,�洢��������λ���ȣ�
  	mov ah,0     ;����ax
		jmp divagain ;�ٴγ�����������
		
divover:       ;��ջ�������
	  cmp ch,0   ;�ж������Ƿ��Ѿ�����
		je outputover
  	pop ax     ;ȡ��ah����
  	mov dl,ah  ;�������
  	add dl,48
  	mov ah,2
  	int 21h
  	dec ch
		jmp divover 
		
outputover:     ;��β����
  	pop dx
  	pop cx
  	pop ax      ;���ݳ�ջ��
  	ret
output endp


CODES ENDS
    END START
 
 