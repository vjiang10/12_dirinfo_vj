#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {
    DIR *d = opendir(".");
    int tot_size = 0;
    struct stat file;
    struct dirent *entry;
    entry = readdir(d);
    
    printf("Statistics for directory: %s\n", entry->d_name);
    
    // calculating total regular file size
    while (entry) {
        if (entry->d_type == DT_REG) {
            stat(entry->d_name, &file);
            tot_size += file.st_size;
        }
        entry = readdir(d);
    }
    printf("Total Directory Size: %d Bytes\n", tot_size);
    
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