#include <stdio.h>
#include <stdlib.h>

typedef struct Tree {
    int data;             // ���������
    struct Tree *lchild;  // ����������ָ��
    struct Tree *rchild;  // ����������ָ��
} Tree, *BitTree;

BitTree CreateLink() {
    int data;
    int temp;
    BitTree T;

    scanf("%d", &data);  //	��������
    temp = getchar();    //	���տո�

    if (data == -1) {  //	����-1 ����˽ڵ��������������ݣ�Ҳ���ǲ������ݹ鴴��
        return NULL;
    } else {
        T = (BitTree) malloc(sizeof(Tree));  // �����ڴ�ռ�
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
    ShowHouXu(T->rchild);  // �ݹ����������
    printf("%d ", T->data);
}

int main() {
    BitTree S;
    printf("�������һ���ڵ������:\n");
    S = CreateLink();  // ���ܴ�����������ɵĸ��ڵ�
    printf("����������: \n");
    ShowXianXu(S);  // �������������

    printf("\n����������: \n");
    ShowZhongXu(S);  // �������������

    printf("\n����������: \n");
    ShowHouXu(S);  // �������������

    return 0;
}