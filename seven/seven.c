/*
 * William Kinderman
 * Assignment 7
 * source based on pipes/pipe_sync.c @
 *  http://man7.org/tlpi/code/online/book/pipes/pipe_sync.c.html
 */

#include "semun.h"
#include "curr_time.h"
#include "tlpi_hdr.h"

int main(int argc, char *argv[]) {
    pid_t pid;
    int i, semid;
    unsigned int child_count = argc - 1;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s sleep-time...\n", argv[0]);

    setbuf(stdout, NULL);
    printf("%s  Parent started.\n", currTime("%T"));

    // create semaphore
    semid = semget(IPC_PRIVATE, (child_count), 0666);

    for (i = 0; i < argc; ++i) semctl(semid, i, SETVAL, 0);

    for (i = 0; i < child_count; i++) {
        switch (fork()) {
        case -1:
            errExit("fork %d", i);

        case 0: /* Child */

            sleep(getInt(argv[i + 1], GN_NONNEG, "sleep-time"));
            printf("%s  Child %d (PID=%ld) child done.\n", currTime("%T"), i, (long) getpid());

            struct sembuf c_buffer;
            c_buffer.sem_num = i;
            c_buffer.sem_op = 1;
            c_buffer.sem_flg = 0;

            // decriment semaphore
            if (semop(semid, &c_buffer, 1) < 0) {
                perror("semop");
                _exit(EXIT_FAILURE);
            }
            _exit(EXIT_SUCCESS);
        default: /* Parent */
            break;
        }
    }

    struct sembuf p_buffer[child_count];
    for (i = 0; i < argc; i++) {
        p_buffer[i].sem_op = -1;
        p_buffer[i].sem_num = i;
        p_buffer[i].sem_flg = 0;
    }

    semop(semid, p_buffer, child_count);

    printf("%s  Parent ready to go.\n", currTime("%T"));

    // remove semaphore
    semctl(semid, 0, IPC_RMID, NULL);

    exit(EXIT_SUCCESS);
}