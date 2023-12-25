;学生成绩管理系统

DATA SEGMENT

    TIPS0 DB 'Tips:',0DH,0AH,'$'				;插入提示信息
    TIPS1 DB '          SEX: 1:male   0:female',0DH,0AH,'$'
    TIPS3 DB 'Please input ID:$'				;查询提示信息
    TIPS4 DB '  Please enter "r" to return$'
    TIPS5 DB '  Please enter "r" to return,"c" to continue$'
    ID    DB '   ID: $'
    NAM   DB ' NAME: $'
    SEX   DB '  SEX: $'
    SCORE DB 'SCORE: $'
    
    FID   DW ?		;文件号
    SEXM  DB 'male     $'
    SEXF  DB 'female   $'
    COUNT_A DB '         9 0 ~ 100: $'		;统计提示信息
    COUNT_B DB '         8 0 ~ 8 9: $'
    COUNT_C DB '         7 0 ~ 7 9: $'
    COUNT_D DB '         6 0 ~ 6 9: $'
    COUNT_E DB '         0 0 ~ 5 9: $'
    AB      DB    5 DUP('0')		;统计结果
    
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
    
    ID_LENGTH    EQU 4		;配置信息
    NAM_LENGTH   EQU 20
    SEX_LENGTH   EQU 1	  ;性别请勿更改位数
    SCORE_LENGTH EQU 5
    
    STU_LENGTH DW ?		;每条学生信息总长度
    STU_LENGTH_ADD1 DW ?
    NAM_SEX_SCORE_LENGTH DW ?
    
    DEL      DB 30 DUP (' ')	;清空信息用
    DEL_DONE DB '   Delete success !$'
    
    ERR      DB '  Data error,Please input again!$'	;错误提示信息
    NOSTU    DB '   Sorry,there is no this studnet!$'
    ERR_NO   DB '  No student information!$'
    ERR_SAME DB '   There is the same ID,please input again!$'
    NEWF     DB 0DH,0AH,0DH,0AH,'    Warning: this operation will empty all your data!',0DH,0AH,0DH,0AH,'    Will you continue? (y:empty,other key:return):$'
    
    
    FPATH DB 'c:\score.txt',0	;数据库文本
    
    STR   DB 50		;缓冲区str
          DB ?
          DB 50 DUP (?)
    STR0  DB 50 DUP (?)	;缓冲区str0
    
    ENTER DB '   $'			;空格
    TMP   DW 0			    ;是否为空标志信息
    SC    DB 0			  	;分数保护处用 
    
    BYE DB '                      Thanks for use our program!',0DH,0AH,0DH,0AH,'                               Bye~ Bye~$'
    BY0 DB '                    Writer:                         $'
    BY1 DB '                         07212151206 (Gao      Tian)$'
    BY2 DB '                         07212151207 (Yu Chang Ming)$'
    BY3 DB '                         07212151208 (Yi    Bao  Fa)$'
    BY4 DB '                         07212151209 (Dong  Jun Zai)$'
    BY5 DB '                         07212151210 (Luo      Chun)$'

DATA ENDS


SET_P1  MACRO				    ;设定光标位置A
    MOV AH,02H
    MOV DH,02
    MOV DL,03
    MOV BH,0
    INT 10H
ENDM

SET_P3 MACRO
     MOV AH,02H         ;设定光标的位置B   
     MOV DH,15               	          
     MOV DL,44
     MOV BH,0           ;当前这页
     INT 10H
ENDM


TAB MACRO				;换行
    MOV AH,2
    MOV DL,0DH
    INT 21H
    MOV DL,0AH
    INT 21H
ENDM

CREATEF MACRO FILE_ID,FILE_PATH		;创建文件（[传入]文件号、[传入]文件路径）
  	MOV AH,3CH
  	MOV CX,00H			;普通文件
  	LEA DX,FILE_PATH
  	INT 21H
  	MOV FILE_ID,AX
ENDM

OPENF MACRO FILE_ID,FILE_PATH		;打开文件（[传入]文件号、[传入]文件路径）
  	MOV AL,2			;读写文式打开
  	MOV AH,3DH
  	LEA DX,FILE_PATH
  	INT 21H
  	MOV FILE_ID,AX
ENDM

CLOSEF  MACRO FILE_ID			;关闭文件（[传入]文件号）
  	MOV BX,FILE_ID
  	MOV AH,3EH
  	INT 21H	
ENDM

READF MACRO FILE_ID,TEMP,NUM		;读文件（[传入]文件号、[传入]缓冲区、[传入]字节数）
  	MOV BX,FILE_ID
  	LEA DX,TEMP
  	MOV AX,NUM
  	MOV CX,AX
  	MOV AH,3FH
  	INT 21H
ENDM

WRITEF MACRO FILE_ID,TEMP,NUM		;写文件（[传入]文件号、[传入]缓冲区、[传入]字节数）
	MOV BX,FILE_ID
	MOV CX,NUM
	LEA DX,TEMP[2]
	MOV AH,40H
	INT 21H
ENDM

MOVEF MACRO FILE_ID,STYPE,HIGEC,LOWD	;移动文件指针（[传入]文件号、[传入]移动方式、[传入]偏移字节（高位）[传入]偏移字节（低位））
  	MOV BX,FILE_ID
  	MOV AH,42H
  	MOV AL,STYPE			;尾+偏移量方式
  	MOV CX,HIGEC			;偏移字节（高位）
  	MOV DX,LOWD			;偏移字节（低位）
  	INT 21H
ENDM


INPUT MACRO BUFFER,LENGTH		;输入字符串（[传入]字符串名、[返回]字符串长度）
  	MOV AH,10
  	LEA DX,BUFFER
  	INT 21H
  	MOV LENGTH,BUFFER[1]
ENDM

SHOW MACRO BUFFER			;显示字符串（[传入]字符串名）
  	MOV AH,9
  	LEA DX,BUFFER
  	INT 21H
ENDM



STAK SEGMENT STACK
  DB 200 DUP (?)
STAK ENDS



CODE SEGMENT
  ASSUME CS:CODE,DS:DATA
SHOW_EXIT PROC NEAR		;提示按r退出
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

SHOW_EC PROC NEAR		;询问退出还是继续
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


SHOW_ERR PROC NEAR		;显示出错信息子程序
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

RE_TMP PROC NEAR		;用空格初始化缓冲区子程序
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


CLEAR  PROC NEAR 		;清屏
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX                      
    MOV AL,0                         ;上滚行数
    MOV CL,0                         ;上滚窗口左上角的列号为0
    MOV CH,0                         ;上滚窗口左上角的行号为0
    MOV DH,24                        ;上滚窗口右上角的行号为24
    MOV DL,79                        ;上滚窗口右上角的列号为79
    MOV BH,14                        ;空白行的属性
    MOV AH,6                         ;入口参数
    INT 10H
    SET_P1
    POP DX
    POP CX
    POP BX
    POP AX
    RET
CLEAR  ENDP   

SHOW_STU PROC NEAR		;显示学生信息子程序
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
  	CMP DL,'1'		;  1显示male,  0显示female
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

PRINT_STU PROC NEAR		;打印学生信息子程序
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

;====================以下插入(insert)子程序================
INSERT PROC NEAR
  	PUSH AX
  	PUSH BX
  	PUSH CX
  	PUSH DX	
  	TAB
          CALL CLEAR              ;清屏	
  	SHOW TIPS0		;显示提示信息
  	SHOW TIPS1
  	TAB
  	TAB
  					
  	OPENF FID,FPATH		;打开文件
		
IN_ID:	SHOW ID			; 学号		
  	INPUT STR,BL		;向缓冲区输入ID
  	CMP BL,ID_LENGTH	;看ID是否合法
  	JZ L1
  	JNZ ERR_ID
ERR_SA: 			;错误处理
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
L1:					;ID判断只能为数字
  	MOV CX,ID_LENGTH
  	LEA SI,STR+2
LN:	MOV AL,BYTE PTR[SI]
  	CMP AL,'0'
  	JB   ERR_ID
  	CMP  AL,'9'
  	JA   ERR_ID 
  	INC SI
  	LOOP LN
	  MOVEF FID,0,0,0			;指针移到文件首
IA:	
	  MOVEF FID,1,0,5		
	
IB:	READF FID,STR0,STU_LENGTH	;读取学生信息
    	CMP AX,0			;文件是否结束
    	JNZ IL1	
    	JMP IC				;没有重复学号，可以插入
IL1:	LEA SI,STR0
    	LEA DI,STR
    	INC DI
    	DEC SI
    	MOV CX,ID_LENGTH	
IL2:	INC SI
    	INC DI
    	MOV AL,BYTE PTR [DI]
    	CMP AL,BYTE PTR [SI]
    	JNZ IA			;不符合条件读取下一个同学信息
    	LOOPZ IL2		
    	JMP ERR_SA		;有重复学号
	
IC:	MOVEF FID,2,0,5
  	WRITEF FID,STR,ID_LENGTH;数据合法则写入数据
  	TAB

IN_NAM:	SHOW NAM		;姓名
  	CALL RE_TMP		;初始化缓冲区
  	INPUT STR,BL
  
  	ADD BL,2		;去掉回车
  	MOV BH,0		
  	MOV SI,BX
  	MOV STR[SI],' '
  	SUB BL,2
  
  	CMP BL,NAM_LENGTH
  	JNA L2
ERR_NAM:
  	CALL SHOW_ERR
  	JMP IN_NAM
	
L2:	CMP STR[2],' '		;姓名第一个字符不为空
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
  	
IN_SEX:	SHOW SEX		;性别
  	CALL RE_TMP
  	INPUT STR,BL
  
  	ADD BL,2		;去掉回车
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
  	MOV SC,BL		;BL保护
  	ADD BL,2		;去掉回车
  	MOV BH,0
  	MOV SI,BX
  	MOV STR[SI],' '
  	SUB BL,2
  
  	CMP BL,SCORE_LENGTH		;分数最多4位
  	JB L5
ERR_SCORE:
  	CALL SHOW_ERR
  	JMP IN_SCORE
	
L5:	MOV CX,BX	;分数只能是数字和.
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
  	CMP BL,4		;分数(0~100),支持一位小数
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
  
  	CLOSEF FID			;关闭文件
  	CALL SHOW_EC
  	POP DX
  	POP CX
  	POP BX
  	POP AX
  	RET
INSERT ENDP

;================以下是查询(query)子程序================
QUERY PROC NEAR
  	PUSH AX
  	PUSH BX
  	PUSH CX
  	PUSH DX
    CALL CLEAR
  	OPENF FID,FPATH			;打开文件
IN_ID1:	SHOW TIPS3			;显示提示信息		
  	INPUT STR,BL			;向缓冲区STR输入ID
  	CMP BL,ID_LENGTH		;看ID是否合法
  	JZ QL1
QERR_ID: 				;错误处理
  	CALL SHOW_ERR
  	JMP IN_ID1

A:	MOVEF FID,1,0,5
	
B:	READF FID,STR0,STU_LENGTH	;读取学生信息
	  CMP AX,0			;文件是否结束
  	JNZ QL1				

QL3:	TAB
    	TAB			;文件结束，没有该学生信息
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
    	JNZ A			;不符合条件读取下一个同学信息
    	LOOPZ QL2
    	
    	TAB
    	TAB			;符合条件显示
    	CALL SHOW_STU	
    	JMP C
	
C:	CLOSEF FID
  	TAB
  	TAB
  	SHOW TIPS5		;询问退出还是继续
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

;==============以下是浏览(list)子程序==================

LIST PROC NEAR
  	PUSH AX
  	PUSH BX
  	PUSH CX
  	PUSH DX	
  	CALL CLEAR
  	MOV AX,0
  	MOV TMP,AX			;是否为空标志清0	
  	OPENF FID,FPATH			;打开文件
  	TAB

D:	MOVEF FID,1,0,5
E:	READF FID,STR0,STU_LENGTH	;读取学生信息
  	CMP AX,0			;是否到文件尾
  	JNZ G						
  	CMP TMP,0			;判断有没有信息
  	JNZ F
  	TAB
  	TAB
  	TAB
  	SHOW ERR_NO
  	JMP F
				
	
G:	MOV CX,ID_LENGTH		;ID为空不显示
  	MOV BX,0
  	DEC BX
NULL:	INC BX
    	CMP STR0[BX],' '
    	JZ D
    	LOOP NULL
    	CALL SHOW_STU
    	INC TMP		;有信息为空标志自加
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

;===============以下是删除(delete)子程序=====================

DELETE  PROC NEAR
  	PUSH AX
  	PUSH BX
  	PUSH CX
  	PUSH DX
  	CALL CLEAR
  	OPENF FID,FPATH			;打开文件

D0:	SHOW TIPS3			;显示提示信息		
  	INPUT STR,BL			;向缓冲区STR输入ID
  	CMP BL,ID_LENGTH		;看ID是否合法
  	JZ D2
  	CALL SHOW_ERR
  	JMP D0

D2:	MOVEF FID,1,0,5
  	READF FID,STR0,STU_LENGTH	;读取学生信息
  	CMP AX,0			;文件是否结束
  	JNZ D5
  	TAB
  	TAB				
  	SHOW NOSTU			;文件结束，没有该学生信息
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
  	JNZ D2			;不符合条件读取下一个同学信息
  	LOOPZ D6
  	
  	TAB			;显示修改前信息
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
    	SHOW TIPS5		;询问退出还是继续
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

;===============以下是修改(modify)子程序=====================

MODIFY PROC NEAR
  	PUSH AX
  	PUSH BX
  	PUSH CX
  	PUSH DX
  	CALL CLEAR
  	OPENF FID,FPATH			;打开文件

M0:	SHOW TIPS3			;显示提示信息		
  	INPUT STR,BL			;向缓冲区STR输入ID
  	CMP BL,ID_LENGTH		;看ID是否合法
  	JZ M2
  	CALL SHOW_ERR
  	JMP M0

M2:	MOVEF FID,1,0,5
  	READF FID,STR0,STU_LENGTH	;读取学生信息
  	CMP AX,0			;文件是否结束
  	JNZ M5
  	TAB
  	TAB				
  	SHOW NOSTU			;文件结束，没有该学生信息
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
  	JNZ M2			;不符合条件读取下一个同学信息
  	LOOPZ M6
  	
  	TAB			;显示修改前信息
  	TAB
  	CALL SHOW_STU
  	TAB
  	TAB

M7:	SHOW NAM		;开始修改信息
  	CALL RE_TMP		;初始化缓冲区
  	INPUT STR,BL
  
  	ADD BL,2		;去掉回车
  	MOV BH,0		
  	MOV SI,BX
  	MOV STR[SI],' '
  	SUB BL,2
  
  	CMP BL,NAM_LENGTH
  	JNA ML2			;开始修改信息

ERR_N0:
    	CALL SHOW_ERR		;溢出提示
    	JMP M7

ML2:	
    	CMP STR[2],' '		;姓名第一个字符不为空
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
	
MM0:	MOV CX,NAM_LENGTH		;名字只能是字母或空格
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
    
    	MOVEF FID,1,0FFFFH,NAM_SEX_SCORE_LENGTH		;指针移到姓名处
    	WRITEF FID,STR,NAM_LENGTH
    	TAB
	
M10:	SHOW SEX
    	CALL RE_TMP
    	INPUT STR,BL
    
    	ADD BL,2		;去掉回车
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
M11:	CALL SHOW_ERR		;错误提示
	    JMP M10

M12:	WRITEF FID,STR,SEX_LENGTH
	    TAB
M13:
    	SHOW SCORE
    	CALL RE_TMP
    	INPUT STR,BL
    	MOV SC,BL	
    
    	ADD BL,2		;去掉回车
    	MOV BH,0
    	MOV SI,BX
    	MOV STR[SI],' '
    	SUB BL,2
    
    	CMP BL,SCORE_LENGTH		;分数错误判断
    	JB M14
MEC:	CALL SHOW_ERR
	    JMP M13
M14:	MOV BL,SC
    	MOV BH,0
    	MOV CX,BX	;分数只能是数字和.
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
M21:	JMP MEC			;中转
M17:	MOV BL,SC
    	CMP BL,4		;分数(0~100),支持一位小数
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
    	SHOW TIPS5		;询问退出还是继续
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

;===========以下是统计各分数段人数(count)子程序==============

COUNT PROC NEAR
    	PUSH AX
    	PUSH BX
    	PUSH CX
    	PUSH DX	
      CALL CLEAR
    	TAB
    	TAB
    	TAB
    	OPENF FID,FPATH			;打开文件

C_0:	MOV BX,FID
    	MOV AH,42H
    	MOV AL,1			;当前+偏移量方式
    	MOV CX,0			;偏移字节（高位）
    	MOV DX,5			;偏移字节（低位）
    	INT 21H
    	
	
C_1:	READF FID,STR0,STU_LENGTH	;读取学生信息
    	CMP AX,0			
    	JZ C_8				;到文件尾则结束
    	MOV BX,ID_LENGTH
    	ADD BX,NAM_LENGTH
    	INC BX
    	MOV AX,BX
    	MOV DL,STR0[BX]			;DL里放分数第一位
    	CMP DL,'1'			    ;如果是100分直接显示A
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
	      SHOW COUNT_A    ;显示每个阶段分数的人数
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


;===============以下是打印(print)子程序======================

PRINT PROC NEAR
  	PUSH AX
  	PUSH BX
  	PUSH CX
  	PUSH DX	
  	CALL CLEAR	
  	OPENF FID,FPATH			;打开文件
  	TAB
P1:	
    MOVEF FID,1,0,5
		
P2:	
    READF FID,STR0,STU_LENGTH	;读取学生信息
  	CMP AX,0			
  	JZ P3				;到文件尾则结束
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

;===============以下是退出(exit)子程序=======================

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
  	MOV BX,0F00FH		;信息显示
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


;================以下是主程序====================

MAIN:	MOV AX,DATA
	MOV DS,AX
  MOV AH,0
  MOV AL,3                          ;80*25的文本方式
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
	MOV STU_LENGTH,AX	;计算每个学生信息长度
	INC AX
	NOT AX
	ADD AX,1
	MOV STU_LENGTH_ADD1,AX		;删除时指针参数
	MOV AX,NAM_LENGTH
	ADD AX,SEX_LENGTH
	ADD AX,SCORE_LENGTH
	NOT AX
	ADD AX,1
	MOV NAM_SEX_SCORE_LENGTH,AX	;修改时指针参数

	OPENF FID,FPATH			;是否新建文本
	CMP AX,2
	JZ NEWFILE
	CLOSEF FID
	JMP START
NEWFILE:
	CREATEF FID,FPATH
	
START:	
    MOV AH,7		 ;输入选择命令
  	INT 21H
  	CMP AL,'i'		;判断
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
MNEW:	CMP AL,'n'	;初始化文本数据库
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

