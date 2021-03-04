#include "libft.h"

/*
** Applies function 'apply' to all list nodes
** Returns EXIT_FAILURE if 'apply' does not return successfully
** Returns EXIT_SUCCESS otherwise
*/

int ft_lstapply(t_list *lst, int (apply)(t_node *node))
{
	t_node *node_ptr;

	node_ptr = lst->head;
	while (node_ptr)
	{
		if (apply(node_ptr) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		node_ptr = node_ptr->next;
	}
	return (EXIT_SUCCESS);
}
