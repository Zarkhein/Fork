 #include <stdio.h>

#include <unistd.h>

#include <stdlib.h>



int estPremier(int nbr)

{

    for(int i = 2; i < nbr - 1; i++)

    {

        if(nbr%i == 0)

        {

            return 0;

        }

        return 1;

    }

}



int chercheProchainPremier(int nbr)

{

    nbr = nbr + 1;

    while(estPremier(nbr) == 0)

    {

        nbr = nbr + 1;

    }

    printf("Le nombre premier est: %d \n", nbr);
    return nbr;

}



int main(){

    int pip[2];

    int T[2];

    int pid;

    int i;



    if(pipe(T) == -1)

    {

        perror("erreur de pipe \n");

        exit(1);

    }
    pid = fork();    

    if(pid == 0)

    {

        int nbPremier = 1;

        for(int i = 0; i < 10; i++)

        {

            close(T[0]);

            nbPremier = chercheProchainPremier(nbPremier);
            write(T[1], nbPremier, 999);

            printf("SES Processus: %d", pid);

            printf("Je suis le fils numéro: %d \n", i);

            close(T[1]);

        }

        exit(0);

    }

    else

    {

        close(T[1]);

        printf("Ce Processus: %d", pid);

        printf("Je suis le pere \n");
        read(T[0], &nbPremier, 99);
        printf(" %s ", nbPremier);

        close(T[0]);

    }

    exit(0);

}