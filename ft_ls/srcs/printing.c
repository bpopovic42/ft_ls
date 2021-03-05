#include "ft_ls.h"

void print_parent_folder(t_store *store, t_file *parent_folder)
{
	if (g_flags[3] == 'R' || store->nbr_of_file_args > 1)
		ft_printf("%s:\n", parent_folder->path);
	if (g_flags[1] == 'l')
		ft_printf("total %d\n", parent_folder->properties->total_blocks);
}

// TODO: Issue : Space is added after last file printed if there's a \
//  non-processed file after it in the list (hidden file without -a for
//  instance)
void print_file(t_file *file, int is_last_file)
{
	if (g_flags[1] != 'l')
		ft_printf("%s%s", file->name, is_last_file ? "\n\n" : "  ");
	else
		ft_printf("%s %s\n", &file->mode, file->name);
}

int get_longest_file_size(t_node *file_node, int *result)
{
	t_file *file;
	int file_size_length;

	file = file_node->data;
	file_size_length = ft_intlen(file->properties->size);
	if (file_size_length > *result)
		*result = file_size_length;
	return (EXIT_SUCCESS);
}

void print_file_from_node(t_node *file_node)
{
	t_file *file;
	int l_flag_size_padding;

	file = file_node->data;
	l_flag_size_padding = 0;
	ft_lstmap(file->parent_folder->files, (void*)&l_flag_size_padding,
	          (int (*)(t_node *, void *))&get_longest_file_size);
	if (g_flags[1] != 'l')
		ft_printf("%s%s", file->name, file_node->next == NULL ? "\n\n" : "  ");
	else
		ft_printf("%s %d %s %s %*d %s %s%s%s%s\n",
			&file->mode,
			file->nbr_of_subfolders,
			file->properties->usr_owner,
			file->properties->grp_owner,
			l_flag_size_padding,
			file->properties->size,
			file->properties->date,
			file->name,
			file->mode.type == 'l' ? " -> " : "",
			file->properties->link,
			file_node->next == NULL ? "\n" : ""
			);
}
