#include "sig_handlers.h"
#include "prints_prompt.h"

void sigchld_handler(int signo)
{
    if (hel == 23)
    {
        return;
    }
    else if (hel == 42)
    {
        int status;
        pid_t pid = waitpid(-1, &status, WNOHANG);
        char *read = (char *)malloc(sizeof(char) * 1024);
        char *command = (char *)malloc(sizeof(char) * 1024);
        sprintf(read, "/proc/%d/comm", pid);
        readlink(read, command, 1023);
        if (WIFEXITED(status))
        {
            fprintf(stderr, "\nNormal termination of process %s having pid %d with exit status=%d\n", command, pid, WEXITSTATUS(status));
        }
        if (WIFSIGNALED(status))
        {
            fprintf(stderr, "\nprocess %s with pid %d killed by signal=%d%s\n", command, pid, WTERMSIG(status), WCOREDUMP(status) ? " (dumped core)" : "");
        }
        if (WIFSTOPPED(status))
        {
            fprintf(stderr, "\nprocess %s with pid %d stopped by signal=%d\n", command, pid, WSTOPSIG(status));
        }
        if (WIFCONTINUED(status))
        {
            fprintf(stderr, "\nprocess %s with pid %d continued\n", command, pid);
        }
        fflush(stdout);
    }
    else
    {
        int status;
        pid_t pid = waitpid(-1, &status, WNOHANG);
        char *read = (char *)malloc(sizeof(char) * 1024);
        char *command = (char *)malloc(sizeof(char) * 1024);
        sprintf(read, "/proc/%d/comm", pid);
        readlink(read, command, 1023);
        if (WIFEXITED(status))
        {
            fprintf(stderr, "\nNormal termination of process %s having pid %d with exit status=%d\n", command, pid, WEXITSTATUS(status));
            get_names();
            printf("%s@%s:%s$ ", username, hostname, ret_rel_path());
        }
        if (WIFSIGNALED(status))
        {
            fprintf(stderr, "\nprocess %s with pid %d killed by signal=%d%s\n", command, pid, WTERMSIG(status), WCOREDUMP(status) ? " (dumped core)" : "");
            get_names();
            printf("%s@%s:%s$ ", username, hostname, ret_rel_path());
        }
        if (WIFSTOPPED(status))
        {
            fprintf(stderr, "\nprocess %s with pid %d stopped by signal=%d\n", command, pid, WSTOPSIG(status));
            get_names();
            printf("%s@%s:%s$ ", username, hostname, ret_rel_path());
        }
        if (WIFCONTINUED(status))
        {
            fprintf(stderr, "\nprocess %s with pid %d continued\n", command, pid);
            get_names();
            printf("%s@%s:%s$ ", username, hostname, ret_rel_path());
        }
        fflush(stdout);
    }
}