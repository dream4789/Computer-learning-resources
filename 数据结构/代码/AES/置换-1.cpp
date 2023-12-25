#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 10000
#define MAX_ROW 1000
#define MAX_COL 1000

void clear_console() {
    system("cls");
}

void show_menu() {
    printf("Welcome to the permutation cipher conversion program!\n");
    printf("Please select the function to use:\n");
    printf("1: Encryption\n2: Decryption\n0: Terminate the program\n\n");
}

int get_user_input() {
    int choice;
    printf("Please enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

int get_key() {
    int key;
    printf("Please enter the numeric key (0 < key < 10): ");
    scanf("%d", &key);
    return key;
}

void get_plaintext(char *plaintext) {
    printf("Please enter plaintext: ");
    scanf("%s", plaintext);
}

void get_ciphertext(char *ciphertext) {
    printf("Please enter ciphertext: ");
    getchar();
    gets(ciphertext);
}

void print_matrix(char matrix[MAX_ROW][MAX_COL], int row_num, int col_num) {
    for (int i = 1; i <= row_num; i++) {
        for (int j = 1; j <= col_num; j++) {
            printf("%c", matrix[i][j]);
        }
    }
}

void permute_encrypt(char *plaintext, char *ciphertext, int key) {
    int len = strlen(plaintext);
    int row_num = (len % key == 0) ? len / key : (len / key + 1);
    char matrix[MAX_ROW][MAX_COL] = {0};
    int index = 0;
    for (int j = 1; j <= key; j++) {
        for (int i = 1; i <= row_num; i++) {
            if (index < len) {
                matrix[i][j] = plaintext[index++];
            } else {
                matrix[i][j] = ' ';
            }
        }
    }
    print_matrix(matrix, row_num, key);
    index = 0;
    for (int i = 1; i <= key; i++) {
        int col_idx = -1;
        for (int j = 1; j <= key; j++) {
            if (i == key) {
                col_idx = j;
            } else if (i == j) {
                col_idx = key;
            } else {
                col_idx = j;
            }
            for (int k = 1; k <= row_num; k++) {
                if (matrix[k][j] != ' ') {
                    ciphertext[index++] = matrix[k][col_idx];
                }
            }
        }
    }
}

void permute_decrypt(char *ciphertext, char *plaintext, int key) {
    int len = strlen(ciphertext);
    int row_num = (len % key == 0) ? len / key : (len / key + 1);
    char matrix[MAX_ROW][MAX_COL] = {0};
    int index = 0;
    for (int i = 1; i <= row_num; i++) {
        for (int j = 1; j <= key; j++) {
            if (index < len) {
                matrix[i][j] = ciphertext[index++];
            } else {
                matrix[i][j] = ' ';
            }
        }
    }
    print_matrix(matrix, row_num, key);
    index = 0;
    for (int i = 1; i <= key; i++) {
        int col_idx = -1;
        for (int j = 1; j <= key; j++) {
            if (i == key) {
                col_idx = j;
            } else if (i == j) {
                col_idx = key;
            } else {
                col_idx = j;
            }
            for (int k = 1; k <= row_num; k++) {
                if (matrix[k][col_idx] != ' ') {
                    plaintext[index++] = matrix[k][col_idx];
                }
            }
        }
    }
}

void permute_cipher() {
    clear_console();
    show_menu();
    int choice = get_user_input();
    char plaintext[MAX_LEN] = {0};
    char ciphertext[MAX_LEN] = {0};
    int key = 0;
    switch (choice) {
        case 0:
            printf("Terminating the program...\n");
            break;
        case 1:
            get_plaintext(plaintext);
            key = get_key();
            permute_encrypt(plaintext, ciphertext, key);
            printf("\nCiphertext: %s\n", ciphertext);
            break;
        case 2:
            get_ciphertext(ciphertext);
            key = get_key();
            permute_decrypt(ciphertext, plaintext, key);
            printf("\nPlaintext: %s\n", plaintext);
            break;
        default:
            printf("Invalid choice, please try again.\n");
    }
}

int main() {
    permute_cipher();
    return 0;
}
