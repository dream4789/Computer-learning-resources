#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <stdio.h>
#include <stdlib.h>

int OutputBlockofMemory(int *BlockofMemory, int BlockCount, int ReplacePage, int PageNum);
void OutputPageNumofRef(int* PageNumofRef, int PageNumRefCount);
void ResetBlockofMemory(int *BlockofMemory, int BlockCount);
int PageInBlockofMemory(int PageNum, int *BlockofMemory, int BlockCount);
int DistanceOpt(int *BlockofMemory, int *PageNumofRef, int j, int i, int PageNumRefCount);
void Opt(int *BlockofMemory, int *PageNumofRef, int BlockCount, int PageNumRefCount);
void Fifo(int *BlockofMemory,int *PageNumofRef,int BlockCount,int PageNumRefCount);
void Lru(int *BlockofMemory, int *PageNumofRef, int BlockCount, int PageNumRefCount);


#endif /* CONSOLE_H_ */
