#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
using namespace std;

#define A1 0//A�������ͣ�BΪ���飬CΪL�ͣ�DΪ�����ͣ�ʵ���޷������Ǹ���״��
#define A2 1

#define B 2

#define C11 3
#define C12 4
#define C13 5
#define C14 6

#define C21 7
#define C22 8
#define C23 9
#define C24 10

#define D11 11
#define D12 12

#define D21 13
#define D22 14

void SetPos(int i,int j)//�趨���λ��
{
	COORD pos={i,j};
	HANDLE Out=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(Out, pos);
}

int sharp[15][8]=
{
	{0,0,1,0,2,0,3,0},{0,0,0,1,0,2,0,3},
	{0,0,1,0,0,1,1,1},
	{0,0,1,0,1,1,1,2},{0,1,1,1,2,0,2,1},{0,0,0,1,0,2,1,2},{0,0,0,1,1,0,2,0},
	{1,0,1,1,1,2,0,2},{0,0,0,1,1,1,2,1},{0,0,0,1,0,2,1,0},{0,0,1,0,2,0,2,1},
	{0,0,0,1,1,1,1,2},{0,1,1,0,1,1,2,0},
	{0,1,0,2,1,0,1,1},{0,0,1,0,1,1,2,1}
};//���2ά�������������������״λ�õ�

int high[15]={4,1,2,2,3,2,3,2,3,2,3,2,3,2,3};//����������������������״�߶ȵ�

class Box//����˹������
{
    private:
	   int map[23][12];//��������
	   int hotpoint[2];//�ȵ㣨����ǰ��ĵ㣬����ͼ�ζ����൱�˵���Ƶģ�
	   int top;//��ǰ���λ��
	   int point;//����
	   int level;//�ȼ�
	   int ID;//��ǰ�ͼ�ε�ID��
   public:
	   Box()//��ʼ��
	   {
		   int i,j;
		   for(i=0;i<23;i++)
			   for(j=0;j<12;j++)
				   map[i][j]=0;
		   hotpoint[0]=0;
		   hotpoint[1]=5;
		   point=0;
		   level=1;
		   top=99;
		   ID=0;
	   }
	   void DrawMap();//������
	   int Judge(int x,int y);//�жϵ�ǰλ���ܷ����ͼ��
	   void Welcome();//��ӭ����
	   void DrawBox(int x,int y,int num);//����ͼ��
	   void Redraw(int x,int y,int num);//����ͼ��
	   void Run();//����
	   void Turn();//ת������
	   void UpdataMap();//���»���
};

void Box::DrawMap()//������
{
	int i;

	for(i=0;i<14;i++)
	{
		 SetPos(i*2,0);
		 cout<<"��";
	}
	for(i=1;i<=24;i++)
	{
		SetPos(0,i);
		cout<<"��";
		SetPos(13*2,i);
		cout<<"��";
	}
	for(i=0;i<14;i++)
	{
		 SetPos(i*2,24);
		 cout<<"��";
	}
	
	i=15;
	for(i=15;i<=25;i++)
	{
		 SetPos(i*2,0);
		 cout<<"��";
	}
	for(i=1;i<=8;i++)
	{
		SetPos(15*2,i);
		cout<<"��";
		SetPos(25*2,i);
		cout<<"��";
	}
	for(i=15;i<=25;i++)
	{
		 SetPos(i*2,9);
		 cout<<"��";
	}

	SetPos(16*2,16);
	cout<<"����˹����";
	SetPos(16*2,17);
	cout<<"������"<<point;
	SetPos(16*2,18);
	cout<<"�ȼ���"<<level;
}

void Box::DrawBox(int x,int y,int num)//����ͼ��
{
	 int i;
	 int nx,ny;
	 for(i=0;i<4;i++)
	{ 
		nx=x+sharp[num][i*2];
		ny=y+sharp[num][i*2+1];
		SetPos((ny+1)*2,nx+1);//����sharp��������ڵ�x,y������״
		cout<<"��";
	}
}

void Box::Redraw(int x,int y,int num)//����ͼ�Σ�ԭ��ͬ��
{
	 int i;
	 int nx,ny;
	 for(i=0;i<4;i++)
	{ 
		nx=x+sharp[num][i*2];
		ny=y+sharp[num][i*2+1];
		SetPos((ny+1)*2,nx+1);
		cout<<" ";
	}
}

void Box::Turn()//ת��ͼ�Σ������ĸ�ID����
{
	switch(ID)
	{
	   case A1: ID=A2; break;
	   case A2: ID=A1; break;

	    case B: ID=B; break;

		case C11: ID=C12; break;
		case C12: ID=C13; break;
		case C13: ID=C14; break;
		case C14: ID=C11; break;

		case C21: ID=C22; break;
		case C22: ID=C23; break;
		case C23: ID=C24; break;
		case C24: ID=C21; break;
		
		case D11: ID=D12; break;
		case D12: ID=D11; break;

		case D21: ID=D22; break;
		case D22: ID=D21; break;
	}

}

void Box::Welcome()//��ӭ����
{
	char x;
	while(1)
	{
	  system("cls");
	  cout<<"��������������������������������������"<<endl;
	  cout<<"��    ����˹�������̨�棨��������  ��"<<endl;
	  cout<<"��������������������������������������"<<endl;
	  cout<<"��     A,D�����ƶ�  S���¼���       ��"<<endl;
	  cout<<"��        �ո��ת������            ��"<<endl;
	  cout<<"��������������������������������������"<<endl;
	  cout<<"��                                  ��"<<endl;
	  cout<<"��                                  ��"<<endl;
	  cout<<"��                                  ��"<<endl;
	  cout<<"��         ��1-9ѡ��ȼ�����        ��"<<endl;
	  cout<<"��                                  ��"<<endl;
	  cout<<"��                                  ��"<<endl;
	  cout<<"��������������������������������������"<<endl;
	  SetPos(8,10);
	  x=getch();
	  if(x<='9'&&x>='1')//���õȼ�
	  {
		  level=x-'0';
		  break;
	  }
	}
}

void Box::UpdataMap()//���»��棨�ؼ���
{
	 int clear;
	 int i,j,k;
	 int nx,ny;
	 int flag;
	 for(i=0;i<4;i++)//����map�������Ϣ
	{ 
		nx=hotpoint[0]+sharp[ID][i*2];
		ny=hotpoint[1]+sharp[ID][i*2+1];
		map[nx][ny]=1;
	}
	 if(hotpoint[0]<top)//����ȵ���ڶ�������¶���
		 top=hotpoint[0];
	 clear=0;//�����ĸ���
	 for(i=hotpoint[0];i<hotpoint[0]+high[ID];i++)
	 {
		 flag=0;
		 for(j=0;j<12;j++)//����Ƿ������������
		 {
			 if(map[i][j]==0)
			 {
				 flag=1;
				 break;
			 }
		 }
		 if(flag==0)//��������
		 {
			 for(k=i;k>=top;k--)//�ӵ�ǰλ���������еĵ�����һ��
			 {
				 if(k==0)//��ߵ����⴦��
					 for(j=0;j<12;j++)
					 {
						 map[k][j]=0;
						 SetPos((j+1)*2,k+1);
						 cout<<" ";
					 }
				 else
				 {
					 for(j=0;j<12;j++)
					 {
						 map[k][j]=map[k-1][j];
						 SetPos((j+1)*2,k+1);
		                 if(map[k][j]==0)
						    cout<<" ";
						 else
							cout<<"��";
					 }
				 }

			 }
			 top++;//�����ɹ�����ߵ�����
			 clear++;
			 point+=clear*100;
		 }
	 }
       
	 SetPos(16*2,17);
	    cout<<"������"<<point;
}

void Box::Run()//������Ϸ
{
	int i=0;
	char x;
	int Count;//������
	int tempID;
	int temp;
	srand((int)time(0));
	ID=rand()%15;//�������ID����һ��ID
	tempID=rand()%15;
	DrawBox(hotpoint[0],hotpoint[1],ID);//����ͼ��
	DrawBox(3,17,tempID);
	Count=1000-level*100;//�ȼ���������
	while(1)
	{
		if(i>=Count)//ʱ�䵽
		{
			i=0;//����������
			if(Judge(hotpoint[0]+1,hotpoint[1]))//����¸�λ����Ч�������ף�
			{
				 UpdataMap();//���»���
				 ID=tempID;//������ID����ԭ�ȴ�ID�滻Ϊ��ǰID
				 hotpoint[0]=0;//�ȵ����
				 hotpoint[1]=5;
                 Redraw(3,17,tempID);
				 tempID=rand()%15;
	             DrawBox(hotpoint[0],hotpoint[1],ID);
	             DrawBox(3,17,tempID);
				 if(Judge(hotpoint[0],hotpoint[1]))//�޷����ƿ�ʼͼ�Σ���Ϸ����
				 {
					 system("cls");
					 SetPos(25,15);
					 cout<<"��Ϸ�������������յ÷�Ϊ��"<<point<<endl;
					 system("pause");
					 exit(0);
				 }

            }
			else
			{
				Redraw(hotpoint[0],hotpoint[1],ID);//û�е��ף���������һλ
			    hotpoint[0]++;//�ȵ�����
				DrawBox(hotpoint[0],hotpoint[1],ID);
			}

		}
		if(kbhit())//��ȡ������Ϣ
		{
			x=getch();
			if(x=='a'||x=='A')//����
			{
				 if(Judge(hotpoint[0],hotpoint[1]-1)==0)
				 {
					 Redraw(hotpoint[0],hotpoint[1],ID);
					 hotpoint[1]-=1;
				     DrawBox(hotpoint[0],hotpoint[1],ID);
				 }
			}
			if(x=='d'||x=='D')//����
			{
			     if(Judge(hotpoint[0],hotpoint[1]+1)==0)
				 {
					 Redraw(hotpoint[0],hotpoint[1],ID);
					 hotpoint[1]+=1;
				     DrawBox(hotpoint[0],hotpoint[1],ID);
				 }
			}
			if(x=='s'||x=='S')//���¼���
			{
			     if(Judge(hotpoint[0]+1,hotpoint[1])==0)
				 {
					 Redraw(hotpoint[0],hotpoint[1],ID);
					 hotpoint[0]+=1;
				     DrawBox(hotpoint[0],hotpoint[1],ID);
				 }
			}
			if(x==' ')//ת������
			{
				temp=ID;
				Turn();
				if(Judge(hotpoint[0],hotpoint[1])==0)
				 {
					 Redraw(hotpoint[0],hotpoint[1],temp);
				     DrawBox(hotpoint[0],hotpoint[1],ID);
				 }
				else
				    ID=temp;
			}
			while(kbhit())//����ʣ�µļ�����Ϣ
				getch();
		}
		Sleep(1);//�ȴ�1����
		i++;//��������1
    }
}

int Box::Judge(int x,int y)//�жϵ�ǰ�Ƿ���Ի��Ʒ���
{
	int i;
	int nx,ny;
	for(i=0;i<4;i++)
	{ 
		nx=x+sharp[ID][i*2];
		ny=y+sharp[ID][i*2+1];
		if(nx<0||nx>=23||ny<0||ny>=12||map[nx][ny]==1)//���ܣ�����1
			return 1;
	}
	return 0;
}

int main()//������
{
	Box game;
    game.Welcome();
	system("cls");
	game.DrawMap();
	game.Run();
	system("pause");
}
//��nice