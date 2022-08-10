#include "cd.h"
#include "prints_prompt.h"

void cd_handler(char *input)
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
    if (i == 0)
    {
        printf("Error: insufficient number of arguments\n");
        return;
    }
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
            if (strcmp(arg[1], "~") == 0)
            {
                chdir(ret_home_dir());
            }
            else
            {
                if (chdir(arg[1]) != 0)
                {
                    perror("Error");
                }
            }
            exit(0);
        }
    }
    else
    {
        if (strcmp(arg[1], "~") == 0)
        {
            chdir(ret_home_dir());
        }
        else
        {
            if (chdir(arg[1]) != 0)
            {
                perror("Error");
            }
        }
    }
}