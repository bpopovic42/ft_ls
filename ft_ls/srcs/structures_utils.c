#include "ft_ls.h"

int init_store(t_store *store, char *program_name)
{
	ft_bzero(store, sizeof(t_store));
	if (!(store->folders_queue = ft_lstnew()))
		return (EXIT_FAILURE);
	store->program_name = program_name;
	return (EXIT_SUCCESS);
}

void clean_store(t_store *store)
{
	ft_lstdel(store->folders_queue, (void (*)(void *, size_t))del_file);
	ft_bzero(store, sizeof(t_store));
}