#include "ft_ls.h"

int handle_flag_argument(t_store *store, char *argument)
{
	while (*argument)
	{
		if (!ft_strchr(FT_LS_FLAGS_LIST, *argument))
		{
			ft_printf("%s: invalid option -- '%c'\n", store->program_name,
			          *argument);
			return (EXIT_FAILURE);
		}
		if (*argument == 'a')
			g_flags[0] = 'a';
		else if (*argument == 'l')
			g_flags[1] = 'l';
		else if (*argument == 'r')
			g_flags[2] = 'r';
		else if (*argument == 'R')
			g_flags[3] = 'R';
		else if (*argument == 't')
			g_flags[4] = 't';
		else if (*argument == '-')
			g_flags[5] = '-';
		argument++;
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
		if (arguments[i][0] == '-' && ft_strlen(arguments[i]) > 1 && g_flags[5]
		!= '-') {
			if (handle_flag_argument(store, &arguments[i][1]) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
		}
		else {
			if (handle_path_argument(store, arguments[i]) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
