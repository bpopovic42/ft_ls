#include "ft_ls.h"

int init_store(t_store *store, char *program_name)
{
	ft_bzero(store, sizeof(t_store));
	if (!(store->folders_queue = ft_lstnew()))
		return (handle_error(store, FT_LS_FATAL_ERROR));
	if (!(store->invalid_folders = ft_lstnew()))
		return (handle_error(store, FT_LS_FATAL_ERROR));
	if (create_new_file(&store->cli_file_arguments_folder, "", "") != EXIT_SUCCESS)
		return (handle_error(store, FT_LS_FATAL_ERROR));
	store->program_name = program_name;
	return (EXIT_SUCCESS);
}

void clean_store(t_store *store)
{
	ft_lstdel(store->folders_queue, (void (*)(void *, size_t))del_file);
	ft_lstdel(store->invalid_folders, (void (*)(void *, size_t))del_file);
	if (NULL != store->cli_file_arguments_folder)
		del_file(store->cli_file_arguments_folder,
		   store->cli_file_arguments_folder->struct_size);
	ft_bzero(store, sizeof(t_store));
}