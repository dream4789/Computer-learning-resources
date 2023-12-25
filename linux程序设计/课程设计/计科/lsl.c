// sudo cp lsl /usr/bin/
// lsl 1
// lsl 2
// lsl 3

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void list_files(int option);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ls <option>\n");
        printf("\t-2\tList file names and permissions\n");
        printf("\t-3\tList file names, permissions, and sizes\n");
        exit(1);
    }

    int option = atoi(argv[1]);

    switch (option) {
        case 2:
        case 3: list_files(option); break;
        default: printf("Invalid option\n"); exit(1);
    }
    return 0;
}

void list_files(int option) {
    DIR *dp = opendir(".");
    if (dp == NULL) {
        perror("opendir error");
        exit(1);
    }

    struct dirent *dirp;
    struct stat filestat;
    char filename[1024];

    while ((dirp = readdir(dp)) != NULL) {
        if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0) continue;
        sprintf(filename, "./%s", dirp->d_name);
        if (stat(filename, &filestat) == -1) continue;

        printf((S_ISDIR(filestat.st_mode)) ? "\033[36md" : "\033[36m-");
        printf((filestat.st_mode & S_IRUSR) ? "r" : "-");
        printf((filestat.st_mode & S_IWUSR) ? "w" : "-");
        printf((filestat.st_mode & S_IXUSR) ? "x" : "-");
        printf((filestat.st_mode & S_IRGRP) ? "r" : "-");
        printf((filestat.st_mode & S_IWGRP) ? "w" : "-");
        printf((filestat.st_mode & S_IXGRP) ? "x" : "-");
        printf((filestat.st_mode & S_IROTH) ? "r" : "-");
        printf((filestat.st_mode & S_IWOTH) ? "w" : "-");
        printf((filestat.st_mode & S_IXOTH) ? "x\033[0m" : "-\033[0m");

        if (option == 2) printf(" %10s\n", dirp->d_name);  // 2
        else printf(" %6ld %10s\n", filestat.st_size, dirp->d_name);  // 3
    }
    closedir(dp);
}

