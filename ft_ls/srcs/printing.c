/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:59:54 by bopopovi          #+#    #+#             */
/*   Updated: 2021/05/03 18:02:31 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_help(void)
{
	ft_printf("Usage: ./ft_ls [-alRrt]... [FILE]...\n");
}

void	print_file_error(t_store *store, t_file *file)
{
	char quotes_type;

	quotes_type = '\'';
	if (file)
	{
		if (ft_strchr(file->path, '\''))
			quotes_type = '"';
		ft_dprintf(2, "%r: %s %c%r%c: %s\n",
					store->program_name,
					file->error_msg,
					quotes_type,
					file->path,
					quotes_type,
					strerror(file->error));
	}
}

void	print_parent_folder(t_store *store, t_file *parent_folder)
{
	if (parent_folder->error == 0)
	{
		if (parent_folder != store->folders_queue->head->data)
			ft_putchar('\n');
		if (g_flags.option_upper_r || (store->nbr_of_file_args > 1 &&
			parent_folder->is_cli_arg))
			ft_printf("%r:\n", parent_folder->path);
		if (g_flags.option_l)
			ft_printf("total %d\n", parent_folder->properties->total_blocks);
	}
	else
		print_file_error(store, parent_folder);
}

void	print_file_from_node(t_node *file_node)
{
	t_file		*file;
	t_padding	padding;

	file = file_node->data;
	ft_bzero(&padding, sizeof(padding));
	ft_lstmap(file->parent_folder->files, (void*)&padding,
			(int (*)(t_node *, void *))&get_paddings);
	if (!g_flags.option_l)
		ft_printf("%r\n", file->name);
	else
		print_file_l_flag(file, &padding);
}
