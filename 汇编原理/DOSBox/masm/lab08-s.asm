STACK SEGMENT PARA STACK 'stack'
    DB 1024 DUP(0)
STACK ENDS
data segment    
    grade    dw 46,33,84,90,73,88,99,63,100,55
    grade50  db 0DH, 0AH, '<60   points: the result  $'
    grade60  db 0DH, 0AH, '60~69 points: the result  $'
    grade70  db 0DH, 0AH, '70~79 points: the result  $'
    grade80  db 0DH, 0AH, '80~89 points: the result  $'
    grade90  db 0DH, 0AH, '90~99 points: the result  $'
    grade100 db 0DH, 0AH, '=100  points: the result  $'
    s        db 0
data ends

code segment
    assume cs:code, ds:data
start:
    mov  ax,data
    mov  ds,ax
    mov  cx,10   ; ѭ��10��
    call count   ; ����
    call disp1   ; ��ʾ1
    mov  AH,4ch
    int  21h

; ͳ��ÿ���ֶε�����
count proc near
    mov si,0
next:
    mov ax,grade[si]
    mov bl,10
    div bl
    mov bl,al
    mov bh,0
    cmp bx,6
    jnb next1  ; >=
    
    inc  s[0]   
    add  si,2  ; Ϊ 52�� ��׼��    
    loop next
    ret
    
next1:
    inc  s[bx]
    add  si,2  ; Ϊ 52�� ��׼��
    loop next
    ret
count endp

; ���ÿ���ֶε�����
disp1 proc near
    lea  si,s

    mov  DX,OFFSET grade50
    call print_str
    
    add  si,5

    mov  DX,OFFSET grade60
    call print_str
    
    mov  DX,OFFSET grade70
    call print_str
    
    mov  DX,OFFSET grade80
    call print_str
    
    mov  DX,OFFSET grade90
    call print_str
    
    mov  DX,OFFSET grade100
    call print_str

    ret
disp1 endp

print_str proc near
    mov  ah,9
    int  21h
    mov  dl,[si]
    add  dl,30h
    mov  AH,2  ;����ַ���DL ascii ת �ַ���
    int  21h
    
    add  si,1
    ret
print_str endp

code ends
    end start
