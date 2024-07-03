#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <stdio.h>
#include <stdlib.h> 
#include <readline/readline.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/history.h>
#include <sys/wait.h>

#define CMD    0
#define OTHER -1
#define VAR   -2
#define FLAG  -3
#define DOLLAR -4

#define ALLCMD  " echo cd pwd export unset env exit "
#define ALLOP  " | && || > < >> << $? "

typedef struct s_list t_token;

enum OP {PIPE = 1, AND, GREATER, LESS, DGREATER, DLESS, DQUESTION};

typedef struct s_params
{
    char *name;
    char *value;
    struct s_params *next;
}   t_params;

typedef struct s_exec
{
    t_token *cmds;
}   t_exec;


typedef struct s_var
{
    t_token *head;
    t_token *tmp;
    t_token *cmd_to_execute;
    size_t len;
    size_t start;
    size_t i;
    t_token *node;
    t_token *tokens;
    t_params *params;
    t_params *var_holder;
    char *line;
    int index;
} t_var;


int parse_line(char *line);


/*
** helper_functions.c
*/
t_params	*ft_lstnew_params(char *name, char *value);
t_params	*ft_lstlast_params(t_params *lst);
void	ft_lstadd_back_params(t_params **lst, t_params *new);

/*
** parsing.c
*/
t_token *tokenizer_params(t_var *var);
int set_OP(t_var *var);
int set_OP2(t_var *var);

/*
** execution.c
*/
int execute_cmds(t_var *var);
void    free_double_pointer(char ***args);


/*
** built_in.c
*/
int ft_echo(char **arg);
int ft_cd(char **arg);
int ft_pwd();
int ft_export(char **arg);
int ft_unset(char **arg);
int ft_env();
int ft_exit(char **arg);
#endif