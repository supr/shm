#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>

#define SHMSZ 27

int main()
{
        key_t key = KEY;
        int shmid = -1;
        char *shm, *bufp;

        /* Create or get SHM */
        if ((shmid = shmget(key, SHMSZ, 0666)) < 0)
        {
                perror("shmget");
                exit(1);
        }

        /* SHM attach */
        if ((shm = (char *)shmat(shmid, NULL, 0)) == (char *) -1)
        {
                perror("shmat");
                exit(1);
        }

        bufp = shm;

        for(; *bufp != '\0'; bufp++)
                printf("%c", *bufp);
        printf("\n");

        /* stop server */
        *shm = '*';

        return 0;
}
