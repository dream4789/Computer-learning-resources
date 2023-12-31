#include "stdio.h"
#include "stdlib.h"

// 文件索引表的定义
struct index{
	int lr[32];
	int pr[32];
	char st[32];
}*wq;
#define JOBN 20

// 文件目录的定义
struct list{
	char names[32];
	int size[32];
	
	int pride[1]; // 读写权限，0只读，1读写
  	int rex[1];   // 读写状态，0为关闭状态，1读2写
  	
	// 1.增加新属性的的定义（类型以及变量名）
	struct index*p[32];  // 文件的索引表地址
}*HEAD;

// 作业序列
struct que{
	char name;
	int size;
	
	int pride;
	int rex;
	
	// 2.增加输入新属性保存定义（类型以及名字）
}job[JOBN];


int i,j,ly,li;
char bb;
int NFile=0;//系统的总文件数，模拟开始时为0；
int N=0;//工作变量，标记当前分配文件
int M=32;//系统中空闲磁盘物理块数，开始为32块
int J[4][8];//用位图表示这些磁盘物理块，J[j][i]为0时标记第j*8+i块空闲，为1标记该块已分配出去
FILE *e;//记录模拟中的相关数据
int jobs=0;//作业数

void run(){
	int x1,y,z;
	
    // 如果当前空闲磁盘物理块数能够满足需要，则进行分配
	if(job[N].size<=M){
		ly=0;
		N=NFile;// 标记当前分配文件
		NFile++;// 标记下次分配处理文件
		M-=job[N].size;
			
		// 将文件名以及大小，索引地址填写到文件目录
		HEAD->names[N]=job[N].name;
		HEAD->size[N]=job[N].size;
		HEAD->pride[N]=job[N].pride;
		HEAD->rex[N]=job[N].rex;
		
		printf("---\n");
		
		
        // 3.此处，（按照以上name或size属性）增加新属性值从输入保存地方(job中)，放入文件目录HEAD中
		wq=(struct index *)malloc(sizeof(struct index));
		HEAD->p[N]=wq;
		
		printf("===\n");
		
		// 对分配文件的索引表初始化
		for(z=0;z<32;z++){
			wq->lr[z]=z;// 逻辑块号
			wq->pr[z]=0;// 物理块地址
			wq->st[z]='N';
		}
		
		printf("+++\n");
		// 从位图中分配，分配出去的块其状态为1。一直到分配完成
		for(j=0;j<4&&(ly<job[N].size);j++)
			for(i=0;i<8&&(ly<job[N].size);i++) {
				if(J[j][i]==0){
					li=j*8+i;
					wq->pr[ly]=li;
					wq->st[ly]='Y';
					ly++;
					J[j][i]=1;
				}// 找到一个空闲块，就分配出去
			}
	}else{ 		// 如果当前空闲磁盘物理块数不能够满足需要，则出错处理
		fprintf(e,"\n There are no free blocks in the memory now! \n");
		fprintf(e,"File %c must wait!\n",job[N].name);
	}
	
	printf(">>>\n");

	// 报告目前为止的分配情况，首先报告文件目录的部分信息
    fprintf(e,"...This time ,the file directory:    ----\n");
	fprintf(e,"NAME   size   pride(0/1)   rex(0/1/2)   INDEX_ADDRESS\n");
	for(x1=0;x1<N+1;x1++){  // 4
		fprintf(e,"      %c     %d    %d      %d     %x\n",HEAD->names[x1],HEAD->size[x1],HEAD->pride[x1],HEAD->rex[x1],HEAD->p[x1]);//5
		
    	printf("      %c     %d    %d      %d     %x\n",HEAD->names[x1],HEAD->size[x1],HEAD->pride[x1],HEAD->rex[x1],HEAD->p[x1]);
    }
    // 4.在上面的输出语句中，增加新属性的输出，注意格式控制符与新属性类型要一致
    
    printf("<<<\n");
    
	// 其次报告文件索引表的部分信息
	for(x1=0;x1<N+1;x1++){
		fprintf(e," //////////The index of FILE%c://///////\n",HEAD->names[x1]);
    	fprintf(e," LOGIC_NUMBER  PHYSICAL_NUMBER   FLAG\n");
		for(y=0;y<HEAD->size[x1];y++){
			printf("     %d             %d             %c\n",HEAD->p[x1]->lr[y],HEAD->p[x1]->pr[y],HEAD->p[x1]->st[y]);
			fprintf(e,"     %d             %d             %c\n",HEAD->p[x1]->lr[y],HEAD->p[x1]->pr[y],HEAD->p[x1]->st[y]);
			
		}
	}
	
	printf("!!!\n");
	
	// 第三，报告位图信息
	fprintf(e,"             This time the bit mapping graph:               \n");
	for(j=0;j<4;j++){
		fprintf(e, "        ");
    	for(i=0;i<8;i++)
    		fprintf(e,"%d",J[j][i]);
		fprintf(e,"\n");
	}
}


int main(){
	int k;
	e=fopen("results.txt","w");// 打开保存结果的文件
	
	for(j=0;j<4;j++)
		for(i=0;i<8;i++)
			J[j][i]=0;// 初始化位图

	HEAD=(struct list*)malloc(sizeof(struct list));
	for(i=0;i<32;i++){
		HEAD->names[i]=' '; 
		HEAD->size[i]=0;
		HEAD->p[i]=NULL;
	}// 初始化文件目录
	
	printf("Please input number of jobs:");
	scanf("%d",&jobs);
	scanf("%c",&bb);
	
	int kk=0;
	
	// 以下输入建立的文件数以及文件名字，并将这些信息保存在job数组之中
	while(kk<jobs){
		fprintf(e,"FILE %d: \n",kk);
		printf("FILE %d: \n",kk);
		printf("Name and Size: ");
		scanf("%c %d",&(job[kk].name),&(job[kk].size));
		scanf("%c",&bb);
		
		do{
		
			printf("Enter read or write permissions (0/1): ");
			scanf("%d",&(job[kk].pride));
			scanf("%c",&bb);
		}while(job[kk].pride!=1 && job[kk].pride!=0);
		
		job[kk].rex = 0;
		fprintf(e,"%c,%d,%d,%d", job[kk].name, job[kk].size, job[kk].pride, job[kk].rex);
		kk++;
	}
	
	// 5.按照以上输入name的方法，此处增加新增加属性的输入语句，注意输入格式控制符与新增属性类型要一致，也要注意增加提示输入信息
	for(k=1;k<=jobs;k++)
		run();// 每个文件进行一次分配
	
	// 回收资源
	fclose(e);
	for(i=0;i<32;i++){
		free(HEAD->p[i]);
		HEAD->p[i]=NULL;
	}
	
	free(HEAD);
	HEAD=NULL;
	return 0;
} 