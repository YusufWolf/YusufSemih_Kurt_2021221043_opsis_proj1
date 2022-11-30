#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(){
    int pid = getpid();
    int ppid = getppid();
     
    char str[200];
    read(3, str, 200);

    char *fileName = strtok(str, "\n");
    printf("%s ", fileName);
    FILE *myfile = fopen(fileName, "w");
    fprintf("pid= %s", "ppid= %s", pid, ppid);
    fclose(myfile);
    return 0;
}