#include <windows.h>
#include <iostream>
#include <winbase.h>
#include <stdlib.h>

using namespace std;

unsigned short ReaderID = 0;    //���߱��
unsigned short WriterID = 0;    //д�߱��

int nReaders = 0; // ��ǰ������
bool p_ccontinue = true;      //���Ƴ������
	
// ���廥�������ź���
HANDLE mutex, wMutex;
DWORD WINAPI Reader(LPVOID);    //�����߳�
DWORD WINAPI Writer(LPVOID);    //д���߳�


// ��ʼʱ��
int T_R = 0;
int T_W = 0;
int time_R[5] = {1,2,6,7,8};
float time_W[2] = {2,4.5};

double start;
double end;


int main() {
	srand(time(NULL));

    // ��ʼ���������Ͷ�д��
    mutex = CreateMutex(NULL, FALSE, NULL);
    wMutex = CreateSemaphore(NULL, 1, 1, NULL);


    const unsigned short READER_COUNT = 5;  //���ߵĸ���
    const unsigned short WRITER_COUNT = 2;  //д�ߵĸ���
    
    //�ܵ��߳���
    const unsigned short THREADS_COUNT = READER_COUNT+WRITER_COUNT;

	HANDLE hThreads[THREADS_COUNT]; //���̵߳�handle
    DWORD readerID[READER_COUNT]; //���ߵı�ʶ��
    DWORD writerID[WRITER_COUNT]; //д���̵߳ı�ʶ��
    
    start = GetTickCount();

    // ���������߳�
    for (int i = 0; i < READER_COUNT; i++) {
		hThreads[i]=CreateThread(NULL,0,Reader,NULL,0,&readerID[i]);
        if (hThreads[i]==NULL) return -1;
    }

    // ����д���߳�
    for (int j = 0; j < WRITER_COUNT; j++) {
		hThreads[READER_COUNT+j]=CreateThread(NULL,0,Writer,NULL,0,&writerID[j]);
        if (hThreads[j]==NULL) return -1;
    }
    
	while(p_ccontinue){
        if(getchar()){ //���س�����ֹ��������
            p_ccontinue = false;
        }
    }

	// �ȴ������߳̽���
    WaitForMultipleObjects(THREADS_COUNT, hThreads, TRUE, INFINITE);

    // �رվ��
	for (int k = 0; k < THREADS_COUNT; k++) CloseHandle(hThreads[k]);

	// �رջ������Ͷ�д��
    CloseHandle(mutex);
    CloseHandle(wMutex);

    return 0;
}

void Read()
{
    int a = rand()%500+500;  // 0.5-1
    std::cout << "READ..STAR.." << a << ".." << GetTickCount() - start << ".." << ++ReaderID << std::endl;
    Sleep(a);
    std::cout << "READ..END.." << ReaderID << ".." << GetTickCount() - start << std::endl;
    //if (ReaderID == 5) ReaderID=0;
}

void Write()
{
    int a = rand()%1000+1000;  // 1-2
    std::cout << "WRITER..STAR.." << a << ".." << GetTickCount() - start << ".." << ++WriterID << std::endl;
    Sleep(a);
    std::cout << "WRITER..END.." << WriterID << ".." << GetTickCount() - start << std::endl;
    //if (WriterID == 2) WriterID=0;
}

// ��������̺߳���
DWORD WINAPI Reader(LPVOID lpParam) {

	// if(T_R==5) T_R=0;
	// Sleep(time_R[T_R++]*1000);
    while (p_ccontinue) {
    
    	if(T_R==5) T_R=0;
    	Sleep(time_R[T_R++]*1000);
    
        WaitForSingleObject(mutex, INFINITE);
        if (nReaders == 0) WaitForSingleObject(wMutex, INFINITE);
        nReaders++;
        ReleaseMutex(mutex);
		
		Read();

        WaitForSingleObject(mutex, INFINITE);
        nReaders--;
        if (nReaders == 0) ReleaseSemaphore(wMutex, 1, NULL);
        ReleaseMutex(mutex);

        // Sleep(rand() % 3000);
    }

    return 0;
}

// ����д���̺߳���
DWORD WINAPI Writer(LPVOID lpParam) {

	//if(T_R==2) T_R=0;
	// Sleep(time_W[T_W++]*1000);
    while (p_ccontinue) {
    
    	if(T_W==2) T_W=0;
    	Sleep(time_W[T_W++]*1000);

        WaitForSingleObject(wMutex, INFINITE);
		Write();
        ReleaseSemaphore(wMutex, 1, NULL);
        
        // Sleep(rand() % 3000);
    }

    return 0;
}