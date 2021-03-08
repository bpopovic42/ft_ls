#include "ft_ls.h"

int exit_clean(t_store *store, int error_status)
{
	clean_store(store);
	if (error_status != EXIT_SUCCESS)
		perror("Error");
	return (error_status);
}

int main(int ac, char **av)
{
	t_store store;
	int     error_status;

	(void)ac;
	if ((error_status = init_store(&store, av[0])) != EXIT_SUCCESS)
		return (exit_clean(&store, error_status));
	if ((error_status = parse_arguments(av + 1, &store)) != EXIT_SUCCESS)
		return (exit_clean(&store, error_status));
	sort_files(store.folders_queue);
	error_status = process_folders(&store);
	return (exit_clean(&store, error_status));
}
