#include "libft.h"

void ft_lst_filter(t_list *list, t_list **result, int (f)(t_node *node))
{
	t_node *result_node;
	t_node *node_ptr;

	result_node = NULL;
	node_ptr = list->head;
	while (node_ptr)
	{
		if (f(node_ptr))
		{
			result_node = node_ptr;
			node_ptr = node_ptr->next;
			ft_lstnode_remove(list, result_node);
			ft_lstadd(*result, result_node);
		}
		else
			node_ptr = node_ptr->next;
	}
}