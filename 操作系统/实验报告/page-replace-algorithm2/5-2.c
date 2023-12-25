#include "stdio.h"
#include "stdlib.h"

// �ļ�������Ķ���
struct index{
	int lr[32];
	int pr[32];
	char st[32];
}*wq;
#define JOBN 20

// �ļ�Ŀ¼�Ķ���
struct list{
	char names[32];
	int size[32];
	
	int pride[1]; // ��дȨ�ޣ�0ֻ����1��д
  	int rex[1];   // ��д״̬��0Ϊ�ر�״̬��1��2д
  	
	// 1.���������ԵĵĶ��壨�����Լ���������
	struct index*p[32];  // �ļ����������ַ
}*HEAD;

// ��ҵ����
struct que{
	char name;
	int size;
	
	int pride;
	int rex;
	
	// 2.�������������Ա��涨�壨�����Լ����֣�
}job[JOBN];


int i,j,ly,li;
char bb;
int NFile=0;//ϵͳ�����ļ�����ģ�⿪ʼʱΪ0��
int N=0;//������������ǵ�ǰ�����ļ�
int M=32;//ϵͳ�п��д��������������ʼΪ32��
int J[4][8];//��λͼ��ʾ��Щ��������飬J[j][i]Ϊ0ʱ��ǵ�j*8+i����У�Ϊ1��Ǹÿ��ѷ����ȥ
FILE *e;//��¼ģ���е��������
int jobs=0;//��ҵ��

void run(){
	int x1,y,z;
	
    // �����ǰ���д�����������ܹ�������Ҫ������з���
	if(job[N].size<=M){
		ly=0;
		N=NFile;// ��ǵ�ǰ�����ļ�
		NFile++;// ����´η��䴦���ļ�
		M-=job[N].size;
			
		// ���ļ����Լ���С��������ַ��д���ļ�Ŀ¼
		HEAD->names[N]=job[N].name;
		HEAD->size[N]=job[N].size;
		HEAD->pride[N]=job[N].pride;
		HEAD->rex[N]=job[N].rex;
		
		printf("---\n");
		
		
        // 3.�˴�������������name��size���ԣ�����������ֵ�����뱣��ط�(job��)�������ļ�Ŀ¼HEAD��
		wq=(struct index *)malloc(sizeof(struct index));
		HEAD->p[N]=wq;
		
		printf("===\n");
		
		// �Է����ļ����������ʼ��
		for(z=0;z<32;z++){
			wq->lr[z]=z;// �߼����
			wq->pr[z]=0;// ������ַ
			wq->st[z]='N';
		}
		
		printf("+++\n");
		// ��λͼ�з��䣬�����ȥ�Ŀ���״̬Ϊ1��һֱ���������
		for(j=0;j<4&&(ly<job[N].size);j++)
			for(i=0;i<8&&(ly<job[N].size);i++) {
				if(J[j][i]==0){
					li=j*8+i;
					wq->pr[ly]=li;
					wq->st[ly]='Y';
					ly++;
					J[j][i]=1;
				}// �ҵ�һ�����п飬�ͷ����ȥ
			}
	}else{ 		// �����ǰ���д�������������ܹ�������Ҫ���������
		fprintf(e,"\n There are no free blocks in the memory now! \n");
		fprintf(e,"File %c must wait!\n",job[N].name);
	}
	
	printf(">>>\n");

	// ����ĿǰΪֹ�ķ�����������ȱ����ļ�Ŀ¼�Ĳ�����Ϣ
    fprintf(e,"...This time ,the file directory:    ----\n");
	fprintf(e,"NAME   size   pride(0/1)   rex(0/1/2)   INDEX_ADDRESS\n");
	for(x1=0;x1<N+1;x1++){  // 4
		fprintf(e,"      %c     %d    %d      %d     %x\n",HEAD->names[x1],HEAD->size[x1],HEAD->pride[x1],HEAD->rex[x1],HEAD->p[x1]);//5
		
    	printf("      %c     %d    %d      %d     %x\n",HEAD->names[x1],HEAD->size[x1],HEAD->pride[x1],HEAD->rex[x1],HEAD->p[x1]);
    }
    // 4.��������������У����������Ե������ע���ʽ���Ʒ�������������Ҫһ��
    
    printf("<<<\n");
    
	// ��α����ļ�������Ĳ�����Ϣ
	for(x1=0;x1<N+1;x1++){
		fprintf(e," //////////The index of FILE%c://///////\n",HEAD->names[x1]);
    	fprintf(e," LOGIC_NUMBER  PHYSICAL_NUMBER   FLAG\n");
		for(y=0;y<HEAD->size[x1];y++){
			printf("     %d             %d             %c\n",HEAD->p[x1]->lr[y],HEAD->p[x1]->pr[y],HEAD->p[x1]->st[y]);
			fprintf(e,"     %d             %d             %c\n",HEAD->p[x1]->lr[y],HEAD->p[x1]->pr[y],HEAD->p[x1]->st[y]);
			
		}
	}
	
	printf("!!!\n");
	
	// ����������λͼ��Ϣ
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
	e=fopen("results.txt","w");// �򿪱��������ļ�
	
	for(j=0;j<4;j++)
		for(i=0;i<8;i++)
			J[j][i]=0;// ��ʼ��λͼ

	HEAD=(struct list*)malloc(sizeof(struct list));
	for(i=0;i<32;i++){
		HEAD->names[i]=' '; 
		HEAD->size[i]=0;
		HEAD->p[i]=NULL;
	}// ��ʼ���ļ�Ŀ¼
	
	printf("Please input number of jobs:");
	scanf("%d",&jobs);
	scanf("%c",&bb);
	
	int kk=0;
	
	// �������뽨�����ļ����Լ��ļ����֣�������Щ��Ϣ������job����֮��
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
	
	// 5.������������name�ķ������˴��������������Ե�������䣬ע�������ʽ���Ʒ���������������Ҫһ�£�ҲҪע��������ʾ������Ϣ
	for(k=1;k<=jobs;k++)
		run();// ÿ���ļ�����һ�η���
	
	// ������Դ
	fclose(e);
	for(i=0;i<32;i++){
		free(HEAD->p[i]);
		HEAD->p[i]=NULL;
	}
	
	free(HEAD);
	HEAD=NULL;
	return 0;
} 