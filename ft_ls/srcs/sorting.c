#include "ft_ls.h"

int ascii_compare(t_file *f1, t_file *f2)
{
	int i;

	i = 0;
	while (ft_tolower(f1->name[i]) == ft_tolower(f2->name[i]))
		i++;
	if (ft_tolower(f1->name[i]) - ft_tolower(f2->name[i]) < 0)
		return (1);
	return (0);
}

int ascii_compare_reversed(t_file *f1, t_file *f2)
{
	int i;

	i = 0;
	while (ft_tolower(f1->name[i]) == ft_tolower(f2->name[i]))
		i++;
	if (ft_tolower(f1->name[i]) - ft_tolower(f2->name[i]) >= 0)
		return (1);
	return (0);
}

void sort_files(t_store *store, t_list *files)
{
	if (store->flags[4] == 't')
	{
		; // TODO: Implement file time
	}
	else
	{
		if (store->flags[2] == 'r')
			ft_lstsort(files, (int (*)(void *, void *))ascii_compare_reversed);
		else
			ft_lstsort(files, (int (*)(void *, void *))ascii_compare);
	}
}
