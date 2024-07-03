#include "minishell.h"

int init_var(t_var *var) {
    var->tokens = NULL;
    return 0;
}

int main(void) {
    t_var var;
    char *line;

    while (1) {
        init_var(&var);
        line = readline("minishell$> ");
        if (!line)
            return (1);
        add_history(line);
        if (parse_line(line))
        {
            free(line);
            ft_lstclear(&var.head,free);
            var.head = NULL;
            return (1);
        }
    }
    return 0;

}