#include "libft.h"

/*
** Maps list by applying function 'map' to each of its nodes and providing
** the variable '**res' for 'map' to store its results
** Returns EXIT_FAILURE if 'map' does not return successfully
** Returns EXIT_SUCCESS otherwise
*/

int ft_lstmap(t_list *lst, void *res, int (map)(t_node *node, void *res))
{
	t_node *node_ptr;

	node_ptr = lst->head;
	while (node_ptr)
	{
		if (map(node_ptr, res) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		node_ptr = node_ptr->next;
	}
	return (EXIT_SUCCESS);
}
