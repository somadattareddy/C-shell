#include "echo.h"

void echo_handler(char *input)
{
    int i;
    int amp_at_arg = 0;
    char **arg = (char **)malloc(sizeof(char *) * 5);
    char *token = strtok(NULL, " \t");
    i = 0;
    while (token != NULL)
    {
        i++;
        arg[i] = (char *)malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(arg[i], token);
        token = strtok(NULL, " \t");
    }
    int arg_count = i;
    for (int a = 1; a <= i; a++)
    {
        if (strcmp(arg[a], "&") == 0)
        {
            amp_at_arg = a;
        }
    }
    if (amp_at_arg != 0)
    {
        int ret = fork();
        if (ret == 0)
        {
            printf("\n");
            for (int x = 1; x < i; x++)
            {
                printf("%s ", arg[x]);
            }
            printf("\n");
            exit(0);
        }
    }
    else
    {
        for (int x = 1; x <= i; x++)
        {
            printf("%s ", arg[x]);
        }
        printf("\n");
    }
}
