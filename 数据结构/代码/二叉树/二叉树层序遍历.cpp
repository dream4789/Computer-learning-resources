#include <stdio.h>
#include <stdlib.h>

typedef struct Tree {
    int data;             // ���������
    struct Tree *lchild;  // ����������ָ��
    struct Tree *rchild;  // ����������ָ��
} Tree, *BitTree;

//	���нڵ㶨��
typedef struct QueueNode {
    BitTree data;
    struct QueueNode *next;
} QueueNode, *QueuePtr;

//	���ж���
typedef struct LinkQueue {
    QueuePtr front;  // ͷָ��
    QueuePtr rear;   // βָ��
} LinkQueue;

BitTree CreateLink() {
    int data;
    int temp;
    BitTree T;

    scanf("%d", &data);  //	��������
    temp = getchar();    //	���տո�

    if (data == -1) {  //	����-1 ����˽ڵ��������������ݣ�Ҳ���ǲ������ݹ鴴��
        return NULL;
    } else {
        T = (BitTree)malloc(sizeof(Tree));  // �����ڴ�ռ�
        T->data = data;  // �ѵ�ǰ��������ݴ��뵱ǰ�ڵ�ָ�����������
        printf("������%d��������: ", data);
        T->lchild = CreateLink();  // ��ʼ�ݹ鴴��������
        printf("������%d��������: ", data);
        T->rchild = CreateLink();  // ��ʼ����һ���ڵ���ұߵݹ鴴����������
        return T;                  // ���ظ��ڵ�
    }
}

//	�������
void ShowXianXu(BitTree T) {  // �������������
    if (T == NULL) {          // �ݹ�������NULL��������һ��ڵ�
        return;
    }
    printf("%d ", T->data);
    ShowXianXu(T->lchild);  // �ݹ����������
    ShowXianXu(T->rchild);  // �ݹ����������
}

//	�������
void ShowZhongXu(BitTree T) {  // �������������
    if (T == NULL) {           // �ݹ�������NULL��������һ��ڵ�
        return;
    }
    ShowZhongXu(T->lchild);  // �ݹ����������
    printf("%d ", T->data);
    ShowZhongXu(T->rchild);  // �ݹ����������
}

//	�������
void ShowHouXu(BitTree T) {  // �������������
    if (T == NULL) {         // �ݹ�������NULL��������һ��ڵ�
        return;
    }
    ShowHouXu(T->lchild);  // �ݹ����������
    ShowHouXu(T->rchild);
    // �ݹ����������
    printf("%d ", T->data);
}

//	��ʼ������
void InitQueue(LinkQueue *Q) {
    Q->front = Q->rear = (QueuePtr) malloc(sizeof(QueueNode));
    if (!Q->front)
        exit(0);
    Q->front->next = NULL;
}

//	�ж϶����Ƿ�Ϊ��
int IsEmpty(LinkQueue Q) {
    if (Q.front == Q.rear)
        return 1;
    else
        return 0;
}

//	���
void EnQueue(LinkQueue *Q, BitTree x) {
    QueuePtr p;
    p = (QueuePtr) malloc(sizeof(QueueNode));
    if (!p)
        exit(0);
    p->data = x;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
}

//	����
BitTree DeQueue(LinkQueue *Q) {
    QueuePtr p;
    BitTree u;
    if (Q->front == Q->rear)
        exit(0);
    p = Q->front->next;
    u = p->data;
    Q->front->next = p->next;
    if (Q->rear == p)
        Q->rear = Q->front;
    free(p);
    return u;
}

//	�������Ĳ������
void ShowCengXu(BitTree T) {
    LinkQueue Q;
    InitQueue(&Q);  // ��ʼ������
    BitTree p = T;
    EnQueue(&Q, p);  // ���ڵ����

    while (!IsEmpty(Q)) {           // ���в�Ϊ��ʱ����ѭ��
        p = DeQueue(&Q);            // ȡ������Ԫ��
        printf("%d ", p->data);     // �������Ԫ��
        if (p->lchild != NULL) {    // �������������β
            EnQueue(&Q, p->lchild);
        }
        if (p->rchild != NULL) {    // �������������β
            EnQueue(&Q, p->rchild);
        }
    }
}

int tu() {
    printf("      3\n");
    printf("    /   \\\n");
    printf("   2     5\n");
    printf("  / \\   / \\\n");
    printf(" 1   4 6   8\n");
    printf("      \\\n");
    printf("       7\n");
    return 0;
}


int main() {
    tu();
    BitTree S;
    printf("�������һ���ڵ������:\n");
    S = CreateLink();  // ���ܴ�����������ɵĸ��ڵ�

    printf("����������: \n");
    ShowXianXu(S);

    printf("\n����������: \n");
    ShowZhongXu(S);

    printf("\n����������: \n");
    ShowHouXu(S);

    printf("\n����������: \n");
    ShowCengXu(S);

    return 0;
}
/*

      3
    /   \
   2     5
  / \   / \
 1   4 6   8
      \
       7

�������һ���ڵ������:
3
������3��������:2
 ������2��������:1
 ������1��������:-1
 ������1��������:-1
 ������2��������:4
 ������4��������:-1
 ������4��������:-1

������3��������:5
 ������5��������:6
 ������6��������:-1
 ������6��������:7
 ������7��������:-1
 ������7��������:-1
 ������5��������:8

������8��������:-1
 ������8��������:-1
 ����������:
3 2 1 4 5 6 7 8
����������:
1 2 4 3 6 7 5 8
����������:
1 4 2 7 6 8 5 3
����������:
3 2 5 1 4 6 8 7
Process finished with exit code 0

 */