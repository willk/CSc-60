/* William Kinderman
 * Assignment 5
 * Based on csc60msh by Doan Nguyen
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAXPATH 256
#define MAXLINE 1024
#define MAXARGS 20

void process_input(int argc, char **argv);
int parse_input(char *command, char **argv);
void _exit_error(char* s, bool __exit);

void catch_signal(int d) { write(1, "\nmsh > ", 7); }

int main(void) {
    pid_t pid;
    int argc, status;
    char command[MAXLINE], *argv[MAXARGS], path[MAXPATH];

    signal(SIGINT, catch_signal);

    printf("Welcome to the mini-shell, msh!\n");

    for (;;) {

        printf("msh > ");
        fflush(stdout);
        fgets(command, MAXLINE, stdin);

        argc = parse_input(command, argv);

        /* if nothing is entered do nothing */
        if (*argv == NULL) continue;

        /* exit */
        if (strcmp("exit", argv[0]) == 0) exit(EXIT_SUCCESS);

        /* print working directory */
        if (strcmp("pwd", argv[0]) == 0) {
            printf("%s\n", getenv("PWD"));
            continue;
        }

        /* error handling for invalid commands */
        if (*argv[0] == '<' || *argv[0] == '>') {
            _exit_error("No command.", false);
            continue;
        }

        /* cd */
        if (strcmp("cd", argv[0]) == 0) {
            // not Kansas
            if (argc > 1) chdir(argv[1]);
            // Kansas, there is no place like home Toto.
            else chdir(getenv("HOME"));

            // lets make sure to update PWD.
            getcwd(path, MAXPATH);
            setenv("PWD", path, 1);
            continue;
        }

        pid = fork();

        /* Unable to fork, reached fork limit? */
        if (pid == -1) perror("Shell programming error, unable to fork.\n");

        /* inside the child process */
        else if (pid == 0) process_input(argc, argv);
        /* inside the parent process, waiting on child */
        else {
            if (wait(&status) == -1) perror("Shell program error");
            // else printf("Child returned status: %d\n", status);
        }
    }
    return 0;
}

void process_input(int argc, char **argv) {
    int fd;
    bool flag = false;

    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '<') {
            // error checking
            if (flag) _exit_error("Can't have two input redirects.", true);
            if (argv[i + 1] == NULL) _exit_error("No input redictions file specified.", true);
            // open a fd
            if((fd = open(argv[i + 1], O_RDONLY)) < 0) perror("open");
            // dup the fd and close the fd
            if(dup2(fd, 0) < 0) perror("dup2");
            close(fd);
            argv[i] = NULL;
            flag = true;
        } else if (strcmp(">", argv[i]) == 0) {
            if (argv[i + 1] == NULL) _exit_error("No output file specified.", true);
            if ((fd = open(argv[i + 1], O_TRUNC | O_WRONLY | O_CREAT, 0666)) < 0) perror("open");
            if (dup2(fd, 1) < 0) perror("dup2");
            close(fd);
            argv[i] = NULL;
        } else if (strcmp(">>", argv[i]) == 0) {
            if (argv[i + 1] == NULL) _exit_error("No output file specified.", true);
            if ((fd = open(argv[i + 1], O_APPEND | O_WRONLY | O_CREAT, 0666)) < 0) perror("open");
            if (dup2(fd, 1) < 0) perror("dup2");
            close(fd);
            argv[i] = NULL;
        } else if (argv[i][0] == '|') {
             if (flag) _exit_error("No redirects and pipes.", true);


        }
    }

    if (execvp(*argv, argv) == -1) {
        perror("process_input, shell program.");
        _exit(-1);
    }
}


// print some of my own errors
void _exit_error(char* s, bool __exit) {
    printf("ERROR: %s\n", s);
    if (__exit) _exit(1);
}

/* parse_input takes the userinput from the command we asked the user to input
 * and a pointer to argv. It then breaks up the command. First it sets command
 * equal to the actual command, then for every blank space, or new line, or
 * tab it replaces them with \0. Returning a count of how many replaces it has
 * done.
 */

int parse_input(char *command, char **argv) {
    int count = 0;
    char *separator = " \n\t";
    argv[count] = strtok(command, separator);

    while ((argv[count] != NULL) && (count + 1 < MAXARGS)) {
        argv[++count] = strtok((char *) 0, separator);
    }

    return count;
}
