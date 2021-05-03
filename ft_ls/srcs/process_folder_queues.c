#include "ft_ls.h"

void process_cli_files(t_store *store)
{
	if (store->cli_file_arguments_folder->files->size > 0) {
		ft_lstiter(store->cli_file_arguments_folder->files,
		           &print_file_from_node);
		if (store->folders_queue->size > 0)
			ft_putchar('\n');
	}
}

void process_invalid_folders(t_store *store)
{
	t_node *invalid_folder_ptr;
	t_file *invalid_folder;

	invalid_folder_ptr = store->invalid_folders->head;
	while (invalid_folder_ptr) {
		invalid_folder = invalid_folder_ptr->data;
		print_file_error(store, invalid_folder);
		invalid_folder_ptr = invalid_folder_ptr->next;
	}
}

void process_folder_queues(t_store *store)
{
	sort_files(store->folders_queue);
	sort_files(store->cli_file_arguments_folder->files);
	process_invalid_folders(store);
	process_cli_files(store);
	process_main_folders_queue(store);
}