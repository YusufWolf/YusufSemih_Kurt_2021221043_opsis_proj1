#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>

/*
void writefunction(char *d){
    int ex = 0;
    int pid = fork();     //fork işlemini oluşturulması
    if(pid == 0){
       // write(pipefd[1], d, strlen(d));
        int e = execvp("writef", NULL);
        perror("");
        close(pipefd[1]);
    }else{
        wait(&ex); //childprocess'ler bitene kadar parent process'i bekletme
    }
    }
*/

void bash()
{
    int pid = fork();  //fork işlemini oluşturulması
    if (pid == 0)
    {
        int ev = execvp("bash", NULL);
        perror("");
    }
    else
    {
        wait(&pid); //childprocess'ler bitene kadar parent process'i bekletme
    }
}

void ls()
{
    int pid = fork();  //fork işlemini oluşturulması
    if (pid == 0)
    {
        int ev = execvp("/bin/ls", NULL);
        perror("");
    }
    else
    {
        wait(&pid);  //childprocess'ler bitene kadar parent process'i bekletme
    }
}

int main(int argc, char *argv[])
{
    char input[300];
    int inputsize;
    char *myString = "";

    while (1) // exit komutu girilene kadar myshell>> gelicek.
    {
        inputsize = 1;  // for döngüsünden önce her seferinde size'ı tekrar = 1
        printf("myshell>> "); // Komut Satırım myshell>>
        // getc(stdin);
        fgets(input, 300, stdin); // inputu okur.
        // printf("%s\n", input);
        // char *token = strtok(input, " ");
        for (int i = 0; i < 300; i++)
        {
            if (input[i] == ' ')
            {
                inputsize++;   //her seferinde size'ı 1 arttırıyorum.
            }

        }
        char *token = strtok(input, " ");
        char *arr[inputsize];
        int x = 0;
        while (token != NULL) // Data spliting
        {
            arr[x++] = token;
            token = strtok(NULL, " ");
        }
        if (strcmp(arr[0], "cat") == 0)   //array'in 0. sı cat olucak
        {
            
            printf("cat:");   
            for (int i = 1; i < inputsize; i++)  //array'in diğer elemanları sırayla yazdırılıyor
            {
                printf(" ");
                printf("%s", arr[i]);
            }
            

        }
        else if (strcmp(input, "ls\n") == 0)  //string compare ile kullanıcıdan alınan inputun kontrolü
        {
            printf("ls has been hit\n");
            ls();
        }
        else if (strcmp(input, "bash\n") == 0) //string compare ile kullanıcıdan alınan inputun kontrolü
        {
            printf("bash has been hit\n");
            bash();
        }
        else if (strcmp(input, "exit\n") == 0) //string compare ile kullanıcıdan alınan inputun kontrolü
        {
            printf("Exiting... ");  //myshell'den çıkış 
            exit(0);
        }
        else if (strcmp(input, "clear\n") == 0) //string compare ile kullanıcıdan alınan inputun kontrolü
        {
            system("clear");  //terminal'in clearlanması
        }
        else
        {
            printf("command not found\n"); // Yanlis komut girdiniz Myshell'e geri dönme
        }
    }
    return 0;
}
