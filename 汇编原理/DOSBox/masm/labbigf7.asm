;------------------------------------------------
;---     ������ĸcʵ�ֻ�Բ��������ѡ��ģʽ    ---
;---  1������Բ����뾶 2��������������Ϊֱ�� ---
;------------------------------------------------
data segment
    shuc db 'please input C,I will draw a yuan for you: $'
    xuan db 'select moshi input 1 or 2: $'
    hua1 db 'input yuanxin and banjing(Must like:310,220 200): $'
    hua2 db 'input two point as zhijing(Must like:120,170 500,340): $'
    ero  db 'input error! please restart! $'
    zifu db 20 dup(0) ;�˶�������ʱ��������ַ�
    shu  db 20 dup(0) ;�ٴδ���������ֵ�ASCII��ת����Ϊ������
    suan db 24 dup(0) ;������ż���Բ�����в�������ʱ����
data ends

stack segment stack
    stk db 16 dup(0)
stack ends

code segment
    assume cs:code, ds:data, ss:stack
start:
    mov ax,data
    mov ds,ax
    ;mov ax,stack
    ;mov ss,ax
    mov dx,offset shuc ;��ʾ����C����ʾ�ַ�
    call showmsg
        
    call input         ;�����ַ�c�Ĵ���
    mov al,ds:[si]
    and al,11011111b   ;���ڴ�Сд��ʶ�𣬽��ַ�ת���ɴ�д
    cmp al,43h
    jnz showero        ;�������C��ת��ero
        
    mov dx,offset xuan ;��ʾ����1��2�Ļ�Բ��ʽ
    call showmsg
            
    call input
    mov al,ds:[si]     ;�Ƚ�ѡ��Բ�ķ�ʽ
    cmp al,31h
    jz draw1
    cmp al,32h
    jz draw2
    call showero

;-----------------------------------------------------------
showero: ;���������ʾ
    mov dx,offset ero
    mov ah,9h
    int 21h
    mov ax,4c00h
    int 21h


draw1: ;��һ�ֻ�Բ��ʽ��Բ������+�뾶
    mov dx,offset hua1
    call showmsg
    call input
    call zhuanshu
    call moshi
    mov bx,offset shu
    mov ax,ds:[bx]
    mov si,ax
    mov ax,ds:[bx+2]
    mov di,ax
    mov ax,ds:[bx+4]
    call drawyuan
    mov ax,4c00h
    int 21h

draw2: ;�ڶ��л�Բ��ʽ����������Ϊֱ��
    mov dx,offset hua2
    call showmsg
    call input
    call zhuanshu
    call moshi
    mov bx,offset shu
    mov bp,offset zifu
    mov ax,ds:[bx]
    add ax,ds:[bx+4]
    shr ax,1
    mov si,ax ;Բ�ĺ�����
    mov ax,ds:[bx+2]
    add ax,ds:[bx+6]
    shr ax,1
    mov di,ax ;Բ��������
    mov ax,ds:[bx]
    sub ax,ds:[bx+4]
    shr ax,1
    xor dx,dx
    imul ax
    mov word ptr ds:[bp],ax
    mov word ptr ds:[bp+2],dx
    mov ax,ds:[bx+2]
    sub ax,ds:[bx+6]
    shr ax,1
    xor dx,dx
    imul ax
    add ax,word ptr ds:[bp]
    adc dx,word ptr ds:[bp+2]
    mov word ptr ds:[bp+4],ax ;����뾶��ƽ��
    mov word ptr ds:[bp+6],dx
    mov cx,1000h ;�����ҳ��뾶ֵ
    mov bx,0

zhao:
    mov ax,bx
    xor dx,dx
    mul ax
    cmp dx,word ptr ds:[bp+6]
    jnb ok
    cmp ax,word ptr ds:[bp+4]
    jnb ok
    inc bx
    loop zhao
ok:
    mov ax,bx
    call drawyuan
    mov ax,4c00h
    int 21h

;---------------------------------------------------------
input: ;ʵ�ּ��������ַ� 
    mov bx,0
    mov cx,20
re: mov ah,1h ;DOS�ж� ���̼�����ԣ�alΪ�ַ�
    int 21h
    cmp al,0dh ;0dhΪ�س���ASCII��
    jz scx
    mov si,offset zifu
    mov [bx][si],al ;��������ַ��ŵ�zifu��
    inc bx
    loop re
    ret


;---------------------------------------------------------
scx: ;������תʱ��cx����
    mov cx,0
    ret
;----------------------------------------------------------
showmsg: ;������ʾ��ʾ�ַ�
    mov ah,9h
    int 21h
    ret
    
;-----------------------------------------------------------
moshi: ;��Ļ��ʾģʽ
    mov al,12h
    mov ah,0
    int 10h
    ret
;----------------------------------------------------------
zhuanshu: ;�������ascII��תΪ����
    mov bx,offset zifu
    mov bp,offset shu
    mov cx,16
    mov si,0
    mov di,0
lei: ;�˶δ���Ƚφ��£����ǴﵽĿ�ľ��У�
    mov al,ds:[bx][si]
    cmp al,0
    jz scx
    sub al,30h
    mov dl,100
    mul dl
    mov word ptr ds:[bp][di],ax
    mov ax,0
    mov al,ds:[bx][si+1]
    sub al,30h
    mov dl,10
    mul dl
    add ax,word ptr ds:[bp][di]
    mov word ptr ds:[bp][di],ax
    mov ax,0
    mov al,ds:[bx][si+2]
    sub al,30h
    add ax,word ptr ds:[bp][di]
    mov word ptr ds:[bp][di],ax
    add si,4
    add di,2
    loop lei
    ret
;-----------------------------------------------------------
drawyuan: ;������� ax�뾶��si��diԲ�ĵĺ�������
    mov bx,offset suan
    mov word ptr ds:[bx],si ;����Բ�ĺ�����
    mov word ptr ds:[bx+2],di ;����Բ��������
    sub si,ax
    mov word ptr ds:[bx+4],si ;������ʼ�������
    sub di,ax
    mov word ptr ds:[bx+6],di ;������ʼ��������
    shl ax,1 ;ֱ��
    mov cx,ax
    mov word ptr ds:[bx+10],ax ;����ֱ��
    shr ax,1
    xor dx,dx
    mul ax
    mov word ptr ds:[bx+12],ax
    mov word ptr ds:[bx+14],dx ;����뾶��ƽ��
;-----------------��ʱ axֱ����bx������̵�ƫ�Ƶ�ַ��cxδ��
;-----------------dxδ�ã�si��ʼ������꣬di��ʼ��������
hang:
    push cx ;д���ص������зֱ���DX��CX
    mov cx,ds:[bx+10]
    mov dx,di
    mov si,ds:[bx+4] ;ÿ��ѭ��ǰ�Ѻ��������
lie:
    push cx ;��������ͱȽϵ���Ҫѹջ2��
    push dx
    xor dx,dx
    mov cx,si
    mov ax,si
    sub ax,ds:[bx]
    xor dx,dx ;��֮ǰ��������
    imul ax
    mov word ptr ds:[bx+16],ax
    mov word ptr ds:[bx+18],dx
    mov ax,di
    sub ax,ds:[bx+2]
    xor dx,dx
    imul ax
    add ax,ds:[bx+16]
    adc dx,ds:[bx+18]
    mov word ptr ds:[bx+20],ax
    mov word ptr ds:[bx+22],dx
    pop dx
    mov ax,ds:[bx+22]
    cmp ax,ds:[bx+14]
    jne kong
    mov ax,ds:[bx+12]
    sub ax,ds:[bx+20]
    cmp ax,500 ;����һ����������Χ
    ja kong ;������
    ; cmp ax,ds:[bx+20]
    ; jb kong
    ;��ʵ��Բ
    mov ah,0ch
    mov al,5h ;1����2�̣�3ǳ����4�졢�����Ͳ�һ��һ������
    int 10h
kong:
    pop cx
    inc si
    loop lie
    pop cx
    inc di
    loop hang
    ret
;-------------------------------------------------
code ends
    end start