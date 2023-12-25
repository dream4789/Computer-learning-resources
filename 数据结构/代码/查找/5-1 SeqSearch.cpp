#include <stdio.h>
#include <conio.h>  // getch();

#define ARRAYLEN 8
int source[] = {69, 65, 90, 37, 92, 6, 28, 54};

int SeqSearch(int s[], int n, int key) {
    int i;
    for (i = 0; i < n && s[i] != key; i++);
    if (i < n)
        return i;
    else
        return -1;
}

int main() {
    int key, i, pos;
    printf("Please enter key words:");
    scanf("%d", &key);
    pos = SeqSearch(source, ARRAYLEN, key);
    printf("original data sheet:");
    for (i = 0; i < ARRAYLEN; i++)
        printf("%d ", source[i]);
    printf("\n");
    if (pos >= 0)
        printf("The search was successful, the key is at position %d of the array.\n", pos);
    else
        printf("Lookup failed!\n");
    getch();
    return 0;
}
