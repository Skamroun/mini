#include "minishell.h"

int parse_line(char *line) {
    int i;
    int j;

    i = 0;
    j = 0;
    while (line[i]) {
        
        while (line[i] == ' ')
            i++;
        while (line[i] && line[i] != ' ')
            j++;
        i++;
    }
    return 0;
}