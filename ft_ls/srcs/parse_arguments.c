#include "ft_ls.h"

int handle_invalid_flag(t_store *store, char *argument)
{
	ft_dprintf(2, "%s: invalid option -- '%c'\n", store->program_name,
		   *argument);
	ft_dprintf(2, "Try '%s --help' for more information.\n",
	store->program_name);
	return (handle_error(store, FT_LS_FATAL_ERROR));
}

int handle_flag_argument(t_store *store, char *argument)
{
	while (*argument)
	{
		if (!ft_strchr(FT_LS_FLAGS_LIST, *argument))
			return (handle_invalid_flag(store, argument));
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

void handle_invalid_file(t_store *store, t_file *invalid_file)
{
	store->error_status = FT_LS_FATAL_ERROR;
	invalid_file->error = errno;
	invalid_file->error_msg = "cannot access";
}

int handle_path_argument(t_store *store, char *argument)
{
	t_node *new_node;
	t_file *new_folder;

	new_node   = NULL;
	new_folder = NULL;
	if (create_new_file(&new_folder, argument, NULL) != EXIT_SUCCESS)
	{
		if (errno != ENOENT)
			return (handle_error(store, FT_LS_FATAL_ERROR));
		handle_invalid_file(store, new_folder);
	}
	if (!(new_node = ft_node_new(NULL, 0)))
		return (handle_error(store, FT_LS_FATAL_ERROR));
	new_node->data = new_folder;
	if (new_folder->error != 0)
		ft_lstpush_back(store->invalid_folders, new_node);
	else if (new_folder->mode.type == 'd'){
		ft_lstadd(store->folders_queue, new_node);
		store->nbr_of_file_args += 1; // TODO : what's that
	}
	else {
		new_folder->parent_folder = store->cli_file_arguments_folder;
		ft_lstadd(store->cli_file_arguments_folder->files, new_node);
	}
	return (EXIT_SUCCESS);
}

int parse_arguments(int arg_count, char **arguments, t_store *store)
{
	int    i;

	i          = 0;
	while (i < arg_count) {
		if (arguments[i][0] == '-' && ft_strlen(arguments[i]) > 1 && g_flags[5]
		!= '-') {
			if (handle_flag_argument(store, &arguments[i][1]) != EXIT_SUCCESS)
				return (handle_error(store, FT_LS_FATAL_ERROR));
		}
		else {
			if (handle_path_argument(store, arguments[i]) != EXIT_SUCCESS)
				return (handle_error(store, FT_LS_FATAL_ERROR));
		}
		i++;
	}
	if (store->folders_queue->size == 0 &&
		store->invalid_folders->size == 0 &&
		store->cli_file_arguments_folder->files->size == 0)
	{
		if (handle_path_argument(store, ".") != EXIT_SUCCESS)
			return (handle_error(store, FT_LS_FATAL_ERROR));
	}
	return (EXIT_SUCCESS);
}
