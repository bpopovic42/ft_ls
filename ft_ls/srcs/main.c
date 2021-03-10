#include "ft_ls.h"

int exit_clean(t_store *store)
{
	int status;

	status = store->error_status;
	if (status > FT_LS_ERROR && status != ENOENT && status != EACCES)
		ft_dprintf(2, "%s: %s\n", store->program_name, strerror(status));
	clean_store(store);
	return (status);
}

void print_invalid_folders(t_store *store)
{
	t_node *invalid_folder_ptr;
	t_file *invalid_folder;

	if (store->invalid_folders->size > 1)
		ft_lstsort(store->invalid_folders, (int (*)(void *, void *))&ascii_compare);
	invalid_folder_ptr = store->invalid_folders->head;
	while (invalid_folder_ptr)
	{
		invalid_folder = invalid_folder_ptr->data;
		print_file_error(store, invalid_folder);
		invalid_folder_ptr = invalid_folder_ptr->next;
	}
}

int main(int ac, char **av)
{
	t_store store;

	(void)ac;
	if ((init_store(&store, av[0])) != EXIT_SUCCESS)
		return (exit_clean(&store));
	if ((parse_arguments(av + 1, &store)) != EXIT_SUCCESS)
		return (exit_clean(&store));
	sort_files(store.folders_queue);
	print_invalid_folders(&store);
	process_folders(&store);
	return (exit_clean(&store));
}
