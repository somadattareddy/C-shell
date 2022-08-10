#include "exec.h"
#include "prints_prompt.h"

void exec_handler(char *token, char *input)
{
    int i;
    int status;
    int amp_at_arg = 0;
    char **arg = (char **)malloc(sizeof(char *) * 10);
    char *token1 = strtok(NULL, " \t");
    i = 0;
    while (token1 != NULL)
    {
        i++;
        arg[i] = (char *)malloc(sizeof(char) * (strlen(token1) + 1));
        strcpy(arg[i], token1);
        token1 = strtok(NULL, " \t");
    }
    arg[0] = token;
    arg[i + 1] = NULL;

    for (int a = 1; a <= i; a++)
    {
        if (strcmp(arg[a], "&") == 0)
        {
            amp_at_arg = a;
            hel = 42;
        }
    }
    if (amp_at_arg == 0)
    {
        hel = 23;
    }
    int ret = fork();
    if (ret != 0)
    {
        waitpid(ret, &status, 0);
    }
    if (ret == 0)
    {
        int d = execvp(token, arg);
        if (d == -1)
        {
            perror("Error");
        }
        exit(0);
    }
}