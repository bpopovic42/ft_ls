#include "ft_ls.h"

// TODO: Figure out exactly how files are supposed to be sorted

int ascii_compare(t_file *f1, t_file *f2)
{
	int cmp;

	cmp = ft_strcmp(f1->name, f2->name);
	return cmp <= 0 ? 1 : 0;
}

int ascii_compare_reversed(t_file *f1, t_file *f2)
{
	int cmp;

	cmp = ft_strcmp(f1->name, f2->name);
	return cmp <= 0 ? 0 : 1;
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
