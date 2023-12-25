STACK SEGMENT PARA STACK 'stack'
    DB 1024 DUP(0)
STACK ENDS

data segment
    but   db 0DH, 0AH, 'the result   $'
    
    but1   db 0DH, 0AH, '1 $'
    but2   db 0DH, 0AH, '2 $'
    but3   db 0DH, 0AH, '3 $'
    but4   db ' $'
    
    grade dw 46,33,84,90,73,88,99,63,100,55
    
    grade50  db 0DH, 0AH, '<60   points: the result  $'
    grade60  db 0DH, 0AH, '60~69 points: the result  $'
    grade70  db 0DH, 0AH, '70~79 points: the result  $'
    grade80  db 0DH, 0AH, '80~89 points: the result  $'
    grade90  db 0DH, 0AH, '90~99 points: the result  $'
    grade100 db 0DH, 0AH, '=100  points: the result  $'
    
    s      db 0
    ;s7    db 0
    ;s8    db 0
    ;s9    db 0
    ;s10   db 0
data ends

code segment
    assume cs:code, ds:data
start:
    ;push ds
    ;sub  ax,ax
    ;push ax
    
    mov  ax,data
    mov  ds,ax
    
    mov  cx,10   ; ѭ��10��
    call count   ; ����
    
    ;call disp    ; ��ʾ
    call disp1   ; ��ʾ1
    
    ;mov  AH,1    ; �����ַ�����Ϊascii��
    ;int  21h
    ;ret
    
    mov AH,4ch
    int 21h



; ͳ��ÿ���ֶε�����
count proc near
    mov si,0         ;si=0000
next:
    ;mov  DX,OFFSET but1  ;(but2 0010)
    ;mov  ah,9  ;����ַ�����DX=�ַ����׵�ַ��
    ;int  21h
    
    mov ax,grade[si] ;[si+0010] -> ax=004c
    mov bl,10        ; -> bl=0a
    div bl     ; �޷����ֽڳ���:AX �� BL��AL�̣�AH������-> ax=0607
    mov bl,al  ; bl = 07
    mov bh,0   ; bh = 00
    ;sub bx,5   ; bx = 0002  70~79
    ;cmp bx,0006H   ; >60
    cmp bx,6
    jnb  next1  ; >=
    

    
    inc  s[0]  ; ����60�ֵģ�+1
    add  si,2  ; Ϊ 52�� ��׼��
    
    mov  DX,OFFSET but2  ;(but2 0014)
    mov  ah,9  ;����ַ�����DX=�ַ����׵�ַ��
    int  21h
        
    mov  dl,bl
    add  dl,30h
    mov  AH,2  ;����ַ���DL ascii ת �ַ���
    int  21h
    
    mov  DX,OFFSET but4  ;(but2 0018)
    mov  ah,9  ;����ַ�����DX=�ַ����׵�ַ��
    int  21h
    
    mov  dl,s[0]
    add  dl,30h
    mov  AH,2  ;����ַ���DL ascii ת �ַ���
    int  21h
    
    loop next
    ret
    
next1:

    
    inc  s[bx]
    add  si,2  ; Ϊ 52�� ��׼��
    
    mov  DX,OFFSET but3  ;(but2 0018)
    mov  ah,9  ;����ַ�����DX=�ַ����׵�ַ��
    int  21h
    
    mov  dl,bl
    add  dl,30h
    mov  AH,2  ;����ַ���DL ascii ת �ַ���
    int  21h
    
    mov  DX,OFFSET but4  ;(but2 0018)
    mov  ah,9  ;����ַ�����DX=�ַ����׵�ַ��
    int  21h
    
    mov  dl,s[bx]
    add  dl,30h
    mov  AH,2  ;����ַ���DL ascii ת �ַ���
    int  21h
    
    
    
    loop next
    
    ret
count endp


; ���ÿ���ֶε�����
disp proc near
    lea si,s
    ;mov si,0
    mov cx,5

loop1:
    mov  DX,OFFSET but
    mov  ah,9  ;����ַ�����DX=�ַ����׵�ַ��
    int  21h
    
    mov  dl,[si]
    add  dl,30h
    
    mov  AH,2  ;����ַ���DL ascii ת �ַ���
    int  21h
    
    inc  si
    
    loop loop1
    
    ret
disp endp


disp1 proc near
    lea  si,s
    
    mov  DX,OFFSET grade50
    ;mov  ah,9
    ;int  21h
    call print_str
    
    add  si,5

    mov  DX,OFFSET grade60
    ;mov  ah,9
    ;int  21h
    call print_str
    
    mov  DX,OFFSET grade70
    ;mov  ah,9
    ;int  21h
    call print_str
    
    mov  DX,OFFSET grade80
    ;mov  ah,9
    ;int  21h
    call print_str
    
    mov  DX,OFFSET grade90
    ;mov  ah,9
    ;int  21h
    call print_str
    
    mov  DX,OFFSET grade100
    ;mov  ah,9
    ;int  21h
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