#include "ls.h"
#include <pwd.h>
#include <grp.h>
void sfile(char const filename[])
{

    struct stat sfile;
    char *time = (char *)malloc(sizeof(char) * 100);
    if (stat(filename, &sfile) == -1)
    {
        printf("Error Occurred\n");
    }
    printf("%s", (S_ISDIR(sfile.st_mode)) ? "d" : "-");
    printf("%s", (sfile.st_mode & S_IRUSR) ? "r" : "-");
    printf("%s", (sfile.st_mode & S_IWUSR) ? "w" : "-");
    printf("%s", (sfile.st_mode & S_IXUSR) ? "x" : "-");
    printf("%s", (sfile.st_mode & S_IRGRP) ? "r" : "-");
    printf("%s", (sfile.st_mode & S_IWGRP) ? "w" : "-");
    printf("%s", (sfile.st_mode & S_IXGRP) ? "x" : "-");
    printf("%s", (sfile.st_mode & S_IROTH) ? "r" : "-");
    printf("%s", (sfile.st_mode & S_IWOTH) ? "w" : "-");
    printf("%s", (sfile.st_mode & S_IXOTH) ? "x" : "-");
    printf("\t");
    printf("%ld\t", sfile.st_nlink);
    printf("%s\t", getpwuid(sfile.st_uid)->pw_name);
    printf("%s\t", getgrgid(sfile.st_gid)->gr_name);
    printf("%ld\t", sfile.st_size);
    strftime(time, 100, "%b  %d %H:%M", localtime(&sfile.st_mtime));
    printf("%s\t", time);
    printf("%s\n", filename);
}

void ls_handler2(char *input)
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(input)) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL)
        {
            printf("%s\n", ent->d_name);
        }
        closedir(dir);
    }
    else
    {
        /* could not open directory */
        perror("ls");
    }
}
void ls_handler3(char *input)
{
    DIR *dir;
    struct dirent *ent;
    char names[1024];
    if ((dir = opendir(input)) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL)
        {
            strcpy(names, ent->d_name);
            if (names[0] != '.')
                printf("%s\n", names);
        }
        closedir(dir);
    }
    else
    {
        /* could not open directory */
        perror("ls");
    }
}

void ls_handler4(char *input)
{
    DIR *dir;
    struct dirent *ent;
    char names[1024];
    if ((dir = opendir(input)) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL)
        {
            strcpy(names, ent->d_name);
            if (names[0] != '.')
                sfile(names);
        }
        closedir(dir);
    }
    else
    {
        /* could not open directory */
        perror("ls");
    }
}
void ls_handler5(char *input)
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(input)) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL)
        {
            sfile(ent->d_name);
        }
        closedir(dir);
    }
    else
    {
        /* could not open directory */
        perror("ls");
    }
}
void ls_handler(char *input)
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
                ls_handler3(".");
            }
            else if (i == 2)
            {
                if (strcmp(arg[1], "-a") == 0)
                {
                    ls_handler2(".");
                }
                else if (strcmp(arg[1], ".") == 0)
                {
                    ls_handler3(".");
                }
                else if (strcmp(arg[1], "..") == 0)
                {
                    ls_handler3("..");
                }
                else if (strcmp(arg[1], "~") == 0)
                {
                    char *homedir = getenv("HOME");
                    ls_handler3(homedir);
                }
                else if (strcmp(arg[1], "-l") == 0)
                {
                    ls_handler4(".");
                }
                else if (strcmp(arg[1], "-la") == 0 || strcmp(arg[1], "-al") == 0)
                {
                    ls_handler5(".");
                }
                else
                {
                    ls_handler3(arg[1]);
                }
            }
            else if (i == 3)
            {
                if ((strcmp(arg[1], "-l") == 0 && strcmp(arg[2], "-a") == 0) || (strcmp(arg[1], "-a") == 0 && strcmp(arg[2], "-l") == 0))
                {
                    ls_handler5(".");
                }
                else if (strcmp(arg[1], "-l") == 0)
                {
                    ls_handler4(arg[2]);
                }
                else if (strcmp(arg[1], "-a") == 0)
                {
                    ls_handler2(arg[2]);
                }
                else if (strcmp(arg[1], "-la") == 0 || strcmp(arg[1], "-al") == 0)
                {
                    ls_handler5(arg[2]);
                }
                else
                {
                    ls_handler3(arg[1]);
                }
            }
            else if (i == 4)
            {
                if ((strcmp(arg[1], "-l") == 0 && strcmp(arg[2], "-a") == 0) || (strcmp(arg[1], "-a") == 0 && strcmp(arg[2], "-l") == 0))
                {
                    ls_handler5(arg[3]);
                }
                else
                {
                    ls_handler3(arg[1]);
                }
            }
            else
            {
                ls_handler3(arg[1]);
            }
            exit(0);
        }
    }
    else
    {

        if (i == 0)
        {
            ls_handler3(".");
        }
        else if (i == 1)
        {
            if (strcmp(arg[1], "-a") == 0)
            {
                ls_handler2(".");
            }
            else if (strcmp(arg[1], ".") == 0)
            {
                ls_handler3(".");
            }
            else if (strcmp(arg[1], "..") == 0)
            {
                ls_handler3("..");
            }
            else if (strcmp(arg[1], "~") == 0)
            {
                char *homedir = getenv("HOME");
                ls_handler3(homedir);
            }
            else if (strcmp(arg[1], "-l") == 0)
            {
                ls_handler4(".");
            }
            else if (strcmp(arg[1], "-la") == 0 || strcmp(arg[1], "-al") == 0)
            {
                ls_handler5(".");
            }
            else
            {
                ls_handler3(arg[1]);
            }
        }
        else if (i == 2)
        {
            if ((strcmp(arg[1], "-l") == 0 && strcmp(arg[2], "-a") == 0) || (strcmp(arg[1], "-a") == 0 && strcmp(arg[2], "-l") == 0))
            {
                ls_handler5(".");
            }
            else if (strcmp(arg[1], "-l") == 0)
            {
                ls_handler4(arg[2]);
            }
            else if (strcmp(arg[1], "-a") == 0)
            {
                ls_handler2(arg[2]);
            }
            else if (strcmp(arg[1], "-la") == 0 || strcmp(arg[1], "-al") == 0)
            {
                ls_handler5(arg[2]);
            }
            else
            {
                ls_handler3(arg[1]);
            }
        }
        else if (i == 3)
        {
            if ((strcmp(arg[1], "-l") == 0 && strcmp(arg[2], "-a") == 0) || (strcmp(arg[1], "-a") == 0 && strcmp(arg[2], "-l") == 0))
            {
                ls_handler5(arg[3]);
            }
            else
            {
                ls_handler3(arg[1]);
            }
        }
        else
        {
            ls_handler3(arg[1]);
        }
    }
}
