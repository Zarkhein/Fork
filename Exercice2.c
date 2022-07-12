/*
*Programme avec 2 processus qui communiquent par tube 
*les deux processus s'envoient un message ou des messages différentset affichent les messages reçus
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int pip[2];
    char message[6] = "hello";
    char message2[8] = "douglas";
    int T[2]; //Tube 1
    int P[2]; //Tube 2
    int pid;


    if(pipe(T) == -1)
    {
        perror("erreur de pipe \n");
        exit(1);
    }

    pid = fork();
    if(pid < 0)
    {
        printf("%d", pid);
        perror("Erreur de fork\n");
        exit(1);
    }
    if(pid == 0) //Fils
    {
        //tube 1
        close(T[0]);
        write(T[1], message, 20);
        close(T[1]);

        //tube 2
        close(P[0]);
        write(P[1], message2, 20);
        close(P[1]);
        exit(0);
    }
    else //Pere
    {
        //tube 1
        close(T[1]);
        read(T[0], &message, 20);
        printf(" %s ", message);
        close(T[0]);

        //tube 2
        close(P[1]);
        read(P[0], &message2, 20);
        printf(" %s ", message2);
        close(P[0]);

        exit(0);
    }

}