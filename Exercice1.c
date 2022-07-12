//Programme avec 2 processus qui communiquent par tube
//le premier envoie un message au second qui l'affiche

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int pip[2];
    char message[6] = "hello";
    int T[2];
    int pid;

    if(pipe(T) == -1)
    {
        perror("erreur de pipe \n");
        exit(1);
    }

    pid = fork();
    if(pid <= 0)
    {
        printf("%d", pid);
        perror("Erreur de fork\n");
        exit(1);
    }

    if(pid == 0) //Fils
    {
        close(T[0]);
        write(T[1], message, 20);
        close(T[1]);
        exit(0);
    }
    else //Pere
    {
        close(T[1]);
        read(T[0], &message, 20);
        printf(" %s ", message);
        close(T[0]);
        exit(0);
    }

}