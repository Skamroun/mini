#include "minishell.h"

int is_buit_in(char *cmd)
{
   return (!(cmd[0] == '/' || cmd[0] == '.'));
}

void    free_double_pointer(char ***args)
{
    if (args && *args)
    {
        while (**args)
        {
            free(**args);
            (*args)++;
        }
    }
}

int execute_built_in(char **arg)
{
    if (ft_strncmp(arg[0], "cd", 2) == 0)
        ft_cd(arg);
    else if (ft_strncmp(arg[0], "echo", 4) == 0)
        ft_echo(arg);
    else if (ft_strncmp(arg[0], "env", 3) == 0)
        ft_env();
    else if (ft_strncmp(arg[0], "export", 6) == 0)
        ft_export(arg);
    else if (ft_strncmp(arg[0], "pwd", 3) == 0)
        ft_pwd();
    else if (ft_strncmp(arg[0], "unset", 5) == 0)
        ft_unset(arg);
    else if (ft_strncmp(arg[0], "exit", 4) == 0)
        ft_exit(arg);
    return 0;
}

int execute_cmd(char *cmd)
{
    int pid;
    char **args;

    args = ft_split(cmd, ' ');
    if (!is_buit_in(args[0]))
    {
        pid = fork();
        if (pid == 0 && !is_buit_in(args[0]))
        {
            execve(args[0], args, NULL);
            free_double_pointer(&args);
            exit(0);
        }
        else
        {
            waitpid(pid, 0, 0);
            free_double_pointer(&args);
        }
    }
    else
    {
        execute_built_in(args);
        free_double_pointer(&args);
    }
    return 0;
}

// int execute_pipe(char *cmd1, char *cmd2)
// {
//     int pipefd[2];
//     int pid;
//     int status;
//     char **args1;
//     char **args2 = NULL;

//     pipe(pipefd);
//     pid = fork();
//     if (pid == 0)
//     {
//         args1 = ft_split(cmd1, ' ');
//         args2 = ft_split(cmd2, ' ');
//         close(pipefd[0]);  // close reading end in the child
//         dup2(pipefd[1], STDOUT_FILENO);  // send stdout to the pipe
//         close(pipefd[1]);  // this descriptor is no longer needed
//         execve(args1[0], args1, NULL);
//         free(args1);
//         exit(0);
//     }
//     else
//     {
//         close(pipefd[1]);  // close the write end of the pipe in the parent
//         pid = fork();
//         if (pid == 0)
//         {
//             dup2(pipefd[0], STDIN_FILENO);  // read from the pipe
//             close(pipefd[0]);  // this descriptor is no longer needed
//             execve(args2[0], args2, NULL);
//             free(args2);
//       {
//     int pid;
//     char **args1;
//     int fd;

//     pid = fork();
//     if (pid == 0)
//     {
//         args1 = ft_split(cmd1, ' ');
//         fd = open(cmd2, O_WRONLY | O_CREAT | O_TRUNC, 0777);
//         dup2(fd, STDOUT_FILENO);
//         execve(args1[0], args1, NULL);
//         free(args1);
//         close(fd);
//         exit(0);
//     }
//     else
//         waitpid(pid,0, 0);
//     return 0;
// }      exit(0);
//         }
//         else
//         {
//             close(pipefd[0]);
//             waitpid(pid, &status, 0);
//             if (WIFEXITED(status))
//                 return WEXITSTATUS(status);
//         }
//     }
//     return 0;
// }

int execute_and(char *cmd1)
{
    execute_cmd(cmd1);
    return (0);
}

int execute_greater(char *cmd1, char *cmd2)
{

    int pid;
    char **args1;
    int fd;

    pid = fork();
    if (pid == 0)
    {
        args1 = ft_split(cmd1, ' ');
        fd = open(cmd2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd, STDOUT_FILENO);
        execve(args1[0], args1, NULL);
        free(args1);
        close(fd);
        exit(0);
    }
    else
        waitpid(pid,0, 0);
    return 0;
}

// int execute_less(char *cmd1, char *cmd2)
// {
//     int pid;
//     int status;
//     char **args1;
//     char **args2;
//     int fd;

//     pid = fork();
//     if (pid == 0)
//     {
//         args1 = ft_split(cmd1, ' ');
//         fd = open(cmd2, O_RDONLY);
//         dup2(fd, STDIN_FILENO);
//         execve(args1[0], args1, NULL);
//         free(args1);
//         close(fd);
//         exit(0);
//     }
//     else
//     {
//         waitpid(pid, &status, 0);
//         if (WIFEXITED(status))
//             return WEXITSTATUS(status);
//     }
//     return 0;
// }

int execute_dgreater(char *cmd1, char *cmd2)
{
    int pid;
    char **args1;
    int fd;

    pid = fork();
    if (pid == 0)
    {
        args1 = ft_split(cmd1, ' ');
        fd = open(cmd2, O_WRONLY | O_CREAT | O_APPEND, 0644);
        dup2(fd, STDOUT_FILENO);
        execve(args1[0], args1, NULL);
        free(args1);
        close(fd);
        exit(0);
    }
    else
        waitpid(pid,0, 0);
    return 0;
}
int execute_cmds(t_var *var)
{
    var->cmd_to_execute = tokenizer_params(var);
    var->head = var->cmd_to_execute;
    if (var->cmd_to_execute->type == CMD)
    {
        while (var->cmd_to_execute != NULL)
        {
            if (var->cmd_to_execute->next != NULL && var->cmd_to_execute->next->type > 0)
            {
                // if (var->cmd_to_execute->next->type == PIPE && var->cmd_to_execute->next->next
                //     && var->cmd_to_execute->next->next->type == CMD)
                //     execute_pipe(var->cmd_to_execute->content, var->cmd_to_execute->next->next->content);
                if (var->cmd_to_execute->next->type == AND)
                    execute_and(var->cmd_to_execute->content);
                else if (var->cmd_to_execute->next->type == GREATER && var->cmd_to_execute->next->next)
                    execute_greater(var->cmd_to_execute->content, var->cmd_to_execute->next->next->content);
                // else if (var->cmd_to_execute->next->type == LESS)
                //     execute_less(var->cmd_to_execute->content, var->cmd_to_execute->next->content);

                else if (var->cmd_to_execute->next->type == DGREATER && var->cmd_to_execute->next->next)
                        execute_dgreater(var->cmd_to_execute->content, var->cmd_to_execute->next->next->content);
                // else if (var->cmd_to_execute->next->type == DLESS)
                //     execute_dless(var->cmd_to_execute->content, var->cmd_to_execute->next->content);
                // else if (var->cmd_to_execute->next->type == DQUESTION)
                //     execute_dquestion(var->cmd_to_execute->content, var->cmd_to_execute->next->content);
                var->cmd_to_execute = var->cmd_to_execute->next;
            }
            else
                execute_cmd(var->cmd_to_execute->content);
            var->cmd_to_execute = var->cmd_to_execute->next;
        }
    }

    return 0;
}