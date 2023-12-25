#include "console.h"

int main1()
{
	int *BlockofMemory;		//内存物理块
	const int BlockCount = 5;
	int PageNumofRef[] = {7,0,1,2,0,3,0,4,2,3,0,1,1,7,0,1,0,3};  //页面号引用串
	int PageNumRefCount = sizeof(PageNumofRef) / sizeof(PageNumofRef[0]);

	BlockofMemory = (int*)malloc(BlockCount * sizeof(int));
	if(BlockofMemory == (int*)NULL)
	{
		printf("内存分配出错\n");
		exit(1);
	}
	// printf("%d --- %d",PageNumRefCount,*BlockofMemory);  // 18 --- 12466016

	// ResetBlockofMemory(BlockofMemory, BlockCount);
	// Opt(BlockofMemory, PageNumofRef, BlockCount, PageNumRefCount);

	// ResetBlockofMemory(BlockofMemory,BlockCount);
	// Fifo(BlockofMemory, PageNumofRef, BlockCount, PageNumRefCount);
	
	ResetBlockofMemory(BlockofMemory,BlockCount);
	Lru(BlockofMemory, PageNumofRef, BlockCount, PageNumRefCount);

	free(BlockofMemory);

	return 0;
}

//输出内存块页面序号
int OutputBlockofMemory(int *BlockofMemory, int BlockCount, int ReplacePage, int PageNum)
{
	int i;

	printf("访问页面 %d 后，", PageNum);
	printf("内存中的页面号为:\t");
	for(i = 0; i < BlockCount; i++)
	{
		if(BlockofMemory[i] < 0)
			printf("#  ");
		else
			printf("%d  ", BlockofMemory[i]);
	}

	if(ReplacePage != -1)
		printf("\t淘汰页面号为:%d", ReplacePage);

	printf("\n");

	return -1;
}

//输出页面引用串号
void OutputPageNumofRef(int* PageNumofRef, int PageNumRefCount)
{
	int i = 0;
	printf("页面引用串为:\t");
	for(i = 0; i < PageNumRefCount; i++)
		printf("%d  ", PageNumofRef[i]);
	printf("\n");
}

//内存块页面号清零
void ResetBlockofMemory(int *BlockofMemory, int BlockCount)
{
	int i;
	for(i = 0; i < BlockCount; i++)
		BlockofMemory[i] = -1;
}

//判断页是否在内存中，如果页在内存中，返回1，否则返回0；
int PageInBlockofMemory(int PageNum, int *BlockofMemory, int BlockCount)
{
	int i;
	for(i = 0; i < BlockCount; i++)
		if(PageNum == BlockofMemory[i])
			return 1;
	return 0;
}

//下次访问次序
//参数j:  页面在内存块中的位置
//参数i： 页面号在页面号引用串中的位置
int DistanceOpt(int *BlockofMemory, int *PageNumofRef, int j, int i, int PageNumRefCount)
{
	int k;
	for(k = i + 1; k < PageNumRefCount; k++)
		if(BlockofMemory[j] == PageNumofRef[k])
			return k;
	return PageNumRefCount;
}

//最佳页面置换算法OPT
void Opt(int *BlockofMemory, int *PageNumofRef, int BlockCount, int PageNumRefCount)
{
	int i, j, k;
	int MaxIndex1, MaxIndex2;
	int MissCount = 0;
	int ReplacePage;
	int EmptyBlockCount = BlockCount;

	printf("**********最佳页面置换算法：**********\n");

	//输出页面引用串号
	OutputPageNumofRef(PageNumofRef, PageNumRefCount);

	for(i = 0; i < PageNumRefCount; i++)
	{
		if(!PageInBlockofMemory(PageNumofRef[i], BlockofMemory, BlockCount)) //页不在内存中
		{
			MissCount++;

			if(EmptyBlockCount > 0)
			{
				BlockofMemory[BlockCount - EmptyBlockCount] = PageNumofRef[i];
				OutputBlockofMemory(BlockofMemory, BlockCount, -1, PageNumofRef[i]);
				EmptyBlockCount--;
			}
			else
			{
				MaxIndex1 = MaxIndex2 = 0;
				//求出未来最长时间不被访问的页
				for(j = 0; j < BlockCount; j++)
				{
					MaxIndex2 = DistanceOpt(BlockofMemory, PageNumofRef, j, i, PageNumRefCount);
					if(MaxIndex1 < MaxIndex2)
					{
						MaxIndex1 = MaxIndex2;
						k = j;
					}
				}
				ReplacePage = BlockofMemory[k];
				BlockofMemory[k] = PageNumofRef[i];
				OutputBlockofMemory(BlockofMemory, BlockCount, ReplacePage, PageNumofRef[i]);
			}
		}
		else
		{
			OutputBlockofMemory(BlockofMemory,BlockCount, -1, PageNumofRef[i]);
		}
	}

	printf("缺页次数为: %d\n", MissCount);
	printf("OPT缺页率为: %.3f\n", (float)MissCount / PageNumRefCount);
}

//先进先出页面置换算法FIFO
void Fifo(int *BlockofMemory,int *PageNumofRef,int BlockCount,int PageNumRefCount)
{
	int i;
	int ReplacePage;
	int ReplaceIndex = 0;
	int MissCount = 0;
	int EmptyBlockCount = BlockCount;

	printf("**********先进先出页面置换算法：**********\n");
	
	//输出页面引用串号
	OutputPageNumofRef(PageNumofRef,PageNumRefCount);

	for(i = 0; i < PageNumRefCount; i++)
	{
		if(!PageInBlockofMemory(PageNumofRef[i], BlockofMemory, BlockCount)) //页不在内存中
		{
			MissCount++;

			if(EmptyBlockCount > 0)
			{
				printf("----");
				BlockofMemory[BlockCount - EmptyBlockCount] = PageNumofRef[i];
				OutputBlockofMemory(BlockofMemory, BlockCount, -1, PageNumofRef[i]);
				EmptyBlockCount--;
			}
			else
			{
				printf("===");  // 这是缺页的
				ReplacePage = BlockofMemory[ReplaceIndex];
				BlockofMemory[ReplaceIndex] = PageNumofRef[i];
				ReplaceIndex = (ReplaceIndex + 1) % BlockCount;
				OutputBlockofMemory(BlockofMemory, BlockCount, ReplacePage, PageNumofRef[i]);
			}
		}
		else
			OutputBlockofMemory(BlockofMemory, BlockCount, -1, PageNumofRef[i]);
	}
	printf("缺页次数为：%d\n", MissCount);
	printf("FIFO缺页率为：%.3f\n", (float)MissCount / PageNumRefCount);
}

//最近最久未使用页面置换算法
void Lru(int *BlockofMemory, int *PageNumofRef, int BlockCount, int PageNumRefCount)
{
	int i;
	int MissCount = 0;
	int EmptyBlockCount = BlockCount;
	

	printf("************最近最久未使用页面置换算法：************\n");
	
	//输出页面引用串号
	OutputPageNumofRef(PageNumofRef, PageNumRefCount);

	for(i = 0; i < PageNumRefCount; i++)
	{
		if(!PageInBlockofMemory(PageNumofRef[i], BlockofMemory, BlockCount)) //页不在内存中
		{
			MissCount++;
			
			if(EmptyBlockCount > 0)
			{
				// printf("----");
				BlockofMemory[BlockCount - EmptyBlockCount] = PageNumofRef[i];
				OutputBlockofMemory(BlockofMemory, BlockCount, -1, PageNumofRef[i]);
				EmptyBlockCount--;
			}
			else
			{
				int k = 0;
				int j = i;
				int q;
				int l;
				int tag = 0;
				int ReplacePage;
	
				int *T_BlockofMemory;
				T_BlockofMemory = (int*)malloc(BlockCount * sizeof(int));
				ResetBlockofMemory(T_BlockofMemory, BlockCount);
				
				for(q = 0; q < i; q++){
					// printf(" +%d+ ", PageNumofRef[j-1]);
					j--;
					if(!PageInBlockofMemory(PageNumofRef[j], T_BlockofMemory, BlockCount)) {
						T_BlockofMemory[k++] = PageNumofRef[j];
						
						// printf(" -%d-%d~%d-%d-%d-%d-%d~ ",j,k,T_BlockofMemory[0],T_BlockofMemory[1],T_BlockofMemory[2],T_BlockofMemory[3],T_BlockofMemory[4]);
					}
					
					
					if(k == BlockCount && tag == 0) {
						ReplacePage = PageNumofRef[i];
						// printf("---%d---", PageNumofRef[j], PageNumofRef[i]);
						for(l = 0; l < BlockCount; l++)
							if(BlockofMemory[l] == PageNumofRef[j]) {
								BlockofMemory[l] = ReplacePage;
								tag = 1;
								break;
							}
					}
				}
				
				free(T_BlockofMemory);
				OutputBlockofMemory(BlockofMemory, BlockCount, ReplacePage, PageNumofRef[i]);
			}
			
				
		}
		else
			OutputBlockofMemory(BlockofMemory, BlockCount, -1, PageNumofRef[i]);
	}

	printf("缺页次数为：%d\n", MissCount);
	printf("LRU缺页率为：%.3f\n", (float)MissCount / PageNumRefCount);
}


