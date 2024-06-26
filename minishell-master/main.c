#include "minishell.h"

int init_var(t_var *var) {
    var->tokens = NULL;
    return 0;
}

int main(void) {
    t_var var;
    char *line;

    init_var(&var);
    while (1) {
        line = readline("minishell$> ");
        if (!line)
            return (1);
        if (parse_line(line))
        {
            free(line);
            return (1);
        }
    }
    return 0;

}