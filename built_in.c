#include "minishell.h"

extern char **environ;

int ft_cd(char **arg)
{
    if (arg[1] == NULL)
    {
        chdir(getenv("HOME"));
        return 0;
    }
    else if (chdir(arg[1]) == -1)
    {
        printf("cd: %s: No such file or directory\n", arg[1]);
        return 1;
    }
    return 0;
}
size_t ft_strlen_double(char **arr)
{
    size_t i = 0;

    if (arr == NULL)
        return 0;
    while (arr[i] != NULL)
        i++;
    return i;
}

int ft_echo(char **arg)
{
    int i = 1;
    int flag = 0;

    if (ft_strlen_double(arg) > 1)
    {
        if (ft_strncmp(arg[1], "-n", 2) == 0)
        {
            flag = 1;
            i++;
        }
        while (arg[i])
        {
            printf("%s", arg[i]);
            if (arg[i + 1])
                printf(" ");
            i++;
        }
    }
    if (flag == 0)
        printf("\n");
    return 0;
}

int ft_env()
{
    int i = 0;
    while (environ[i])
    {
        printf("%s\n", environ[i]);
        i++;
    }
    return 0;
}

int ft_export(char **arg)
{
    int i = 1;
    while (arg[i])
    {
        if (ft_strchr(arg[i], '='))
            putenv(arg[i]);
        i++;
    }
    return 0;
}

int ft_pwd()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
    return 0;
}
int ft_unset(char **arg)
{
    int i = 1;
    while (arg[i])
    {
        unsetenv(arg[i]);
        i++;
    }
    return 0;
}

int ft_exit(char **arg)
{
    free_double_pointer(&arg);
    // ft_lstclear(&var->head,free);
    // var->head = NULL;
    exit(1);
    return 0;
}