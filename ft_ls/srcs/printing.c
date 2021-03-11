#include "ft_ls.h"

void print_help()
{
	ft_printf("Usage: ./ft_ls [-alRrt]... [FILE]...\n");
}

void print_file_error(t_store *store, t_file *file)
{
	if (file)
	{
		ft_dprintf(2, "%s: %s '%s': %s\n",
		           store->program_name,
		           file->error_msg,
		           file->path,
		           strerror(file->error)
		);
	}
}
void print_parent_folder(t_store *store, t_file *parent_folder)
{
	if (parent_folder->error == 0)
	{
		if (g_flags[3] == 'R' || store->nbr_of_file_args > 1)
			ft_printf("%s:\n", parent_folder->path);
		if (g_flags[1] == 'l')
			ft_printf("total %d\n", parent_folder->properties->total_blocks);
	}
	else
		print_file_error(store, parent_folder);
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

int get_paddings(t_node *file_node, t_padding *padding)
{
	t_file *file;

	file = file_node->data;
	if (ft_strlen(file->properties->usr_owner) > padding->file_uid)
		padding->file_uid = ft_strlen(file->properties->usr_owner);
	if (ft_strlen(file->properties->grp_owner) > padding->file_gid)
		padding->file_gid = ft_strlen(file->properties->usr_owner);
	if (ft_intlen(file->hard_links) > padding->file_links)
		padding->file_links = ft_intlen(file->hard_links);
	if (ft_intlen(file->properties->size) > padding->file_size)
		padding->file_size = ft_intlen(file->properties->size);
	return (EXIT_SUCCESS);
}

void print_file_from_node(t_node *file_node)
{
	t_file *file;
	t_padding padding;

	file = file_node->data;
	ft_bzero(&padding, sizeof(padding));
	ft_lstmap(file->parent_folder->files, (void*)&padding,
			(int (*)(t_node *, void *))&get_paddings);
	if (g_flags[1] != 'l')
		ft_printf("%s\n", file->name);
	else
		ft_printf("%s %*d %-*s %-*s %*d %s %s%s%s\n",
			&file->mode,
			padding.file_links,
			file->hard_links,
			padding.file_uid,
			file->properties->usr_owner,
			padding.file_gid,
			file->properties->grp_owner,
			padding.file_size,
			file->properties->size,
			file->properties->date,
			file->name,
			file->mode.type == 'l' ? " -> " : "",
			file->properties->link
			);
}
