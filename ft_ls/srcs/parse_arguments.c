#include "ft_ls.h"

int handle_flag_argument(t_store *store, char *argument)
{
	if (!ft_strcmp(argument, "--"))
	{
		store->flags_end = true;
		return (EXIT_SUCCESS);
	}
	else
	{
		while (++argument)
		{
			if (*argument == 'a')
				store->flags[0] = 'a';
			else if (*argument == 'l')
				store->flags[1] = 'l';
			else if (*argument == 'r')
				store->flags[2] = 'r';
			else if (*argument == 'R')
				store->flags[3] = 'R';
			else if (*argument == 't')
				store->flags[4] = 't';
			else
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int handle_path_argument(t_store *store, char *argument)
{
	t_node *new_node;
	t_file *new_folder;

	new_node   = NULL;
	new_folder = NULL;
	if (create_new_file(&new_folder, argument, NULL) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (!(new_node = ft_node_new(NULL, 0)))
		return (EXIT_FAILURE);
	new_node->data = new_folder;
	ft_lstadd(store->folders_queue, new_node);
	store->nbr_of_file_args += 1;
	return (EXIT_SUCCESS);
}

int parse_arguments(char **arguments, t_store *store)
{
	int    i;

	i          = 0;
	while (arguments[i]) {
		if (arguments[i][0] == '-' && !store->flags_end)
			handle_flag_argument(store, arguments[i]);
		else {
			if (handle_path_argument(store, arguments[i]) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
