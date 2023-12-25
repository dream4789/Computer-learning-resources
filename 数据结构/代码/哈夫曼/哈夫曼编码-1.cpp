#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000

typedef struct {
    char *code;    /* 编码 */
    char leaf;     /* 叶子字符 */
    int length;    /* 编码长度 */
} CodeType;

typedef struct {
    int weight;    /* 权重 */
    int lchild;    /* 左孩子 */
    int rchild;    /* 右孩子 */
    int parent;    /* 父节点 */
    char ch;       /* 叶子字符 */
} Htnode;

void selectsort(Htnode huftree[], int n, int *s1, int *s2) {
    int i, j;
    int min1, min2;
    min1 = min2 = MAXN;

    for (i = 1; i <= n; i++) {
        if (huftree[i].parent == -1 && huftree[i].weight < min1) {
            min2 = min1;
            min1 = huftree[i].weight;
            *s2 = *s1;
            *s1 = i;
        } else if (huftree[i].parent == -1 && huftree[i].weight < min2) {
            min2 = huftree[i].weight;
            *s2 = i;
        }
    }
}

void Hufcoding(Htnode huftree[], CodeType cd[], int w[], int n) {
    int i, k, s1, s2, m, f, c, sum;
    char temp[MAXN];  /* 暂存叶子编码字符串，最后需要转置 */
    m = 2 * n - 1; /* 计算哈夫曼树的结点总数 */
    /* 初始化每个叶子结点自成一棵树 */
    for (i = 1; i <= n; i++) {
        huftree[i].weight = w[i - 1];
        huftree[i].lchild = huftree[i].rchild = huftree[i].parent = -1;
        huftree[i].ch = 'a' + i - 1; /* 随机赋予字符，可根据实际情况修改 */
    }
    /* 初始化非叶子结点 */
    for (i = n + 1; i <= m; i++) {
        huftree[i].weight = -1;
        huftree[i].lchild = huftree[i].rchild = huftree[i].parent = -1;
    }
    /* 生成n-1个非叶子结点的循环 */
    for (i = 1; i <= n - 1; i++) {
        selectsort(huftree, n + i - 1, &s1, &s2);
        /* 对数组huftree[1..n+i-1]中无双亲的结点权值进行排序，s1,s2将是
           无双亲且权重最小的两个结点下标 */
        sum = huftree[s1].weight + huftree[s2].weight;
        huftree[n + i].weight = sum;
        huftree[s1].parent = huftree[s2].parent = n + i;
        huftree[n + i].lchild = s1;
        huftree[n + i].rchild = s2;
    }
    /* 开始求每个叶子结点的编码 */
    for (i = 1; i <= n; i++) {
        c = 0;
        for (k = i, f = huftree[i].parent; f != -1; k = f, f = huftree[f].parent)
            if (huftree[f].lchild == k) {
                temp[c] = '0';
                c++;
            } else {
                temp[c] = '1';
                c++;
            }                               /*左分枝是0右分枝是1 */
        cd[i].code = (char *)malloc(c + 1); /*产生存储编码的空间*/
        cd[i].code[c] = '\0';
        c--;
        k = 0;
        while (c >= 0) {
            cd[i].code[k++] = temp[c--]; // 将temp转置到cd中
        }
        cd[i].leaf = huftree[i].ch;
        cd[i].length = k;
    }
}

int main() {
    int i, n;
    Htnode huftree[MAXN];
    CodeType cd[MAXN];
    int w[MAXN] = {5, 9, 12, 13, 16, 45};
    n = 6;

    Hufcoding(huftree, cd, w, n);
    // 字符    权值    编码
    printf("Character   Weight   Encoding\n");
    for (i = 1; i <= n; i++) {
        printf("%4c   %8d    %8s\n", cd[i].leaf, w[i - 1], cd[i].code);
    }

    return 0;
}

/*

在这个程序中，我们首先定义了两个结构体：CodeType用于存储编码信息，Htnode用于表示哈夫曼树的节点。
 然后，我们实现了一个用于选择排序的函数selectsort和一个用于生成哈夫曼编码的函数Hufcoding。

在main函数中，我们定义了一些测试数据，包括字符集、字符出现频率和字符集大小。
 然后，我们调用Hufcoding函数来生成并打印每个叶子结点的哈夫曼编码。
 最后，我们通过循环遍历cd数组来打印每个叶子结点的字符、权重和编码。
 */