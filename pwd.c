#include "mypwd.h"

void pwd_handler(char *input)
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
            int ret = fork();
            if (ret == 0)
            {
                printf("\n%s\n", getcwd(NULL, 0));
                exit(0);
            }
            //printf("for background\n");
        }
    }
    if (amp_at_arg == 0)
    {
        printf("%s\n", getcwd(NULL, 0));
    }
}
