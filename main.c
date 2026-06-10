#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <dirent.h>

int main(void) {
    DIR *folder;
    struct dirent *entry;
    int files = 0;

    folder = opendir("/sys/devices/virtual/thermal/");
    if (folder == NULL)
    {
        puts("Directory doesn't exist!");
        return(1);
    }
    while ((entry=readdir(folder)))
    {
        files++;
        printf("%s\n", entry->d_name);
    }
    closedir(folder);
    return 0;
}
