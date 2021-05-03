#include "ft_ls.h"

int exit_clean(t_store *store)
{
	int exit_code;

	exit_code = store->error.exit_code;
	if (store->error.exit_code > FT_LS_ERROR)
		if (store->error.type != EACCES && store->error.type != ENOENT)
			ft_dprintf(2, "%s: %s\n", store->program_name,
			  store->error.message);
	clean_store(store);
	return (exit_code);
}

int help_flag_requested(int ac, char **av)
{
	int i;

	i = 0;
	while (i < ac) {
		if (ft_strequ(av[i], "--help"))
			return (1);
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	t_store store;

	if (help_flag_requested(ac - 1, av + 1))
		print_help();
	else {
		if ((init_store(&store, av[0])) != EXIT_SUCCESS)
			return (exit_clean(&store));
		if ((parse_arguments(&store, ac - 1, av + 1)) != EXIT_SUCCESS)
			return (exit_clean(&store));
		process_folder_queues(&store);
	}
	return (exit_clean(&store));
}
