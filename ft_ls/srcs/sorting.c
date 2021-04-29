#include "ft_ls.h"

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

int timestamp_compare(t_file *f1, t_file *f2)
{

	if (f1->properties->mtime == f2->properties->mtime)
		return ascii_compare(f1, f2);
	return (f1->properties->mtime > f2->properties->mtime);
}

int timestamp_compare_reversed(t_file *f1, t_file *f2)
{
	if (f1->properties->mtime == f2->properties->mtime)
		return ascii_compare_reversed(f1, f2);
	return (f1->properties->mtime < f2->properties->mtime);
}

void sort_files(t_list *files)
{
	if (g_flags.option_t)
	{
		if (g_flags.option_r)
			ft_lstsort(files, (int (*)(void *, void *))
			timestamp_compare_reversed);
		else
			ft_lstsort(files, (int (*)(void *, void *))timestamp_compare);
	}
	else
	{
		if (g_flags.option_r)
			ft_lstsort(files, (int (*)(void *, void *))ascii_compare_reversed);
		else
			ft_lstsort(files, (int (*)(void *, void *))ascii_compare);
	}
}
