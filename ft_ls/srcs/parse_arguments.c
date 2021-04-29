#include "ft_ls.h"

int handle_invalid_flag(t_store *store, char *argument)
{
	ft_dprintf(2, "%s: invalid option -- '%c'\n", store->program_name,
		   *argument);
	ft_dprintf(2, "Try '%s --help' for more information.\n",
	store->program_name);
	return (handle_error(store, FT_LS_FATAL_ERROR));
}

int handle_unrecognized_flag(t_store *store, char *argument)
{
	ft_dprintf(2, "%s: unrecognized option '%s'\n", store->program_name,
	           argument);
	ft_dprintf(2, "Try '%s --help' for more information.\n",
	           store->program_name);
	return (handle_error(store, FT_LS_FATAL_ERROR));
}

int handle_flag_argument(t_store *store, char *argument)
{
	int i;

	i = 1;
	if (!ft_strcmp(argument, "--"))
		g_flags.option_stop = true;
	else {
		while (argument[i]) {
			if (argument[i] == '-' && i == 1)
				return (handle_unrecognized_flag(store, argument));
			else if (!ft_strchr(FT_LS_FLAGS_LIST, argument[i]))
				return (handle_invalid_flag(store, argument + i));
			else if (argument[i] == 'a')
				g_flags.option_a = true;
			else if (argument[i] == 'l')
				g_flags.option_l = true;
			else if (argument[i] == 'r')
				g_flags.option_r = true;
			else if (argument[i] == 'R')
				g_flags.option_R = true;
			else if (argument[i] == 't')
				g_flags.option_t = true;
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

void handle_invalid_file(t_store *store, t_file *invalid_file)
{
	store->error_status = FT_LS_FATAL_ERROR;
	store->error_type = errno;
	invalid_file->error = errno;
	invalid_file->error_msg = "cannot access";
}

int handle_path_argument(t_store *store, char *argument, int is_cli_arg)
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
		return (handle_error(store, ENOMEM));
	new_node->data = new_folder;
	if (new_folder->error != 0)
		ft_lstpush_back(store->invalid_folders, new_node);
	else if (new_folder->mode.type == 'd' ||
		(!g_flags.option_l && new_folder->mode.type == 'l' &&
		new_folder->properties->link_mode
		.type == 'd')) {
		ft_lstadd(store->folders_queue, new_node);
	}
	else {
		new_folder->parent_folder = store->cli_file_arguments_folder;
		ft_lstadd(store->cli_file_arguments_folder->files, new_node);
	}
	new_folder->is_cli_arg = is_cli_arg;
	return (EXIT_SUCCESS);
}

int argument_is_a_flag(char *argument)
{
	if (argument[0] == '-' && ft_strlen(argument) > 1 && !g_flags.option_stop)
		return 1;
	return 0;
}

int parse_arguments(t_store *store, int arg_count, char **arguments)
{
	int    i;

	i          = 0;
	while (i < arg_count) {
		if (argument_is_a_flag(arguments[i])) {
			if (handle_flag_argument(store, &arguments[i][0]) != EXIT_SUCCESS)
				return (handle_error(store, FT_LS_FATAL_ERROR));
		}
		else {
			store->nbr_of_file_args += 1;
			if (handle_path_argument(store, arguments[i], 1) != EXIT_SUCCESS)
				return (FT_LS_FATAL_ERROR);
		}
		i++;
	}
	if (store->folders_queue->size == 0 &&
		store->invalid_folders->size == 0 &&
		store->cli_file_arguments_folder->files->size == 0)
	{
		if (handle_path_argument(store, ".", 0) != EXIT_SUCCESS)
			return (FT_LS_FATAL_ERROR);
	}
	return (EXIT_SUCCESS);
}
