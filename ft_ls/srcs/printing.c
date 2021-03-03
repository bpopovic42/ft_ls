#include "ft_ls.h"

void print_parent_folder(t_store *store, t_file *parent_folder)
{
	if (g_flags[3] == 'R' || store->nbr_of_file_args > 1)
		ft_printf("%s:\n", parent_folder->path);
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

void print_file_from_node(t_node *file_node)
{
	t_file *file;

	file = file_node->data;
	if (g_flags[1] != 'l')
		ft_printf("%s%s", file->name, file_node->next == NULL ? "\n\n" : "  ");
	else
		ft_printf("%s %d %s %s %s%s%s\n",
			&file->mode,
			file->nbr_of_subfolders,
			file->properties->usr_owner,
			file->properties->grp_owner,
			file->name,
			file->mode.type == 'l' ? " -> " : "",
			file->properties->link
			);
}
