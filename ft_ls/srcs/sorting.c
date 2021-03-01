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

// TODO: What happens when timestamp is the same for 2 files ?

int timestamp_compare(t_file *f1, t_file *f2)
{
	return (f1->timestamp - f2->timestamp <= 0);
}

int timestamp_compare_reversed(t_file *f1, t_file *f2)
{
	return (f1->timestamp - f2->timestamp >= 0);
}

void sort_files(t_list *files)
{
	if (g_flags[4] == 't')
	{
		if (g_flags[2] == 'r')
			ft_lstsort(files, (int (*)(void *, void *))
			timestamp_compare_reversed);
		else
			ft_lstsort(files, (int (*)(void *, void *))timestamp_compare);
	}
	else
	{
		if (g_flags[2] == 'r')
			ft_lstsort(files, (int (*)(void *, void *))ascii_compare_reversed);
		else
			ft_lstsort(files, (int (*)(void *, void *))ascii_compare);
	}
}
