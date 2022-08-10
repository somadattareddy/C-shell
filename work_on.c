#include "work_on.h"
#include "mypwd.h"
#include "pinfo.h"
#include "prints_prompt.h"
#include "cd.h"
#include "echo.h"
#include "ls.h"
#include "exec.h"

void work_on2(char *input)
{
    char *token = strtok(input, " \t");
    if (strcmp(token, "pwd") == 0)
    {
        pwd_handler(input);
    }
    else if (strcmp(token, "cd") == 0)
    {
        cd_handler(input);
    }
    else if (strcmp(token, "echo") == 0)
    {
        echo_handler(input);
    }
    else if (strcmp(token, "ls") == 0)
    {
        ls_handler(input);
    }
    else if (strcmp(token, "pinfo") == 0)
    {
        pinfo_handler(input);
    }
    else
    {
        exec_handler(token, input);
        hel = 0;
    }
}

void work_on(char *input)
{
    int i;
    int c = 0;
    for (int a = 0; a < strlen(input); a++)
    {
        if (input[a] == ';')
        {
            c++;
        }
        c += 1;
    }
    char **command = (char **)malloc(sizeof(char *) * c);
    char *token = strtok(input, ";");
    i = 0;
    while (token != NULL)
    {
        i++;
        command[i] = (char *)malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(command[i], token);
        token = strtok(NULL, ";");
    }
    int command_count = i;

    for (int r = 1; r <= i; r++)
    {
        work_on2(command[r]);
    }
}
