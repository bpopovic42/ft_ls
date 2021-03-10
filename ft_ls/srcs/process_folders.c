#include "ft_ls.h"

void add_subfolders_to_queue(t_node *folders_queue, t_file *parent_folder)
{
	if (parent_folder->sub_folders->size > 0) {
		ft_lstinsert_after(parent_folder->sub_folders, folders_queue);
		parent_folder->sub_folders->head = NULL;
	}
}

int process_folders(t_store *store)
{
	t_node *folders_queue_ptr;
	t_file *folder;

	folders_queue_ptr = store->folders_queue->head;
	folder            = NULL;
	while (folders_queue_ptr)
	{
		folder = folders_queue_ptr->data;
		if (should_process_file(folder)) {
			if (get_folder_files(folder) != EXIT_SUCCESS)
			{
				if (errno != EACCES)
					return (handle_error(store, FT_LS_FATAL_ERROR));
				handle_error(store, FT_LS_ERROR);
			}
			if (folders_queue_ptr != store->folders_queue->head && !folder->error)
				ft_putchar('\n');
			if (process_folder_files(store, folder) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
			add_subfolders_to_queue(folders_queue_ptr, folder);
		}
		folders_queue_ptr = folders_queue_ptr->next;
	}
	return (EXIT_SUCCESS);
}