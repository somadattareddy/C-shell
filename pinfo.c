#include "pinfo.h"
#include "prints_prompt.h"
void pinfo_handler(char *input)
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

            if (i == 1)
            {
                char *read = (char *)malloc(sizeof(char) * 1024);
                char *path = (char *)malloc(sizeof(char) * 1024);

                sprintf(read, "/proc/%d/status", shell_pid);
                readlink(read, path, 1023);
                printf("pid -- %d\n", shell_pid);
                FILE *fp;
                char str[1000];
                char *filename = read;
                int i = 1;
                fp = fopen(read, "r");
                if (fp == NULL)
                {
                    printf("Could not open file %s", filename);
                    return;
                }
                while (fgets(str, 1000, fp) != NULL)
                {
                    if (i == 1 || i == 3 || i == 18)
                    {
                        printf("%s", str);
                    }
                    i++;
                }
                fclose(fp);
                printf("executable path -- %s\n", path);
            }
            if (i == 2)
            {
                char *read1 = (char *)malloc(sizeof(char) * 1024);
                char *path1 = (char *)malloc(sizeof(char) * 1024);
                char *path2 = (char *)malloc(sizeof(char) * 1024);
                FILE *fp;
                char str[1000];
                char *filename;
                int x = atoi(arg[1]);
                sprintf(path1, "/proc/%d/exe", x);
                readlink(path1, path2, 1023);
                sprintf(read1, "/proc/%d/status", x);
                printf("pid -- %d\n", x);

                int lk = 1;
                fp = fopen(read1, "r");
                if (fp == NULL)
                {
                    printf("Could not open file %s\n", read1);
                    exit(0);
                }
                while (fgets(str, 1000, fp) != NULL)
                {
                    if (lk == 1 || lk == 3 || lk == 18)
                    {
                        printf("%s", str);
                    }
                    lk++;
                }
                fclose(fp);
                printf("executable path -- %s\n", path2);
            }
            exit(0);
        }
    }
    else
    {
        char *read = (char *)malloc(sizeof(char) * 1024);
        char *path = (char *)malloc(sizeof(char) * 1024);

        sprintf(read, "/proc/%d/exe", shell_pid);
        readlink(read, path, 1023);

        if (i == 0)
        {
            printf("pid -- %d\n", shell_pid);
            FILE *fp;
            char str[1000];
            char *filename = "/proc/self/status";
            int i = 1;
            fp = fopen(filename, "r");
            if (fp == NULL)
            {
                printf("Could not open file %s\n", filename);
                return;
            }
            while (fgets(str, 1000, fp) != NULL)
            {
                if (i == 1 || i == 3 || i == 18)
                {
                    printf("%s", str);
                }
                i++;
            }
            fclose(fp);
            printf("executable path -- %s\n", path);
            return;
        }
        if (i == 1)
        {
            char *read1 = (char *)malloc(sizeof(char) * 1024);
            char *path1 = (char *)malloc(sizeof(char) * 1024);
            char *path2 = (char *)malloc(sizeof(char) * 1024);
            FILE *fp;
            char str[1000];
            char *filename;
            int x = atoi(arg[1]);
            sprintf(path1, "/proc/%d/exe", x);
            readlink(path1, path2, 1023);
            sprintf(read1, "/proc/%d/status", x);
            printf("pid -- %d\n", x);

            int lk = 1;
            fp = fopen(read1, "r");
            if (fp == NULL)
            {
                printf("Could not open file %s\n", read1);
                return;
            }
            while (fgets(str, 1000, fp) != NULL)
            {
                if (lk == 1 || lk == 3 || lk == 18)
                {
                    printf("%s", str);
                }
                lk++;
            }
            fclose(fp);
            printf("executable path -- %s\n", path2);
        }
    }
}