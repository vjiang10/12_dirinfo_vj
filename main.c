#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char **argv) {
    DIR *d;
    char dir_arg[100];

    if (argc > 1) 
        strcpy(dir_arg, argv[1]);
    else {
        printf("Directory to scan: ");
        fgets(dir_arg, sizeof(dir_arg), stdin);
    }

    int len = strlen(dir_arg);
    if (dir_arg[len-1] == '\n')
        dir_arg[len-1] = '\0';

    d = opendir(dir_arg);
    if (d == NULL) {
        printf("errno: %d\nerror: %s\n", errno, strerror(errno));
        return 0;
    }

    struct dirent * entry;
    entry = readdir(d);
    long int tot_size = 0;
    struct stat file;
    
    printf("Statistics for directory: %s\n", dir_arg);
    
    // calculating total regular file size
    while (entry) {
        if (entry->d_type == DT_REG) {
            stat(entry->d_name, &file);
            tot_size += file.st_size;
        }
        entry = readdir(d);
    }
    printf("Total Directory Size: %ld Bytes\n", tot_size);
    
    rewinddir(d);
    entry = readdir(d);
    printf("Directories: \n");
    // printing all directories
    while (entry) {
        if (entry->d_type == DT_DIR) 
            printf("\t%s\n", entry->d_name);
        entry = readdir(d);
    }

    rewinddir(d);
    entry = readdir(d);
    printf("Regular files: \n");
    // priting all files 
    while (entry) {
        if (entry->d_type == DT_REG) {
            stat(entry->d_name, &file);
            printf("\t%s; file size: %ld Bytes\n", entry->d_name, file.st_size);
        }
        entry = readdir(d);
    }

    closedir(d);
    return 0;
}

