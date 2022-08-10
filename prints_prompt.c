#include "prints_prompt.h"
#include "work_on.h"
#include "sig_handlers.h"

void get_names()
{
    hostname[1023] = '\0';
    username[1023] = '\0';
    gethostname(hostname, 1023);
    getlogin_r(username, 1023);
}
char *ret_home_dir()
{
    char *home_dir = (char *)malloc(sizeof(char) * 1024);
    char *for_reading = (char *)malloc(sizeof(char) * 1024);
    sprintf(for_reading, "/proc/%d/exe", shell_pid);
    readlink(for_reading, home_dir, 1023);
    free(for_reading);
    dirname(home_dir);
    return home_dir;
}
char *ret_rel_path()
{
    char *home_dir = (char *)malloc(sizeof(char) * 1024);
    home_dir = ret_home_dir();
    char *cur_dir = (char *)malloc(sizeof(char) * 1024);
    cur_dir = getcwd(NULL, 0);
    char *rel_path = (char *)malloc(sizeof(char) * 1024);
    if (strcmp(cur_dir, home_dir) == 0)
    {
        return "~";
    }
    else if (strcmp(cur_dir, home_dir) < 0)
    {
        return cur_dir;
    }
    else
    {
        int j = 1;
        for (int i = strlen(home_dir); i < strlen(cur_dir); i++)
        {
            rel_path[j] = cur_dir[i];
            j++;
        }
        rel_path[0] = '~';
        return rel_path;
    }
}

void print_prompt()
{
    char a;
    hel = 0;
    char *input = (char *)malloc(sizeof(char) * 1024);
    get_names();
    while (1)
    {
        int cur = 0;

        printf("%s@%s:%s$ ", username, hostname, ret_rel_path());

        while ((a = getchar()) != '\n')
        {
            input[cur++] = a;
        }
        input[cur] = '\0';
        hel = 0;
        work_on(input);
        signal(SIGCHLD, sigchld_handler);
    }
}
