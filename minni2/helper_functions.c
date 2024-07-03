#include "minishell.h"

t_params	*ft_lstnew_params(char *name, char *value)
{
	t_params	*node;

	node = (t_params *)malloc(sizeof(t_params));
	if (!node)
		return (NULL);
	node->name = name;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_params	*ft_lstlast_params(t_params *lst)
{
	if (lst != NULL)
	{
		while (lst->next != NULL)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

void	ft_lstadd_back_params(t_params **lst, t_params *new)
{
	t_params	*node;

	if (!new)
		return ;
	else if (!lst)
		return ;
	else if (*lst == NULL)
		*lst = new;
	else
	{
		node = ft_lstlast_params(*lst);
		node->next = new;
	}
}

void	free_t_token(t_params **lst)
{
	t_params	*head;

	if (!lst)
		return ;
	while (*lst)
	{
		head = (*lst)->next;
		free((*lst)->name);
        free((*lst)->value);
		free(*lst);
		*lst = head;
	}
}