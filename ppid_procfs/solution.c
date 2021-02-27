#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char buff[1024];

int main() {
    pid_t pid;
    char *ppid;
    FILE *f;

    pid = getpid();
    sprintf(buff, "/proc/%d/stat", pid);
    f = fopen(buff, "r");
    if (!(f)) return 1;
    if (fread(buff, sizeof(char), sizeof(buff), f) > 0){
        strtok(buff, " ");
        strtok(NULL, " ");
        strtok(NULL, " ");
        ppid = strtok(NULL, " ");
        printf("%s\n", ppid);
    }
    fclose(f);
    return 0;
}
