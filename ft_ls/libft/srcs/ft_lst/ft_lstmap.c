#include "libft.h"

int ft_lstmap(t_list *lst, t_list *result, int (f)(t_node *node, t_node
**result))
{
	t_node *node_ptr;
	t_node *result_node;

	node_ptr = lst->head;
	while (node_ptr)
	{
		result_node = NULL;
		if (f(node_ptr, &result_node) == -1)
			return (EXIT_FAILURE);
		if (result_node != NULL)
			ft_lstadd(result, result_node);
		node_ptr = node_ptr->next;
	}
	return (EXIT_SUCCESS);
}