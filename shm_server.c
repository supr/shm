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

        /* Create SHM */
        if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0)
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

        for(char c = 'a'; c <= 'z'; c++)
                *bufp++ = c;
        *bufp = '\0';

        /* Wait till client writes a * */
        while (*shm != '*')
                sleep(1);

        if (shmdt(shm) < 0)
        {
                perror("shmdt");
                exit(1);
        }

        if (shmctl(shmid, IPC_RMID, NULL) < 0)
        {
                perror("shmctl");
                exit(1);
        }

        return 0;
}
