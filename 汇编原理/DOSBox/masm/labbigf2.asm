;ѧ���ɼ�����ϵͳ

DATA SEGMENT

    TIPS0 DB 'Tips:',0DH,0AH,'$'				;������ʾ��Ϣ
    TIPS1 DB '          SEX: 1:male   0:female',0DH,0AH,'$'
    TIPS3 DB 'Please input ID:$'				;��ѯ��ʾ��Ϣ
    TIPS4 DB '  Please enter "r" to return$'
    TIPS5 DB '  Please enter "r" to return,"c" to continue$'
    ID    DB '   ID: $'
    NAM   DB ' NAME: $'
    SEX   DB '  SEX: $'
    SCORE DB 'SCORE: $'
    
    FID   DW ?		;�ļ���
    SEXM  DB 'male     $'
    SEXF  DB 'female   $'
    COUNT_A DB '         9 0 ~ 100: $'		;ͳ����ʾ��Ϣ
    COUNT_B DB '         8 0 ~ 8 9: $'
    COUNT_C DB '         7 0 ~ 7 9: $'
    COUNT_D DB '         6 0 ~ 6 9: $'
    COUNT_E DB '         0 0 ~ 5 9: $'
    AB      DB    5 DUP('0')		;ͳ�ƽ��
    
    mess1   DB '       *                 The Student Grade Management System             *',0ah,0dh,'$'
    mess2   DB '       *      this is main menu                                          *',0ah,0dh,'$'
    mess3   DB '       *      insert  (i)                                                *',0ah,0dh,'$' 
    mess4   DB '       *      modify  (m)                                                *',0ah,0dh,'$'
    mess5   DB '       *      delete  (d)                                                *',0ah,0dh,'$'
    mess6   DB '       *      query   (q)                                                *',0ah,0dh,'$'
    mess7   DB '       *      count   (c)                                                *',0ah,0dh,'$'
    mess8   DB '       *      print   (p)                                                *',0ah,0dh,'$'
    mess9   DB '       *      exit    (e)                                                *',0ah,0dh,'$'  
    mess10  DB '       * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *',0ah,0dh,'$'  
    mess13  DB '       *      list    (l)                                                *',0ah,0dh,'$'
    mess14  DB '       *      please chose(l/i/m/d/q/c/p/e):                             *',0ah,0dh,'$'
    
    ID_LENGTH    EQU 4		;������Ϣ
    NAM_LENGTH   EQU 20
    SEX_LENGTH   EQU 1	  ;�Ա��������λ��
    SCORE_LENGTH EQU 5
    
    STU_LENGTH DW ?		;ÿ��ѧ����Ϣ�ܳ���
    STU_LENGTH_ADD1 DW ?
    NAM_SEX_SCORE_LENGTH DW ?
    
    DEL      DB 30 DUP (' ')	;�����Ϣ��
    DEL_DONE DB '   Delete success !$'
    
    ERR      DB '  Data error,Please input again!$'	;������ʾ��Ϣ
    NOSTU    DB '   Sorry,there is no this studnet!$'
    ERR_NO   DB '  No student information!$'
    ERR_SAME DB '   There is the same ID,please input again!$'
    NEWF     DB 0DH,0AH,0DH,0AH,'    Warning: this operation will empty all your data!',0DH,0AH,0DH,0AH,'    Will you continue? (y:empty,other key:return):$'
    
    
    FPATH DB 'c:\score.txt',0	;���ݿ��ı�
    
    STR   DB 50		;������str
          DB ?
          DB 50 DUP (?)
    STR0  DB 50 DUP (?)	;������str0
    
    ENTER DB '   $'			;�ո�
    TMP   DW 0			    ;�Ƿ�Ϊ�ձ�־��Ϣ
    SC    DB 0			  	;������������ 
    
    BYE DB '                      Thanks for use our program!',0DH,0AH,0DH,0AH,'                               Bye~ Bye~$'
    BY0 DB '                    Writer:                         $'
    BY1 DB '                         07212151206 (Gao      Tian)$'
    BY2 DB '                         07212151207 (Yu Chang Ming)$'
    BY3 DB '                         07212151208 (Yi    Bao  Fa)$'
    BY4 DB '                         07212151209 (Dong  Jun Zai)$'
    BY5 DB '                         07212151210 (Luo      Chun)$'

DATA ENDS


SET_P1  MACRO				    ;�趨���λ��A
    MOV AH,02H
    MOV DH,02
    MOV DL,03
    MOV BH,0
    INT 10H
ENDM

SET_P3 MACRO
     MOV AH,02H         ;�趨����λ��B   
     MOV DH,15               	          
     MOV DL,44
     MOV BH,0           ;��ǰ��ҳ
     INT 10H
ENDM


TAB MACRO				;����
    MOV AH,2
    MOV DL,0DH
    INT 21H
    MOV DL,0AH
    INT 21H
ENDM

CREATEF MACRO FILE_ID,FILE_PATH		;�����ļ���[����]�ļ��š�[����]�ļ�·����
  	MOV AH,3CH
  	MOV CX,00H			;��ͨ�ļ�
  	LEA DX,FILE_PATH
  	INT 21H
  	MOV FILE_ID,AX
ENDM

OPENF MACRO FILE_ID,FILE_PATH		;���ļ���[����]�ļ��š�[����]�ļ�·����
  	MOV AL,2			;��д��ʽ��
  	MOV AH,3DH
  	LEA DX,FILE_PATH
  	INT 21H
  	MOV FILE_ID,AX
ENDM

CLOSEF  MACRO FILE_ID			;�ر��ļ���[����]�ļ��ţ�
  	MOV BX,FILE_ID
  	MOV AH,3EH
  	INT 21H	
ENDM

READF MACRO FILE_ID,TEMP,NUM		;���ļ���[����]�ļ��š�[����]��������[����]�ֽ�����
  	MOV BX,FILE_ID
  	LEA DX,TEMP
  	MOV AX,NUM
  	MOV CX,AX
  	MOV AH,3FH
  	INT 21H
ENDM

WRITEF MACRO FILE_ID,TEMP,NUM		;д�ļ���[����]�ļ��š�[����]��������[����]�ֽ�����
	MOV BX,FILE_ID
	MOV CX,NUM
	LEA DX,TEMP[2]
	MOV AH,40H
	INT 21H
ENDM

MOVEF MACRO FILE_ID,STYPE,HIGEC,LOWD	;�ƶ��ļ�ָ�루[����]�ļ��š�[����]�ƶ���ʽ��[����]ƫ���ֽڣ���λ��[����]ƫ���ֽڣ���λ����
  	MOV BX,FILE_ID
  	MOV AH,42H
  	MOV AL,STYPE			;β+ƫ������ʽ
  	MOV CX,HIGEC			;ƫ���ֽڣ���λ��
  	MOV DX,LOWD			;ƫ���ֽڣ���λ��
  	INT 21H
ENDM


INPUT MACRO BUFFER,LENGTH		;�����ַ�����[����]�ַ�������[����]�ַ������ȣ�
  	MOV AH,10
  	LEA DX,BUFFER
  	INT 21H
  	MOV LENGTH,BUFFER[1]
ENDM

SHOW MACRO BUFFER			;��ʾ�ַ�����[����]�ַ�������
  	MOV AH,9
  	LEA DX,BUFFER
  	INT 21H
ENDM



STAK SEGMENT STACK
  DB 200 DUP (?)
STAK ENDS



CODE SEGMENT
  ASSUME CS:CODE,DS:DATA
SHOW_EXIT PROC NEAR		;��ʾ��r�˳�
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	TAB
	TAB
	SHOW TIPS4
EXIT_1:	MOV AH,7
	INT 21H
	CMP AL,'r'
	JNZ EXIT_1
	POP DX
	POP CX
	POP BX
	POP AX
	RET
SHOW_EXIT ENDP

SHOW_EC PROC NEAR		;ѯ���˳����Ǽ���
  	PUSH AX
  	PUSH BX
  	PUSH CX
  	PUSH DX
  	TAB
  	TAB
  	SHOW TIPS5
EXIT_2:	MOV AH,7
  	INT 21H
  	CMP AL,'r'
  	JZ EXIT_4
  	CMP AL,'c'
  	JNZ EXIT_2
  	CALL INSERT
EXIT_4:	POP DX
  	POP CX
  	POP BX
  	POP AX
  	RET
SHOW_EC ENDP


SHOW_ERR PROC NEAR		;��ʾ������Ϣ�ӳ���
  	PUSH AX
  	PUSH BX
  	PUSH CX
  	PUSH DX
  	TAB
  	TAB
  	SHOW ERR
  	TAB
  	TAB
  	POP DX
  	POP CX
  	POP BX
  	POP AX
  	RET
SHOW_ERR ENDP

RE_TMP PROC NEAR		;�ÿո��ʼ���������ӳ���
  	PUSH AX
  	PUSH BX
  	PUSH CX
  	PUSH DX
  	MOV CX,50
  	MOV BX,1
RE:	INC BX
  	MOV STR[BX],' '
  	LOOP RE
  	POP DX
  	POP CX
  	POP BX
  	POP AX
  	RET
RE_TMP ENDP


CLEAR  PROC NEAR 		;����
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX                      
    MOV AL,0                         ;�Ϲ�����
    MOV CL,0                         ;�Ϲ��������Ͻǵ��к�Ϊ0
    MOV CH,0                         ;�Ϲ��������Ͻǵ��к�Ϊ0
    MOV DH,24                        ;�Ϲ��������Ͻǵ��к�Ϊ24
    MOV DL,79                        ;�Ϲ��������Ͻǵ��к�Ϊ79
    MOV BH,14                        ;�հ��е�����
    MOV AH,6                         ;��ڲ���
    INT 10H
    SET_P1
    POP DX
    POP CX
    POP BX
    POP AX
    RET
CLEAR  ENDP   

SHOW_STU PROC NEAR		;��ʾѧ����Ϣ�ӳ���
  	PUSH AX
  	PUSH BX
  	PUSH CX
  	PUSH DX
  	
  	SHOW ID			;ID
  	MOV CX,ID_LENGTH
  	MOV BX,-1
SH_ID:	INC BX
  	MOV DL,STR0[BX]
  	MOV AH,2
  	INT 21H
  	LOOP SH_ID
  	
  	SHOW ENTER
  	SHOW NAM		;NAME
  	MOV CX,NAM_LENGTH
  	MOV BX,ID_LENGTH
  	DEC BX
SH_NAME:INC BX
  	MOV DL,STR0[BX]
  	MOV AH,2
  	INT 21H
  	LOOP SH_NAME
  	
  	SHOW ENTER
  	SHOW SEX		;SEX
  	MOV BX,ID_LENGTH
  	ADD BX,NAM_LENGTH
  	MOV DL,STR0[BX]
  	CMP DL,'1'		;  1��ʾmale,  0��ʾfemale
  	JNZ SEX_F
  	SHOW SEXM
  	JMP NN
SEX_F:	SHOW SEXF
		
NN:	SHOW ENTER
  	SHOW SCORE		;SCORE
  	MOV CX,SCORE_LENGTH
  	MOV BX,ID_LENGTH
  	ADD BX,NAM_LENGTH
SH_SCORE:INC BX
  	MOV DL,STR0[BX]
  	MOV AH,2
  	INT 21H
  	LOOP SH_SCORE
  	
  	POP DX
  	POP CX
  	POP BX
  	POP AX
  	RET
SHOW_STU ENDP

PRINT_STU PROC NEAR		;��ӡѧ����Ϣ�ӳ���
  	PUSH AX
  	PUSH BX
  	PUSH CX
  	PUSH DX
  	TAB
  
  	SHOW ID			;ID
  	MOV CX,ID_LENGTH
  	MOV BX,-1
P_ID:	INC BX
  	MOV DL,STR0[BX]
  	MOV AH,5
  	INT 21H
  	LOOP P_ID
  	
  	SHOW ENTER
  	SHOW NAM		;NAME
  	MOV CX,NAM_LENGTH
  	MOV BX,ID_LENGTH
  	DEC BX
P_NAME:	INC BX
  	MOV DL,STR0[BX]
  	MOV AH,5
  	INT 21H
  	LOOP P_NAME
  	
  	SHOW ENTER
  	SHOW SEX		;SEX
  	MOV BX,ID_LENGTH
  	ADD BX,NAM_LENGTH
  	MOV DL,STR0[BX]
  	MOV AH,5
  	INT 21H
		
PNN:	SHOW ENTER
  	SHOW SCORE		;SCORE
  	MOV CX,SCORE_LENGTH
  	MOV BX,ID_LENGTH
  	ADD BX,NAM_LENGTH
P_SCORE:INC BX
  	MOV DL,STR0[BX]
  	MOV AH,5
  	INT 21H
  	LOOP P_SCORE
  	POP DX
  	POP CX
  	POP BX
  	POP AX
  	RET
PRINT_STU ENDP

;====================���²���(insert)�ӳ���================
INSERT PROC NEAR
  	PUSH AX
  	PUSH BX
  	PUSH CX
  	PUSH DX	
  	TAB
          CALL CLEAR              ;����	
  	SHOW TIPS0		;��ʾ��ʾ��Ϣ
  	SHOW TIPS1
  	TAB
  	TAB
  					
  	OPENF FID,FPATH		;���ļ�
		
IN_ID:	SHOW ID			; ѧ��		
  	INPUT STR,BL		;�򻺳�������ID
  	CMP BL,ID_LENGTH	;��ID�Ƿ�Ϸ�
  	JZ L1
  	JNZ ERR_ID
ERR_SA: 			;������
  	TAB
  	TAB
  	SHOW ERR_SAME
  	TAB
  	TAB
  	JMP IN_ID
ERR_ID:
  	TAB
  	TAB
  	CALL SHOW_ERR
  	TAB
  	TAB
  	JMP IN_ID
L1:					;ID�ж�ֻ��Ϊ����
  	MOV CX,ID_LENGTH
  	LEA SI,STR+2
LN:	MOV AL,BYTE PTR[SI]
  	CMP AL,'0'
  	JB   ERR_ID
  	CMP  AL,'9'
  	JA   ERR_ID 
  	INC SI
  	LOOP LN
	  MOVEF FID,0,0,0			;ָ���Ƶ��ļ���
IA:	
	  MOVEF FID,1,0,5		
	
IB:	READF FID,STR0,STU_LENGTH	;��ȡѧ����Ϣ
    	CMP AX,0			;�ļ��Ƿ����
    	JNZ IL1	
    	JMP IC				;û���ظ�ѧ�ţ����Բ���
IL1:	LEA SI,STR0
    	LEA DI,STR
    	INC DI
    	DEC SI
    	MOV CX,ID_LENGTH	
IL2:	INC SI
    	INC DI
    	MOV AL,BYTE PTR [DI]
    	CMP AL,BYTE PTR [SI]
    	JNZ IA			;������������ȡ��һ��ͬѧ��Ϣ
    	LOOPZ IL2		
    	JMP ERR_SA		;���ظ�ѧ��
	
IC:	MOVEF FID,2,0,5
  	WRITEF FID,STR,ID_LENGTH;���ݺϷ���д������
  	TAB

IN_NAM:	SHOW NAM		;����
  	CALL RE_TMP		;��ʼ��������
  	INPUT STR,BL
  
  	ADD BL,2		;ȥ���س�
  	MOV BH,0		
  	MOV SI,BX
  	MOV STR[SI],' '
  	SUB BL,2
  
  	CMP BL,NAM_LENGTH
  	JNA L2
ERR_NAM:
  	CALL SHOW_ERR
  	JMP IN_NAM
	
L2:	CMP STR[2],' '		;������һ���ַ���Ϊ��
  	JZ ERR_NAM
  	CMP STR[2],'z'
  	JA ERR_NAM
  	CMP STR[2],'A'
  	JB ERR_NAM
  	CMP STR[2],'a'
  	JNB III
  	CMP STR[2],'Z'
  	JA ERR_NAM 	
  	CMP STR[2],'A'
  	JB ERR_NAM
	
III:	
    MOV CX,NAM_LENGTH
	  MOV BX,2		
II0:	
    INC BX
  	DEC CX
  	CMP STR[BX],'z'
  	JA ERR_NAM
  	CMP STR[BX],' '
  	JB ERR_NAM
  	CMP STR[BX],'a'
  	JNB II0
  	CMP STR[BX],'Z'
  	JA ERR_NAM 	
  	CMP STR[BX],'A'
  	JNB II0
  	CMP STR[BX],' '
  	JNZ ERR_NAM	
  	CMP CX,0
  	JNZ II0
  	
  	WRITEF FID,STR,NAM_LENGTH
  	TAB
  	
IN_SEX:	SHOW SEX		;�Ա�
  	CALL RE_TMP
  	INPUT STR,BL
  
  	ADD BL,2		;ȥ���س�
  	MOV BH,0
  	MOV SI,BX
  	MOV STR[SI],' '
  	SUB BL,2
  
  	CMP BL,SEX_LENGTH
  	JNZ ERR_SEX
  	MOV BL,STR[2]
  	CMP BL,'1'
  	JZ L4
    CMP BL,'0'
  	JZ L4
ERR_SEX:
  	CALL SHOW_ERR
  	JMP IN_SEX

	
L4:	WRITEF FID,STR,SEX_LENGTH
	  TAB
IN_SCORE:
  	SHOW SCORE
  	CALL RE_TMP
  	INPUT STR,BL
  	MOV SC,BL		;BL����
  	ADD BL,2		;ȥ���س�
  	MOV BH,0
  	MOV SI,BX
  	MOV STR[SI],' '
  	SUB BL,2
  
  	CMP BL,SCORE_LENGTH		;�������4λ
  	JB L5
ERR_SCORE:
  	CALL SHOW_ERR
  	JMP IN_SCORE
	
L5:	MOV CX,BX	;����ֻ�������ֺ�.
  	MOV BX,2
L6:	CMP STR[BX],'0'
  	JNB L7			;>=0
  	CMP STR[BX],'.'
  	JNZ ERR_SCORE
  	JZ L8
L7:	CMP STR[BX],'9'		;<=9
  	JA ERR_SCORE
  	INC BX
  	LOOP L6
L8:	MOV BL,SC
  	CMP BL,4		;����(0~100),֧��һλС��
  	JNZ L9
  	CMP STR[4],'.'
  	JNZ ERR_SCORE
  	JMP LW
L9:	CMP BL,3
  	JNZ L10
  	CMP STR[3],'.'
  	JZ LW
  	CMP STR[2],'1'
  	JNZ ERR_SCORE
  	CMP STR[3],'0'
  	JNZ ERR_SCORE
  	CMP STR[4],'0'
  	JNZ ERR_SCORE
  	JMP LW
L10:	CMP BL,2
  	JNZ L11
  	CMP STR[2],'.'
  	JZ ERR_SCORE
  	JMP LW
L11:	CMP STR[2],'.'
	  JZ ERR_SCORE
LW:	
  	WRITEF FID,STR,SCORE_LENGTH
  	TAB
  
  	CLOSEF FID			;�ر��ļ�
  	CALL SHOW_EC
  	POP DX
  	POP CX
  	POP BX
  	POP AX
  	RET
INSERT ENDP

;================�����ǲ�ѯ(query)�ӳ���================
QUERY PROC NEAR
  	PUSH AX
  	PUSH BX
  	PUSH CX
  	PUSH DX
    CALL CLEAR
  	OPENF FID,FPATH			;���ļ�
IN_ID1:	SHOW TIPS3			;��ʾ��ʾ��Ϣ		
  	INPUT STR,BL			;�򻺳���STR����ID
  	CMP BL,ID_LENGTH		;��ID�Ƿ�Ϸ�
  	JZ QL1
QERR_ID: 				;������
  	CALL SHOW_ERR
  	JMP IN_ID1

A:	MOVEF FID,1,0,5
	
B:	READF FID,STR0,STU_LENGTH	;��ȡѧ����Ϣ
	  CMP AX,0			;�ļ��Ƿ����
  	JNZ QL1				

QL3:	TAB
    	TAB			;�ļ�������û�и�ѧ����Ϣ
    	SHOW NOSTU
    	JMP C

QL1:	LEA SI,STR0
    	LEA DI,STR
    	INC DI
    	DEC SI
    	MOV CX,ID_LENGTH	
QL2:	INC SI
    	INC DI
    	MOV AL,BYTE PTR [DI]
    	CMP AL,BYTE PTR [SI]
    	JNZ A			;������������ȡ��һ��ͬѧ��Ϣ
    	LOOPZ QL2
    	
    	TAB
    	TAB			;����������ʾ
    	CALL SHOW_STU	
    	JMP C
	
C:	CLOSEF FID
  	TAB
  	TAB
  	SHOW TIPS5		;ѯ���˳����Ǽ���
Q_2:	MOV AH,7
    	INT 21H
    	CMP AL,'r'
    	JZ Q_4
    	CMP AL,'c'
    	JNZ Q_2
    	CALL QUERY
Q_4:	POP DX
    	POP CX
    	POP BX
    	POP AX
    	RET
QUERY ENDP

;==============���������(list)�ӳ���==================

LIST PROC NEAR
  	PUSH AX
  	PUSH BX
  	PUSH CX
  	PUSH DX	
  	CALL CLEAR
  	MOV AX,0
  	MOV TMP,AX			;�Ƿ�Ϊ�ձ�־��0	
  	OPENF FID,FPATH			;���ļ�
  	TAB

D:	MOVEF FID,1,0,5
E:	READF FID,STR0,STU_LENGTH	;��ȡѧ����Ϣ
  	CMP AX,0			;�Ƿ��ļ�β
  	JNZ G						
  	CMP TMP,0			;�ж���û����Ϣ
  	JNZ F
  	TAB
  	TAB
  	TAB
  	SHOW ERR_NO
  	JMP F
				
	
G:	MOV CX,ID_LENGTH		;IDΪ�ղ���ʾ
  	MOV BX,0
  	DEC BX
NULL:	INC BX
    	CMP STR0[BX],' '
    	JZ D
    	LOOP NULL
    	CALL SHOW_STU
    	INC TMP		;����ϢΪ�ձ�־�Լ�
    	TAB
    	JMP D

F:	CLOSEF FID
  	CALL SHOW_EXIT
  	POP DX
  	POP CX
  	POP BX
  	POP AX
  	RET
	
LIST ENDP	

;===============������ɾ��(delete)�ӳ���=====================

DELETE  PROC NEAR
  	PUSH AX
  	PUSH BX
  	PUSH CX
  	PUSH DX
  	CALL CLEAR
  	OPENF FID,FPATH			;���ļ�

D0:	SHOW TIPS3			;��ʾ��ʾ��Ϣ		
  	INPUT STR,BL			;�򻺳���STR����ID
  	CMP BL,ID_LENGTH		;��ID�Ƿ�Ϸ�
  	JZ D2
  	CALL SHOW_ERR
  	JMP D0

D2:	MOVEF FID,1,0,5
  	READF FID,STR0,STU_LENGTH	;��ȡѧ����Ϣ
  	CMP AX,0			;�ļ��Ƿ����
  	JNZ D5
  	TAB
  	TAB				
  	SHOW NOSTU			;�ļ�������û�и�ѧ����Ϣ
  	JMP D15

D5:	LEA SI,STR0
  	LEA DI,STR
  	INC DI
  	DEC SI
  	MOV CX,ID_LENGTH	
D6:	INC SI
  	INC DI
  	MOV AL,BYTE PTR [DI]
  	CMP AL,BYTE PTR [SI]
  	JNZ D2			;������������ȡ��һ��ͬѧ��Ϣ
  	LOOPZ D6
  	
  	TAB			;��ʾ�޸�ǰ��Ϣ
  	TAB
  	CALL SHOW_STU
  	TAB
  	TAB
  	TAB
  	SHOW DEL_DONE
  	MOVEF FID,1,0FFFFH,STU_LENGTH_ADD1
  	WRITEF FID,DEL,STU_LENGTH
  	TAB
	
D15:	TAB
    	TAB
    	TAB
    	CLOSEF FID
    	SHOW TIPS5		;ѯ���˳����Ǽ���
D_2:	MOV AH,7
    	INT 21H
    	CMP AL,'r'
    	JZ D_4
    	CMP AL,'c'
    	JNZ D_2
    	CALL DELETE
D_4:	POP DX
    	POP CX
    	POP BX
    	POP AX
    	RET

DELETE ENDP

;===============�������޸�(modify)�ӳ���=====================

MODIFY PROC NEAR
  	PUSH AX
  	PUSH BX
  	PUSH CX
  	PUSH DX
  	CALL CLEAR
  	OPENF FID,FPATH			;���ļ�

M0:	SHOW TIPS3			;��ʾ��ʾ��Ϣ		
  	INPUT STR,BL			;�򻺳���STR����ID
  	CMP BL,ID_LENGTH		;��ID�Ƿ�Ϸ�
  	JZ M2
  	CALL SHOW_ERR
  	JMP M0

M2:	MOVEF FID,1,0,5
  	READF FID,STR0,STU_LENGTH	;��ȡѧ����Ϣ
  	CMP AX,0			;�ļ��Ƿ����
  	JNZ M5
  	TAB
  	TAB				
  	SHOW NOSTU			;�ļ�������û�и�ѧ����Ϣ
  	JMP M_2

M5:	LEA SI,STR0
  	LEA DI,STR
  	INC DI
  	DEC SI
  	MOV CX,ID_LENGTH	
M6:	INC SI
  	INC DI
  	MOV AL,BYTE PTR [DI]
  	CMP AL,BYTE PTR [SI]
  	JNZ M2			;������������ȡ��һ��ͬѧ��Ϣ
  	LOOPZ M6
  	
  	TAB			;��ʾ�޸�ǰ��Ϣ
  	TAB
  	CALL SHOW_STU
  	TAB
  	TAB

M7:	SHOW NAM		;��ʼ�޸���Ϣ
  	CALL RE_TMP		;��ʼ��������
  	INPUT STR,BL
  
  	ADD BL,2		;ȥ���س�
  	MOV BH,0		
  	MOV SI,BX
  	MOV STR[SI],' '
  	SUB BL,2
  
  	CMP BL,NAM_LENGTH
  	JNA ML2			;��ʼ�޸���Ϣ

ERR_N0:
    	CALL SHOW_ERR		;�����ʾ
    	JMP M7

ML2:	
    	CMP STR[2],' '		;������һ���ַ���Ϊ��
    	JZ ERR_N0
    	CMP STR[2],'z'
    	JA ERR_N0
    	CMP STR[2],'A'
    	JB ERR_N0
    	CMP STR[2],'a'
    	JNB MM0
    	CMP STR[2],'Z'
    	JA ERR_N0 	
    	CMP STR[2],'A'
    	JB ERR_N0
	
MM0:	MOV CX,NAM_LENGTH		;����ֻ������ĸ��ո�
    	MOV BX,2		
MM1:	INC BX
    	DEC CX
    	CMP STR[BX],'z'
    	JA ERR_N0
    	CMP STR[BX],' '
    	JB ERR_N0
    	CMP STR[BX],'a'
    	JNB MM1
    	CMP STR[BX],'Z'
    	JA ERR_N0 	
    	CMP STR[BX],'A'
    	JNB MM1
    	CMP STR[BX],' '
    	JNZ ERR_N0	
    	CMP CX,0
    	JNZ MM1	
    
    	MOVEF FID,1,0FFFFH,NAM_SEX_SCORE_LENGTH		;ָ���Ƶ�������
    	WRITEF FID,STR,NAM_LENGTH
    	TAB
	
M10:	SHOW SEX
    	CALL RE_TMP
    	INPUT STR,BL
    
    	ADD BL,2		;ȥ���س�
    	MOV BH,0
    	MOV SI,BX
    	MOV STR[SI],' '
    	SUB BL,2
    
    	CMP BL,SEX_LENGTH
    	JNZ M11
    	MOV BL,STR[2]
    	CMP BL,'1'
    	JZ M12
      CMP BL,'0'
    	JZ M12
M11:	CALL SHOW_ERR		;������ʾ
	    JMP M10

M12:	WRITEF FID,STR,SEX_LENGTH
	    TAB
M13:
    	SHOW SCORE
    	CALL RE_TMP
    	INPUT STR,BL
    	MOV SC,BL	
    
    	ADD BL,2		;ȥ���س�
    	MOV BH,0
    	MOV SI,BX
    	MOV STR[SI],' '
    	SUB BL,2
    
    	CMP BL,SCORE_LENGTH		;���������ж�
    	JB M14
MEC:	CALL SHOW_ERR
	    JMP M13
M14:	MOV BL,SC
    	MOV BH,0
    	MOV CX,BX	;����ֻ�������ֺ�.
    	MOV BX,2
M15:	CMP STR[BX],'0'
    	JNB M16			;>=0
    	CMP STR[BX],'.'
    	JNZ MEC
    	JZ M17
M16:	CMP STR[BX],'9'		;<=9
    	JA MEC
    	INC BX
    	LOOP M15
    	JMP M17
M21:	JMP MEC			;��ת
M17:	MOV BL,SC
    	CMP BL,4		;����(0~100),֧��һλС��
    	JNZ M18
    	CMP STR[4],'.'
    	JNZ M21
    	JMP MW
M18:	CMP BL,3
    	JNZ M19
    	CMP STR[3],'.'
    	JZ MW
    	CMP STR[2],'1'
    	JNZ M21
    	CMP STR[3],'0'
    	JNZ M21
    	CMP STR[4],'0'
    	JNZ M21
    	JMP MW
M19:	CMP BL,2
    	JNZ M20
    	CMP STR[2],'.'
    	JZ M21
    	JMP MW
M20:	CMP STR[2],'.'
    	JZ M21    
MW:	
	WRITEF FID,STR,SCORE_LENGTH
M_2:	TAB	
    	TAB
    	TAB
    	TAB
    	CLOSEF FID
    	SHOW TIPS5		;ѯ���˳����Ǽ���
    	MOV AH,7
    	INT 21H
    	CMP AL,'r'
    	JZ M_4
    	CMP AL,'c'
    	JNZ M_2
    	CALL MODIFY
M_4:	POP DX
    	POP CX
    	POP BX
    	POP AX
    	RET

MODIFY ENDP

;===========������ͳ�Ƹ�����������(count)�ӳ���==============

COUNT PROC NEAR
    	PUSH AX
    	PUSH BX
    	PUSH CX
    	PUSH DX	
      CALL CLEAR
    	TAB
    	TAB
    	TAB
    	OPENF FID,FPATH			;���ļ�

C_0:	MOV BX,FID
    	MOV AH,42H
    	MOV AL,1			;��ǰ+ƫ������ʽ
    	MOV CX,0			;ƫ���ֽڣ���λ��
    	MOV DX,5			;ƫ���ֽڣ���λ��
    	INT 21H
    	
	
C_1:	READF FID,STR0,STU_LENGTH	;��ȡѧ����Ϣ
    	CMP AX,0			
    	JZ C_8				;���ļ�β�����
    	MOV BX,ID_LENGTH
    	ADD BX,NAM_LENGTH
    	INC BX
    	MOV AX,BX
    	MOV DL,STR0[BX]			;DL��ŷ�����һλ
    	CMP DL,'1'			    ;�����100��ֱ����ʾA
    	JZ C_2
C_2:	INC BX
    	MOV DL,STR0[BX]
    	CMP DL,'0'
    	JZ C_3
C_3:	INC BX
    	MOV DL,STR0[BX]
    	CMP DL,'0'
    	JZ C_A
    
    	MOV BX,AX
    	MOV DL,STR0[BX]
    	MOV CL,'9'
    	CMP DL,CL
    	JGE C_A
    	MOV CL,'8'
    	CMP DL,CL
    	JGE C_B
    	MOV CL,'7'
    	CMP DL,CL
    	JGE C_C
    	MOV CL,'6'
    	CMP DL,CL
    	JGE C_D
    	CMP DL,' '
    	JZ C_0
    	INC [AB]	
    	JMP C_0

C_A:
    	INC [AB+4]	
    	JMP C_0
C_B:
    	INC [AB+3]	
    	JMP C_0
	
C_C:
    	INC [AB+2]
    	JMP C_0

C_D:
    	INC [AB+1]	
    	JMP C_0

C_8:	  CLOSEF FID
	      SHOW COUNT_A    ;��ʾÿ���׶η���������
        MOV DL,[AB+4]
        CMP  DL,'9'
        JA  LA1     
        MOV AH,02H
        INT 21H
        MOV [AB+4],'0'
        TAB
        JMP  NEXT
LA1:    SUB DL,30H
        MOV AL,DL
        MOV BL,10
        MOV AH,0
        DIV  BL
        MOV DL,AL
        MOV BL,AH
        ADD DL,30H
        MOV AH,02H
        INT 21H
        ADD BL,30H
        MOV DL,BL
        MOV AH,02H
        INT 21H
        MOV [AB+4],'0'
        TAB
NEXT:   SHOW COUNT_B
        MOV DL,[AB+3]
        CMP  DL,'9'
        JA  LB1
        MOV AH,02H
        INT 21H
        MOV [AB+3],'0'
        TAB
        JMP  NEXT1
LB1:    SUB DL,30H
        MOV AL,DL
        MOV BL,10
        MOV AH,0
        DIV  BL
        MOV DL,AL
        MOV BL,AH
        ADD DL,30H
        MOV AH,02H
        INT 21H
        ADD BL,30H
        MOV DL,BL
        MOV AH,02H
        INT 21H
        MOV [AB+3],'0'
        TAB
NEXT1:  SHOW COUNT_C
        MOV DL,[AB+2]
        CMP  DL,'9'
        JA  LC1 
        MOV AH,02H
        INT 21H
        MOV [AB+2],'0'
        TAB
        JMP  NEXT2
LC1:    SUB DL,30H
        MOV AL,DL
        MOV BL,10
        MOV AH,0
        DIV  BL
        MOV DL,AL
        MOV BL,AH
        ADD DL,30H
        MOV AH,02H
        INT 21H
        ADD BL,30H
        MOV DL,BL
        MOV AH,02H
        INT 21H
        MOV [AB+2],'0'
        TAB
NEXT2:   SHOW COUNT_D  
        MOV DL,[AB+1]
        CMP  DL,'9'
        JA  LD1        
        MOV AH,02H
        INT 21H
        MOV [AB+1],'0'
        TAB
        JMP  NEXT3
LD1:    SUB DL,30H
        MOV AL,DL
        MOV BL,10
        MOV AH,0
        DIV  BL
        MOV DL,AL
        MOV BL,AH
        ADD DL,30H
        MOV AH,02H
        INT 21H
        ADD BL,30H
        MOV DL,BL
        MOV AH,02H
        INT 21H
        MOV [AB+1],'0'
        TAB
NEXT3:  SHOW COUNT_E      
        MOV DL,[AB]
        CMP  DL,'9'
        JA  LE1     
        MOV AH,02H
        INT 21H
        MOV [AB],'0'
        TAB
        JMP  NEXT4
LE1:    SUB DL,30H
        MOV AL,DL
        MOV BL,10
        MOV AH,0
        DIV  BL
        MOV DL,AL
        MOV BL,AH
        ADD DL,30H
        MOV AH,02H
        INT 21H
        ADD BL,30H
        MOV DL,BL
        MOV AH,02H
        INT 21H
        MOV [AB],'0'
        TAB
	      TAB
NEXT4:  CALL SHOW_EXIT   
      	POP DX
      	POP CX
      	POP BX
      	POP AX
      	RET
COUNT ENDP


;===============�����Ǵ�ӡ(print)�ӳ���======================

PRINT PROC NEAR
  	PUSH AX
  	PUSH BX
  	PUSH CX
  	PUSH DX	
  	CALL CLEAR	
  	OPENF FID,FPATH			;���ļ�
  	TAB
P1:	
    MOVEF FID,1,0,5
		
P2:	
    READF FID,STR0,STU_LENGTH	;��ȡѧ����Ϣ
  	CMP AX,0			
  	JZ P3				;���ļ�β�����
  	CALL PRINT_STU
  	TAB
  	JMP P1

P3:	TAB
  	CLOSEF FID
  	CALL SHOW_EXIT
  	POP DX
  	POP CX
  	POP BX
  	POP AX
  	RET	
PRINT ENDP

;===============�������˳�(exit)�ӳ���=======================

EXIT PROC NEAR
    CALL CLEAR 
  	TAB
  	TAB
  	TAB
  	SHOW BYE
  	TAB
  	TAB
  	TAB
  	TAB
  	TAB
  	TAB
  	TAB
  	SHOW BY0
  	TAB
  	SHOW BY1
  	TAB
  	SHOW BY2
  	TAB
  	SHOW BY3
  	TAB
  	SHOW BY4
  	TAB
  	SHOW BY5
  	TAB
  	TAB
  	TAB
  	TAB
  	TAB
  	MOV BX,0F00FH		;��Ϣ��ʾ
E0:
  	MOV CX,0FFFFH
E1:	
    LOOP E1
  	DEC BX
  	JNZ E0
  	CALL CLEAR
  	MOV AH,4CH
  	INT 21H
EXIT ENDP


;================������������====================

MAIN:	MOV AX,DATA
	MOV DS,AX
  MOV AH,0
  MOV AL,3                          ;80*25���ı���ʽ
  INT 10H

	MOV AL,0                         
	MOV CL,0                        
 	MOV CH,0                        
 	MOV DH,24                        
 	MOV DL,79                       
 	MOV BH,0FH                     
 	MOV AH,6                         
 	INT 10H	
	TAB
	TAB
	TAB
	TAB
 	SHOW MESS10
 	SHOW MESS1
 	SHOW MESS2
 	SHOW MESS13		
 	SHOW MESS3
 	SHOW MESS4
	SHOW MESS5
	SHOW MESS6
	SHOW MESS7
	SHOW MESS8
	SHOW MESS9
	SHOW MESS14
 	SHOW MESS10
 	SET_P3
		
	MOV AX,ID_LENGTH	
	ADD AX,NAM_LENGTH
	ADD AX,SEX_LENGTH
	ADD AX,SCORE_LENGTH
	MOV STU_LENGTH,AX	;����ÿ��ѧ����Ϣ����
	INC AX
	NOT AX
	ADD AX,1
	MOV STU_LENGTH_ADD1,AX		;ɾ��ʱָ�����
	MOV AX,NAM_LENGTH
	ADD AX,SEX_LENGTH
	ADD AX,SCORE_LENGTH
	NOT AX
	ADD AX,1
	MOV NAM_SEX_SCORE_LENGTH,AX	;�޸�ʱָ�����

	OPENF FID,FPATH			;�Ƿ��½��ı�
	CMP AX,2
	JZ NEWFILE
	CLOSEF FID
	JMP START
NEWFILE:
	CREATEF FID,FPATH
	
START:	
    MOV AH,7		 ;����ѡ������
  	INT 21H
  	CMP AL,'i'		;�ж�
  	JNZ ML
  	CALL INSERT
RETU:	
    JMP MAIN	
ML:	CMP AL,'l'
  	JNZ MQ
  	CALL LIST
  	JMP MAIN
MQ:	CMP AL,'q'
  	JNZ ME
  	CALL QUERY
  	JMP MAIN	
ME:	CMP AL,'e'
  	JNZ MC
  	CALL EXIT
  	JMP MAIN
MC:	CMP AL,'c'
  	JNE MM
  	CALL COUNT
  	JMP MAIN
MM:	CMP AL,'m'
  	JNZ MP
  	CALL MODIFY
  	JMP MAIN	
MP:	CMP AL,'p'
  	JNZ MD
  	CALL PRINT
  	JMP MAIN
MD:	CMP AL,'d'
  	JNZ MNEW
  	CALL DELETE
  	JMP MAIN
MNEW:	CMP AL,'n'	;��ʼ���ı����ݿ�
  	JNZ RETU
  	CALL CLEAR
  	TAB
  	TAB
  	TAB
  	SHOW NEWF
  	MOV AH,7
  	INT 21H
  	CMP AL,'y'
  	JNZ RETU
  	CREATEF FID,FPATH
  	JMP MAIN
	
CODE ENDS
END MAIN

