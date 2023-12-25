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

void permute(char *input, char *output, int key, int encrypt) {
    int len = strlen(input);
    int row_num = (len % key == 0) ? len / key : (len / key + 1);
    int index = 0;
    char matrix[MAX_ROW][MAX_COL] = {0};
    for (int j = 1; j <= key; j++) {
        for (int i = 1; i <= row_num; i++) {
            if (index < len) {
                matrix[i][j] = input[index++];
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
            if (encrypt) {
                if (i == j) {
                    col_idx = key;
                } else {
                    col_idx = j;
                }
            } else {
                if (i == key) {
                    col_idx = j;
                } else if (i == j) {
                    col_idx = key;
                } else {
                    col_idx = j;
                }
            }
            for (int k = 1; k <= row_num; k++) {
                if ((encrypt && matrix[k][j] != ' ') || (!encrypt && matrix[k][col_idx] != ' ')) {
                    output[index++] = encrypt ? matrix[k][col_idx] : matrix[k][j];
                }
            }
        }
    }
}

void permute_cipher() {
    clear_console();
    show_menu();
    int choice = get_user_input();
    char input[MAX_LEN] = {0};
    char output[MAX_LEN] = {0};
    int key = 0;
    switch (choice) {
        case 0:
            printf("Terminating the program...\n");
            break;
        case 1:
            get_plaintext(input);
            key = get_key();
            permute(input, output, key, 1);
            printf("\nCiphertext: %s\n", output);
            break;
        case 2:
            get_ciphertext(input);
            key = get_key();
            permute(input, output, key, 0);
            printf("\nPlaintext: %s\n", output);
            break;
        default:
            printf("Invalid choice, please try again.\n");
    }
}

int main() {
    permute_cipher();
    return 0;
}
