#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char path[PATH_MAX];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s [-t path|-R|-H]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(strcmp(argv[1], "-R") == 0) {
        if(chdir("/") != 0) {
            perror("chdir");
            exit(EXIT_FAILURE);
        }
    } else if(strcmp(argv[1], "-H") == 0) {
        char *homedir = getenv("HOME");
        if(homedir == NULL) {
            fprintf(stderr, "Unable to determine HOME directory.\n");
            exit(EXIT_FAILURE);
        }
        if(chdir(homedir) != 0) {
            perror("chdir");
            exit(EXIT_FAILURE);
        }
    } else if(strcmp(argv[1], "-t") == 0 && argc == 3) {
        if(chdir(argv[2]) != 0) {
            perror("chdir");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Invalid option.\nUsage: %s [-t path|-R|-H]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (getcwd(path, sizeof(path)) == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
    printf("Current working directory changed to: %s\n", path);

    exit(EXIT_SUCCESS);
}

