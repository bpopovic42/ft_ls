/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:02:18 by bopopovi          #+#    #+#             */
/*   Updated: 2021/05/03 17:02:58 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	handle_invalid_file(t_store *store, t_file *invalid_file)
{
	invalid_file->error = errno;
	invalid_file->error_msg = "cannot access";
	handle_error(store, errno);
}

void	add_file_to_proper_queue(t_store *store, t_node *file_node)
{
	t_file *file;

	file = file_node->data;
	if (file->error != 0)
		ft_lstpush_back(store->invalid_folders, file_node);
	else if (file->mode.type == 'd' ||
			(!g_flags.option_l && file->properties->link_mode.type == 'd'))
	{
		ft_lstadd(store->folders_queue, file_node);
	}
	else
	{
		file->parent_folder = store->cli_file_arguments_folder;
		ft_lstadd(store->cli_file_arguments_folder->files, file_node);
	}
}

int		parse_path_argument(struct s_store *store, char *argument,
		int is_cli_arg)
{
	struct s_node *new_node;
	struct s_file *new_file;

	new_node = NULL;
	new_file = NULL;
	if (create_new_file(&new_file, argument, NULL) != EXIT_SUCCESS)
	{
		if (errno != ENOENT)
			return (handle_error(store, errno));
		handle_invalid_file(store, new_file);
	}
	if (!(new_node = ft_node_new(NULL, 0)))
		return (handle_error(store, ENOMEM));
	new_file->is_cli_arg = is_cli_arg;
	new_node->data = new_file;
	add_file_to_proper_queue(store, new_node);
	return (EXIT_SUCCESS);
}
