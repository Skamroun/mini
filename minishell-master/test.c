#include "minishell.h"

int main(void)
{
    t_token *token;

    token = ft_lstnew("abc");
    printf("fuck");

    printf("%s", (char*)token->content);
}