#include "minishell.h"

int is_executable(char *path) {
    int pipefd[2];
    int pid;
    char **args;
    char buffer[1024];

    pipe(pipefd);
    pid = fork();
    if (pid == 0)
    {
        args = (char  **)malloc(sizeof(char *) * 3);
        close(pipefd[0]);  // close reading end in the child
        dup2(pipefd[1], STDOUT_FILENO);  // send stdout to the pipe
        close(pipefd[1]);  // this descriptor is no longer needed
        args[0] = ft_strdup("/usr/bin/file");
        args[1] = ft_strdup(path);
        args[2] = NULL;
        execve(args[0], args, NULL);
        free(args);
        exit(0);
    }
    else
    {
        close(pipefd[1]);  // close the write end of the pipe in the parent
        read(pipefd[0], buffer, sizeof(buffer));
        wait(NULL);  // wait for the child to exit 
        // printf("10 >> path : %s> buffer : %s\n}}}", path ,buffer);    
        if (ft_strnstr(buffer, "directory", ft_strlen(buffer)) != NULL)
            return 0;
        return (ft_strnstr(buffer, "executable", ft_strlen(buffer)) != NULL);
    }
}
int set_OP(t_var *var)
{
    if (ft_strnstr((char *)var->node->content, "|", 1))
        var->node->type = PIPE;
    else if (ft_strnstr((char *)var->node->content, "&&", 2))
        var->node->type = AND;
    else if (ft_strnstr((char *)var->node->content, ">>", 2))
        var->node->type = DGREATER;
    else if (ft_strnstr((char *)var->node->content, "<<", 2))
        var->node->type = DLESS;
    else if (ft_strnstr((char *)var->node->content, "$?", 2))
        var->node->type = DQUESTION;
    else if (ft_strnstr((char *)var->node->content, ">", 1))
        var->node->type = GREATER;
    else if (ft_strnstr((char *)var->node->content, "<", 1))
        var->node->type = LESS;
    else if (ft_strnstr((char *)var->node->content, "$", 1))
        var->node->type = DOLLAR;
    else if (ft_strnstr(&((char *)var->node->content)[0], "-", 1))
        var->node->type = FLAG;
    else
        var->node->type = -1;
    return 0;
}
int set_OP2(t_var *var)
{
    if (ft_strnstr((char *)var->tmp->content, "|", 1))
        var->tmp->type = PIPE;
    else if (ft_strnstr((char *)var->tmp->content, "&&", 2))
        var->tmp->type = AND;
    else if (ft_strnstr((char *)var->tmp->content, ">>", 2))
        var->tmp->type = DGREATER;
    else if (ft_strnstr((char *)var->tmp->content, "<<", 2))
        var->tmp->type = DLESS;
    else if (ft_strnstr((char *)var->tmp->content, "$?", 2))
        var->tmp->type = DQUESTION;
    else if (ft_strnstr((char *)var->tmp->content, ">", 1))
        var->tmp->type = GREATER;
    else if (ft_strnstr((char *)var->tmp->content, "<", 1))
        var->tmp->type = LESS;
    else if (ft_strnstr((char *)var->tmp->content, "$", 1))
        var->tmp->type = DOLLAR;
    else if (ft_strnstr(&((char *)var->node->content)[0], "-", 1))
        var->tmp->type = FLAG;
    else
        var->tmp->type = -1;
    return 0;
}
// int tokenizer_split_cmds(t_var *var)
// {
//     while (var->i < var->len && var->line[var->i] == ' ')
//         var->i++;
//     if (var->i < var->len && var->line[var->i] == '\"')
//     {
//         var->start = var->i;
//         var->i += 1;
//         while (var->i < var->len && var->line[var->i] != '\"')
//             var->i++;
//         var->node = ft_lstnew(ft_substr(var->line,var->start,
//             var->i - var->start+1));
//         var->i++;
//     }
//     else if (var->i < var->len && var->line[var->i] == '\'')
//     {
//         var->start = var->i;
//         var->i += 1;
//         while (var->i < var->len && var->line[var->i] != '\'')
//             var->i++;
//         var->node = ft_lstnew(ft_substr(var->line,
//             var->start,var->i - var->start+1));
//         var->i++;
//     }
//     else
//     {
//         var->start = var->i;
//         var->i += 1;
//         while (var->i < var->len && var->line[var->i] != ' '
//             && (var->line[var->i] != '\"' || var->line[var->i] != '\'')
//             && !ft_strchr("><|", var->line[var->i]))
//             var->i++;
//         var->node = ft_lstnew(ft_substr(var->line,var->start,var->i - var->start));
//         set_OP(var);
//         if (var->i < var->len && ft_strchr("><|", var->line[var->i]))
//         {
//             if (var->line[var->i] != '|' && var->i + 1 < var->len
//                 && var->line[var->i + 1] == var->line[var->i]
//                 && var->i + 2 < var->len && var->line[var->i + 2] != var->line[var->i])
//             {
//                 var->tmp=ft_lstnew(ft_substr(var->line,var->i,2));
//                 set_OP2(var);
//                 ft_lstadd_back(&var->node,var->tmp );
//                 var->i += 2;
//             }
//             else if (var->i + 1 < var->len && var->line[var->i + 1] != var->line[var->i])
//             {
//                 var->tmp=ft_lstnew(ft_substr(var->line,var->i,1));
//                 set_OP2(var);
//                 ft_lstadd_back(&var->node, var->tmp);
//                 var->i += 1;
//             }
//             while (var->i < var->len && ft_strchr("><|", var->line[var->i]))
//             {
//                 var->tmp=ft_lstnew(ft_substr(var->line,var->i ,1));
//                 set_OP2(var);
//                 ft_lstadd_back(&var->node, var->tmp);
//                 var->i+=1;
//             }
//         }
//     }
//     return 0;
// }

t_token *tokenizer(t_var *var)
{
    char *strlower;

    while (var->i < var->len)
    {
        while (var->i < var->len && var->line[var->i] == ' ')
            var->i++;
        if (var->i < var->len && var->line[var->i] == '\"')
        {
            var->start = var->i;
            var->i += 1;
            while (var->i < var->len && var->line[var->i] != '\"')
                var->i++;
            var->node = ft_lstnew(ft_substr(var->line,var->start,
                var->i - var->start+1));
            var->i++;
        }
        else if (var->i < var->len && var->line[var->i] == '\'')
        {
            var->start = var->i;
            var->i += 1;
            while (var->i < var->len && var->line[var->i] != '\'')
                var->i++;
            var->node = ft_lstnew(ft_substr(var->line,
                var->start,var->i - var->start+1));
            var->i++;
        }
        else
        {
            if (var->i < var->len && ft_strchr("><|", var->line[var->i]))
            {
                if (var->line[var->i] != '|' && var->i + 1 < var->len && var->line[var->i + 1] == var->line[var->i] && var->i + 2 < var->len && var->line[var->i + 2] != var->line[var->i])
                {
                    var->tmp=ft_lstnew(ft_substr(var->line,var->i,2));
                    var->i += 2;
                    set_OP2(var);
                    ft_lstadd_back(&var->node, var->tmp);
                }
                else if (var->i + 1 < var->len && var->line[var->i + 1] != var->line[var->i])
                {
                    var->tmp=ft_lstnew(ft_substr(var->line,var->i,1));
                    var->i += 1;
                    set_OP2(var);
                    ft_lstadd_back(&var->node, var->tmp);
                }
                while (var->i < var->len && ft_strchr("><|", var->line[var->i]))
                {
                    var->tmp=ft_lstnew(ft_substr(var->line,var->i ,1));
                    set_OP2(var);
                    ft_lstadd_back(&var->node, var->tmp);
                    var->i+=1;
                }
            }
            else if (var->i < var->len )
            {
                var->start = var->i;
                while (var->i < var->len && var->line[var->i] != ' ' && (var->line[var->i] != '\"' || var->line[var->i] != '\'') && !ft_strchr("><|", var->line[var->i]))
                    var->i++;
                var->node = ft_lstnew(ft_substr(var->line,var->start,var->i - var->start));
                set_OP(var);
                strlower = ft_strtolower(ft_strdup((char *)var->node->content));
                if (strlower[0] == '/' || (strlower[0] == '.' && strlower[1] == '/'))
                {
                    if (is_executable(strlower))
                        var->node->type = CMD;
                    else
                        var->node->type = OTHER ;
                }
                else if (ft_strnstr2(strlower))
                    var->node->type = CMD;
                else if (ft_strnstr(ALLOP, (char *)var->node->content, ft_strlen(ALLOP)))
                    set_OP(var);
                else
                {
                    if (((char *)var->node->content)[0] == '-')
                        var->node->type = FLAG;
                    else
                        var->node->type = OTHER;
                }
                free(strlower);
                ft_lstadd_back(&var->head,var->node);
            }
        }
    }
    return (var->head);
}

// t_token *tokenizer(t_var *var)
// {
//     char *strlower;
//     while (var->i < var->len)
//     {
//         tokenizer_split_cmds(var);
//         strlower = ft_strtolower(ft_strdup((char *)var->node->content));
//         if (strlower[0] == '/' || (strlower[0] == '.' && strlower[1] == '/'))
//         {
//             if (is_executable(strlower))
//                 var->node->type = CMD;
//             else
//                 var->node->type = OTHER ;
//         }
//         else if (ft_strnstr2(strlower))
//             var->node->type = CMD;
//         else if (ft_strnstr(ALLOP, (char *)var->node->content, ft_strlen(ALLOP)))
//             set_OP(var);
//         else
//             if (((char *)var->node->content)[0] == '-')
//                 var->node->type = FLAG;
//             else
//                 var->node->type = OTHER;
//         free(strlower);
//         ft_lstadd_back(&var->head,var->node);
//     }
//     return (var->head);
// }

t_token *tokenizer_params(t_var *var)
{
    t_token *t;
    t_token *list;
    t_token *cur;
    int flag;

    t = tokenizer(var);
    list = NULL;
    cur = NULL;
    while (t != NULL)
    {
        flag = 0;
        cur = ft_lstnew(ft_strdup(t->content));
        cur->type = t->type;
        if (cur->type == CMD && t->next && t->next->type <= 0)
        {
            t = t->next; 
            flag = 1;  
            while (t && t->type <= 0)
            {
                cur->content = ft_strjoin(cur->content, " ");
                cur->content = ft_strjoin(cur->content, ((char *)t->content));
                t = t->next;
            }
        }
        else if(ft_strnstr(cur->content , ">",1) != NULL)
        {
            t = t->next; 
            flag = 1;
            while (t && t->type == FLAG)
            {
                cur->content = ft_strjoin(cur->content, " ");
                cur->content = ft_strjoin(cur->content, ((char *)t->content));
                t = t->next;
            } 
        }
        ft_lstadd_back(&list,cur);
        if (t != NULL && flag == 0)
            t = t->next;
    }
    ft_lstclear((t_list **)&var->head, free);
    var->node = list;
    while (var->node != NULL)
    {
        if (var->node->type == OTHER)
        {
            var->index = ft_strchr_int((char *)var->node->content, '=');
            if (var->index != -1)
            {
                ft_lstadd_back_params(&var->var_holder, ft_lstnew_params(
                    ft_substr((char *)var->node->content, 0,var->index),
                    ft_substr((char *)var->node->content, var->index + 1,
                        ft_strlen((char *)var->node->content))));
                var->node->type = VAR;
            }
        }
        var->node = var->node->next;
    }
    return list;
}

int parse_line(char *line) {
    t_var var;

    var.head = NULL;
    var.var_holder = NULL;
    var.i = 0;
    var.line = line;
    var.len = ft_strlen(line);
    execute_cmds(&var);
    return 0;
}