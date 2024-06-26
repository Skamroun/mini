#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <stdio.h>
#include <stdlib.h> 
#include <readline/readline.h>


typedef struct s_list t_token;

typedef struct s_var
{
    t_token *tokens;
} t_var;

int parse_line(char *line);

#endif