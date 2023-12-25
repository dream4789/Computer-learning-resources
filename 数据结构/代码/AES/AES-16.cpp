//
// Created by xulon on 2023/6/25.
//
//#include<map>
//#include<queue>
//#include<stack>
//#include<cmath>
//#include<string>
#include<cstdio>
#include<cstring>
//#include<cstdlib>
//#include<iostream>
//#include<algorithm>

using namespace std;
const int maxn = 1e4 + 10;
const int N = 100;
char mingwen[maxn];///����
char miyao[maxn];///��Կ
char mingwenhex[N][N];///���ĵ�ʮ������
char mingjuzhen[N][N][N];///���ľ���
char miyaohex[N][N];///��Կ��ʮ������
char miyaojuzhen[N][N][N];///��Կ����
char hangzhong[N][N][N];///����λ���н�
char K[N][N][N];///44����Կ
char key[N][N][N][N];///10������Կ
char nexts[N][N][N];///������һ������
char miwenjuzhen[N][N][N];///���ľ���
char minwennexts[N][N][N];///���ĵ���һ������
char zhong[N][N][N];

void menu();

void jiami();

static const int s[16][16] = {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab,
                              0x76,
                              0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72,
                              0xc0,
                              0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31,
                              0x15,
                              0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2,
                              0x75,
                              0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f,
                              0x84,
                              0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58,
                              0xcf,
                              0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f,
                              0xa8,
                              0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3,
                              0xd2,
                              0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19,
                              0x73,
                              0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b,
                              0xdb,
                              0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4,
                              0x79,
                              0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae,
                              0x08,
                              0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b,
                              0x8a,
                              0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d,
                              0x9e,
                              0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28,
                              0xdf,
                              0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb,
                              0x16
};
static const int s_1[16][16] = {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3,
                                0xd7, 0xfb,
                                0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde,
                                0xe9, 0xcb,
                                0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa,
                                0xc3, 0x4e,
                                0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b,
                                0xd1, 0x25,
                                0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65,
                                0xb6, 0x92,
                                0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d,
                                0x9d, 0x84,
                                0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3,
                                0x45, 0x06,
                                0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13,
                                0x8a, 0x6b,
                                0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4,
                                0xe6, 0x73,
                                0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75,
                                0xdf, 0x6e,
                                0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18,
                                0xbe, 0x1b,
                                0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd,
                                0x5a, 0xf4,
                                0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80,
                                0xec, 0x5f,
                                0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9,
                                0x9c, 0xef,
                                0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53,
                                0x99, 0x61,
                                0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21,
                                0x0c, 0x7d
};
///�л�����õ��ľ���
static const int a[4][4] = {2, 3, 1, 1,
                            1, 2, 3, 1,
                            1, 1, 2, 3,
                            3, 1, 1, 2
};
static const int a_1[4][4] = {0x0e, 0x0b, 0x0d, 0x09,
                              0x09, 0x0e, 0x0b, 0x0d,
                              0x0d, 0x09, 0x0e, 0x0b,
                              0x0b, 0x0d, 0x09, 0x0e
};
static const int Rcon[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

///ת��Ϊ16���ƴ�
///��֤��ȷ
void changebit() {
    for (int i = 0; i < strlen(miyao); i++)
        sprintf(miyaohex[i], "%X", miyao[i]);
    int l = 0;///����Կת��Ϊ4*4����
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            strcpy(miyaojuzhen[j][i], miyaohex[l++]);
        }
    }
    for (int i = 0; i < strlen(mingwen); i++)
        sprintf(mingwenhex[i], "%X", mingwen[i]);
    l = 0;///������ת��Ϊ4*4����
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            strcpy(mingjuzhen[j][i], mingwenhex[l++]);
        }
    }
}

///�ֽڴ���
///��֤��ȷ
void bitchange() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int h = 0, l = 0;
            if (strlen(mingjuzhen[i][j]) == 1) {
                h = 0;
                if (mingjuzhen[i][j][0] >= 'A' && mingjuzhen[i][j][0] <= 'F')
                    l = mingjuzhen[i][j][0] - 'A' + 10;
                else if (mingjuzhen[i][j][0] >= 'a' && mingjuzhen[i][j][0] <= 'f')
                    l = mingjuzhen[i][j][0] - 'a' + 10;
                else
                    l = mingjuzhen[i][j][0] - '0';
            } else {
                if (mingjuzhen[i][j][0] >= 'A' && mingjuzhen[i][j][0] <= 'F')
                    h = mingjuzhen[i][j][0] - 'A' + 10;
                else if (mingjuzhen[i][j][0] >= 'a' && mingjuzhen[i][j][0] <= 'f')
                    h = mingjuzhen[i][j][0] - 'a' + 10;
                else
                    h = mingjuzhen[i][j][0] - '0';
                if (mingjuzhen[i][j][1] >= 'A' && mingjuzhen[i][j][1] <= 'F')
                    l = mingjuzhen[i][j][1] - 'A' + 10;
                else if (mingjuzhen[i][j][1] >= 'a' && mingjuzhen[i][j][1] <= 'f')
                    l = mingjuzhen[i][j][1] - 'a' + 10;
                else
                    l = mingjuzhen[i][j][1] - '0';
            }
            if (h > 16)
                h -= 7;
            if (l > 16)
                l -= 7;
            int temp = s[h][l];
            char ss[10];
            sprintf(ss, "%X", temp);
            strcpy(mingjuzhen[i][j], ss);
        }
    }
}

///����λ
///��֤��ȷ
void shiftrows() {
    for (int i = 0; i < 4; i++) {
        strcpy(hangzhong[0][i], mingjuzhen[0][i]);
    }
    for (int i = 1; i < 4; i++) ///�ӵڶ��п�ʼ��λ����һ�в���,��i��ֵͬʱΪλ��ƫ����ֵ��
    {
        for (int j = 0; j < 4; j++) {
            strcpy(hangzhong[i][j], mingjuzhen[i][(j + i) % 4]);
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            strcpy(mingjuzhen[i][j], hangzhong[i][j]);
        }
    }
}

///�õ��˷������֤��ȷ
int GF(int n1, int n2) {
    int A[32], b[32], s[32];
    memset(A, 0, sizeof(A));
    memset(b, 0, sizeof(b));
    memset(s, 0, sizeof(s));
    int cnt = 0;
    while (n1)///ת��Ϊ������
    {
        s[cnt++] = n1 % 2;
        n1 /= 2;
    }
    A[1] = 0x01, b[1] = n2;
    for (int i = 2; i <= 8; i++)
        A[i] = A[i - 1] << 1;///�õ�0x01 0x02 0x04 0x08 0x10 0x20 0x40 0x80
    for (int i = 2; i <= 8; i++) {
        if (b[i - 1] & 0x80)///������ΪΪ1�ͶԲ���Լ����ʽȡģ,����ֱ������
            b[i] = ((b[i - 1] << 1) ^ 0x1B);
        else
            b[i] = b[i - 1] << 1;
        b[i] &= 0xFF;///ֱ��ȡ����λ
    }
    int hex = 0x00;
    for (int i = 7; i >= 0; i--) {
        if (s[i] == 1)///�������Ƶ���һλΪ1��ʱ��������
            hex ^= b[i + 1];
    }
    return hex;
}

///�л��2�İ˴η��������ϵĳ˷���ӷ�
///��֤��ȷ
void mixcolunmns() {
    int c[N][N];
    memset(c, 0, sizeof(c));
    for (int k = 0; k < 4; k++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int n1 = a[k][j], n2 = 0;
                if (strlen(mingjuzhen[j][i]) == 2) {
                    if (mingjuzhen[j][i][0] >= 'A' && mingjuzhen[j][i][0] <= 'F')
                        n2 += ((mingjuzhen[j][i][0] - 55) * 16);
                    else
                        n2 += (mingjuzhen[j][i][0] - '0') * 16;
                    if (mingjuzhen[j][i][1] >= 'A' && mingjuzhen[j][i][1] <= 'F')
                        n2 += ((mingjuzhen[j][i][1] - 55));
                    else
                        n2 += ((mingjuzhen[j][i][1] - '0'));
                } else {
                    if (mingjuzhen[j][i][0] >= 'A' && mingjuzhen[j][i][0] <= 'F')
                        n2 += ((mingjuzhen[j][i][0] - 55));
                    else
                        n2 += (mingjuzhen[j][i][0] - '0');
                }
                int hexx = GF(n1, n2);///�õ���˵Ľ��
                c[k][i] ^= hexx;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            char temp[10];
            memset(temp, 0, sizeof(temp));
            sprintf(temp, "%X", c[i][j]);
            strcpy(mingjuzhen[i][j], temp);
        }
    }
}

///��Կ��չ
void tuozhan() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            strcpy(K[i][j], miyaojuzhen[j][i]);
        }
    }
    for (int i = 4; i < 44; i++) {
        for (int j = 0; j < 4; j++) {
            int n1 = 0, n2 = 0;
            if (strlen(K[i - 4][j]) == 2)///K[I-4]Ϊ����
            {
                if (K[i - 4][j][0] >= 'A' && K[i - 4][j][0] <= 'F')
                    n1 += ((K[i - 4][j][0] - 55) * 16);
                else if (K[i - 4][j][0] >= 'a' && K[i - 4][j][0] <= 'f')
                    n1 += ((K[i - 4][j][0] - 'a' + 10) * 16);
                else
                    n1 += (K[i - 4][j][0] - '0') * 16;
                if (K[i - 4][j][1] >= 'A' && K[i - 4][j][1] <= 'F')
                    n1 += ((K[i - 4][j][1] - 55));
                else if (K[i - 4][j][1] >= 'a' && K[i - 4][j][1] <= 'f')
                    n1 += ((K[i - 4][j][1] - 'a' + 10));
                else
                    n1 += ((K[i - 4][j][1] - '0'));
            } else {
                if (K[i - 4][j][0] >= 'A' && K[i - 4][j][0] <= 'F')
                    n1 += ((K[i - 4][j][0] - 55));
                else if (K[i - 4][j][0] >= 'a' && K[i - 4][j][0] <= 'f')
                    n1 += ((K[i - 4][j][0] - 'a' + 10));
                else
                    n1 += (K[i - 4][j][0] - '0');
            }
            if (i % 4 == 0)///���Ϊ4�ı�����;Ki=Ki-4^T(Ki-1)
            {
                ///��ȡT��Ki-1��
                int h = 0, l = 0;
                if (strlen(K[i - 1][(j + 1) % 4]) == 1) {
                    h = 0;
                    if (K[i - 1][(j + 1) % 4][0] >= 'A' && K[i - 1][(j + 1) % 4][0] <= 'F')
                        l = K[i - 1][(j + 1) % 4][0] - 'A' + 10;
                    else if (K[i - 1][(j + 1) % 4][0] >= 'a' && K[i - 1][(j + 1) % 4][0] <= 'f')
                        l = K[i - 1][(j + 1) % 4][0] - 'a' + 10;
                    else
                        l = K[i - 1][(j + 1) % 4][0] - '0';
                } else {
                    if (K[i - 1][(j + 1) % 4][0] >= 'A' && K[i - 1][(j + 1) % 4][0] <= 'F')
                        h = K[i - 1][(j + 1) % 4][0] - 'A' + 10;
                    else if (K[i - 1][(j + 1) % 4][0] >= 'a' && K[i - 1][(j + 1) % 4][0] <= 'f')
                        h = K[i - 1][(j + 1) % 4][0] - 'a' + 10;
                    else
                        h = K[i - 1][(j + 1) % 4][0] - '0';
                    if (K[i - 1][(j + 1) % 4][1] >= 'A' && K[i - 1][(j + 1) % 4][1] <= 'F')
                        l = K[i - 1][(j + 1) % 4][1] - 'A' + 10;
                    else if (K[i - 1][(j + 1) % 4][1] >= 'a' && K[i - 1][(j + 1) % 4][1] <= 'f')
                        l = K[i - 1][(j + 1) % 4][1] - 'a' + 10;
                    else
                        l = K[i - 1][(j + 1) % 4][1] - '0';
                }
                if (h > 16)
                    h -= 7;
                if (l > 16)
                    l -= 7;
                int temps = s[h][l];///�õ�s���е����
                ///��ȷ
                int rcon = Rcon[i / 4 - 1];///����ֱ�ӵõ�
                if (j == 0)
                    n2 = temps ^ rcon;///���õ�ÿһ������
                else
                    n2 = temps;
                ///�õ���T������K[i-4]���
            } else ///Ki=Ki-4^Ki-1
            {
                if (strlen(K[i - 1][j]) == 2) {
                    if (K[i - 1][j][0] >= 'A' && K[i - 1][j][0] <= 'F')
                        n2 += ((K[i - 1][j][0] - 55) * 16);
                    else
                        n2 += (K[i - 1][j][0] - '0') * 16;
                    if (K[i - 1][j][1] >= 'A' && K[i - 1][j][1] <= 'F')
                        n2 += ((K[i - 1][j][1] - 55));
                    else
                        n2 += ((K[i - 1][j][1] - '0'));
                } else {
                    if (K[i - 1][j][0] >= 'A' && K[i - 1][j][0] <= 'F')
                        n2 += ((K[i - 1][j][0] - 55));
                    else
                        n2 += (K[i - 1][j][0] - '0');
                }
            }
            int n3 = n1 ^ n2;///������
            char temp[10];
            sprintf(temp, "%X", n3);
            strcpy(K[i][j], temp);
        }
    }
}

///�õ�����Կ��֤��ȷ
void keychoice() {
    tuozhan();///��֤��ȷ���õ�44����չ��Կ
    int l = 0;
    for (int i = 0; i < 44; i++) {
        if (i % 4 == 0 && i != 0)
            l++;
        for (int j = 0; j < 4; j++) {
            strcpy(key[l][j][(i) % 4], K[i][j]);
        }
    }
}

///����Կ��
void addroundkey(int n, int flag) {
    memset(zhong, 0, sizeof(zhong));
    if (flag == 1) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                strcpy(zhong[i][j], mingjuzhen[i][j]);
            }
        }
    } else {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                strcpy(zhong[i][j], miwenjuzhen[i][j]);
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int n1 = 0, n2 = 0;
            if (strlen(zhong[i][j]) == 2) {
                if (zhong[i][j][0] >= 'A' && zhong[i][j][0] <= 'F')
                    n1 += ((zhong[i][j][0] - 55) * 16);
                else
                    n1 += (zhong[i][j][0] - '0') * 16;
                if (zhong[i][j][1] >= 'A' && zhong[i][j][1] <= 'F')
                    n1 += ((zhong[i][j][1] - 55));
                else
                    n1 += ((zhong[i][j][1] - '0'));
            } else {
                if (zhong[i][j][0] >= 'A' && zhong[i][j][0] <= 'F')
                    n1 += ((zhong[i][j][0] - 55));
                else
                    n1 += (zhong[i][j][0] - '0');
            }
            if (strlen(key[n][i][j]) == 2) {
                if (key[n][i][j][0] >= 'A' && key[n][i][j][0] <= 'F')
                    n2 += ((key[n][i][j][0] - 55) * 16);
                else
                    n2 += (key[n][i][j][0] - '0') * 16;
                if (key[n][i][j][1] >= 'A' && key[n][i][j][1] <= 'F')
                    n2 += ((key[n][i][j][1] - 55));
                else
                    n2 += ((key[n][i][j][1] - '0'));
            } else {
                if (key[n][i][j][0] >= 'A' && key[n][i][j][0] <= 'F')
                    n2 += ((key[n][i][j][0] - 55));
                else
                    n2 += (key[n][i][j][0] - '0');
            }
            int n3 = n2 ^ n1;
            sprintf(nexts[i][j], "%X", n3);///�õ���һ�ε�����
        }
    }
}

void duqu() {
    // ��ӭʹ�ü����㷨
    printf("Welcome to Encryption Algorithms!\n\n");
    while (1) {
        // ������128bit��Կ��16λ�ַ�����
        printf("Please enter a 128bit key which is a 16-bit string:\n\n");
        scanf("%s", miyao);
        int l = strlen(miyao);
        if (l % 16)
            // ��Կ���ȴ���������������Կ��
            printf("The key length is wrong, please re-enter the key:\n\n");
        else
            break;
    }
    getchar();
    while (1) {
        // ������128bit���ļ�16λ�����ַ�����
        printf("\nPlease enter 128bit plaintext or 16bit plaintext string:\n");
        scanf("%s", mingwen);
        int l = strlen(mingwen);
        if (l % 16)
            // ���ĳ��ȴ����������������ģ�
            printf("The plaintext length is wrong, please re-enter the plaintext:\n\n");
        else
            break;
    }
}

///�����㷨
void jiami() {

    changebit();///�õ�����

    // �������������ʮ�����Ʊ�ʾΪ:
    printf("The plaintext hexadecimal representation you entered is:\n\n");
    for (int i = 0; i < 16; i++)
        printf("%s ", mingwenhex[i]);
    printf("\n");
    keychoice();///�õ�����Կ
    addroundkey(0, 1);
    for (int ii = 0; ii < 4; ii++) {
        for (int jj = 0; jj < 4; jj++) {
            strcpy(mingjuzhen[ii][jj], nexts[ii][jj]);
        }
    }
    for (int i = 1; i < 10; i++) {
        bitchange();///��ȷ
        shiftrows();///��ȷ
        mixcolunmns();///��ȷ
        addroundkey(i, 1);///��ȷ
        ///����һ�ֵ������Ϊ��һ�ֵ�����
        for (int ii = 0; ii < 4; ii++) {
            for (int jj = 0; jj < 4; jj++) {
                strcpy(mingjuzhen[ii][jj], nexts[ii][jj]);
            }
        }
    }
    ///���һ�����л��
    bitchange();
    shiftrows();
    addroundkey(10, 1);
    printf("\n");
    // ������ɵõ����ģ�
    printf("The encryption is completed to get the ciphertext:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            strcpy(mingjuzhen[i][j], nexts[i][j]);
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            printf("%s ", mingjuzhen[j][i]);
    }
    printf("\n\n");
}

///������λ��֤��ȷ
void invshiftrows() {
    for (int i = 0; i < 4; i++) {
        strcpy(hangzhong[0][i], miwenjuzhen[0][i]);
    }
    for (int i = 1; i < 4; i++) ///�ӵڶ��п�ʼ��λ����һ�в���,��i��ֵͬʱΪλ��ƫ����ֵ��
    {
        for (int j = 0; j < 4; j++) {
            strcpy(hangzhong[i][j], miwenjuzhen[i][(j - i + 4) % 4]);
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            strcpy(miwenjuzhen[i][j], hangzhong[i][j]);
        }
    }
}

///���ֽڴ�����֤��ȷ
void insubbytes() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int h = 0, l = 0;
            if (strlen(miwenjuzhen[i][j]) == 1) {
                h = 0;
                if (miwenjuzhen[i][j][0] >= 'A' && miwenjuzhen[i][j][0] <= 'F')
                    l = miwenjuzhen[i][j][0] - 'A' + 10;
                else if (miwenjuzhen[i][j][0] >= 'a' && miwenjuzhen[i][j][0] <= 'f')
                    l = miwenjuzhen[i][j][0] - 'a' + 10;
                else
                    l = miwenjuzhen[i][j][0] - '0';
            } else {
                if (miwenjuzhen[i][j][0] >= 'A' && miwenjuzhen[i][j][0] <= 'F')
                    h = miwenjuzhen[i][j][0] - 'A' + 10;
                else if (miwenjuzhen[i][j][0] >= 'a' && miwenjuzhen[i][j][0] <= 'f')
                    h = miwenjuzhen[i][j][0] - 'a' + 10;
                else
                    h = miwenjuzhen[i][j][0] - '0';
                if (miwenjuzhen[i][j][1] >= 'A' && miwenjuzhen[i][j][1] <= 'F')
                    l = miwenjuzhen[i][j][1] - 'A' + 10;
                else if (miwenjuzhen[i][j][1] >= 'a' && miwenjuzhen[i][j][1] <= 'f')
                    l = miwenjuzhen[i][j][1] - 'a' + 10;
                else
                    l = miwenjuzhen[i][j][1] - '0';
            }
            if (h > 16)
                h -= 7;
            if (l > 16)
                l -= 7;
            int temp = s_1[h][l];
            char ss[10];
            sprintf(ss, "%X", temp);
            strcpy(miwenjuzhen[i][j], ss);
        }
    }
}

///���л��
void inmixcolumns() {
    int c[N][N];
    memset(c, 0, sizeof(c));
    for (int k = 0; k < 4; k++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int n1 = a_1[k][j], n2 = 0;
                if (strlen(miwenjuzhen[j][i]) == 2) {
                    if (miwenjuzhen[j][i][0] >= 'A' && miwenjuzhen[j][i][0] <= 'F')
                        n2 += ((miwenjuzhen[j][i][0] - 55) * 16);
                    else
                        n2 += (miwenjuzhen[j][i][0] - '0') * 16;
                    if (miwenjuzhen[j][i][1] >= 'A' && miwenjuzhen[j][i][1] <= 'F')
                        n2 += ((miwenjuzhen[j][i][1] - 55));
                    else
                        n2 += ((miwenjuzhen[j][i][1] - '0'));
                } else {
                    if (miwenjuzhen[j][i][0] >= 'A' && miwenjuzhen[j][i][0] <= 'F')
                        n2 += ((miwenjuzhen[j][i][0] - 55));
                    else
                        n2 += (miwenjuzhen[j][i][0] - '0');
                }
                int hexx = GF(n1, n2);///�õ���˵Ľ��
                c[k][i] ^= hexx;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            char temp[10];
            memset(temp, 0, sizeof(temp));
            sprintf(temp, "%X", c[i][j]);
            strcpy(miwenjuzhen[i][j], temp);
        }
    }
}

///���ܹ���
void jiemi() {
    ///�����ܲ��������ĸ��Ƶ����ĵ�16���ƾ�����
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            strcpy(miwenjuzhen[i][j], nexts[i][j]);
        }
    }
    ///��һ��������Կ��
    addroundkey(10, 2);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            strcpy(miwenjuzhen[i][j], nexts[i][j]);
        }
    }
    ///�ڶ�����10��ѭ������
    for (int ii = 9; ii >= 1; ii--) {
        invshiftrows(); ///����λ
        insubbytes();///���ֽڴ���
        addroundkey(ii, 2);///������Կ��
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                strcpy(miwenjuzhen[i][j], nexts[i][j]);
            }
        }
        inmixcolumns();///���л��
    }
    invshiftrows();
    insubbytes();
    addroundkey(0, 2);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            strcpy(miwenjuzhen[i][j], nexts[j][i]);
        }
    }
    // ������ɵõ����ģ�
    printf("After the decryption is completed, the plaintext is obtained:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%s ", miwenjuzhen[i][j]);
        }
    }
    printf("\n");
}

int main() {
    duqu();
    jiami();
    jiemi();
    return 0;
}

/*

Welcome to Encryption Algorithms!

Please enter a 128bit key which is a 16-bit string:

1111111111111111

Please enter 128bit plaintext or 16bit plaintext string:
abcdefghijklmnop
The plaintext hexadecimal representation you entered is:

61 62 63 64 65 66 67 68 69 6A 6B 6C 6D 6E 6F 70

The encryption is completed to get the ciphertext:
B9 9B 2B 71 25 C3 28 5C 2E 57 D5 43 97 41 17 3E

After the decryption is completed, the plaintext is obtained:
61 62 63 64 65 66 67 68 69 6A 6B 6C 6D 6E 6F 70

Process finished with exit code 0

 */