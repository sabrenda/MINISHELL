#include "../minishell.h"

int	ft_lenmassive(char **str) // счетчик строк в 2-ном массиве
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	ft_list_clear(t_list **head)
{
	t_list	*tmp;
	t_list	*list;

	list = *head;
	tmp = NULL;
	while (list)
	{
		if (list->next)
			tmp = list->next;
		else
			tmp = NULL;
		free(list->content);
		free(list);
		list = tmp;
	}
}
