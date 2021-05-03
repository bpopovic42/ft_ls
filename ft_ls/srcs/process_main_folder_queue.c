/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_main_folder_queue.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:56:10 by bopopovi          #+#    #+#             */
/*   Updated: 2021/05/03 16:57:57 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	add_subfolders_to_queue(t_node *folders_queue, t_file *parent_folder)
{
	if (parent_folder->sub_folders->size > 0)
	{
		ft_lstinsert_after(parent_folder->sub_folders, folders_queue);
		parent_folder->sub_folders->head = NULL;
		parent_folder->sub_folders->tail = NULL;
	}
}

int		process_folder(t_store *store, t_file *folder)
{
	int error_status;

	if ((error_status = get_folder_files(folder)) != EXIT_SUCCESS)
	{
		if (handle_error(store, error_status) > FT_LS_ERROR)
			return (EXIT_FAILURE);
	}
	if (process_folder_files(store, folder) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		should_process_folder(t_file *file)
{
	return (!(file->name[0] == '.' && !g_flags.option_a &&
			!ft_strequ(file->name, file->path)));
}

int		process_main_folders_queue(t_store *store)
{
	t_file *folder;
	t_node *folders_queue_ptr;

	folder = NULL;
	folders_queue_ptr = store->folders_queue->head;
	while (folders_queue_ptr)
	{
		folder = folders_queue_ptr->data;
		if (should_process_folder(folder))
		{
			if (process_folder(store, folder) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
			add_subfolders_to_queue(folders_queue_ptr, folder);
		}
		folders_queue_ptr = folders_queue_ptr->next;
	}
	return (EXIT_SUCCESS);
}
