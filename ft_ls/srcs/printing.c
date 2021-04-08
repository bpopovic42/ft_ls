#include "ft_ls.h"

void print_help()
{
	ft_printf("Usage: ./ft_ls [-alRrt]... [FILE]...\n");
}

void print_file_error(t_store *store, t_file *file)
{
	char quotes_type;

	quotes_type = '\'';
	if (file)
	{
		if (ft_strchr(file->path, '\''))
			quotes_type = '"';
		ft_dprintf(2, "%r: %s %c%r%c: %s\n",
		           store->program_name,
		           file->error_msg,
		           quotes_type,
		           file->path,
		           quotes_type,
		           strerror(file->error)
		);
	}
}

void print_parent_folder(t_store *store, t_file *parent_folder)
{
	if (parent_folder->error == 0)
	{
		if (g_flags[3] == 'R' || (store->nbr_of_file_args > 1 &&
			parent_folder->is_cli_arg))
			ft_printf("%r:\n", parent_folder->path);
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
	size_t major_rdev_size;
	size_t minor_rdev_size;

	file = file_node->data;
	major_rdev_size = ft_intlen(file->properties->major_rdev);
	minor_rdev_size = ft_intlen(file->properties->minor_rdev);
	minor_rdev_size = minor_rdev_size < 2 ? 2 : minor_rdev_size;
	if (ft_strlen(file->properties->usr_owner) > padding->file_uid)
		padding->file_uid = ft_strlen(file->properties->usr_owner);
	if (ft_strlen(file->properties->grp_owner) > padding->file_gid)
		padding->file_gid = ft_strlen(file->properties->grp_owner);
	if (ft_intlen(file->hard_links) > padding->file_links)
		padding->file_links = ft_intlen(file->hard_links);
	if (ft_intlen(file->properties->size) > padding->file_size)
		padding->file_size = ft_intlen(file->properties->size);
	if (file->mode.type == 'c' || file->mode.type == 'b')
	{
		if (major_rdev_size > padding->file_major_rdev)
			padding->file_major_rdev = major_rdev_size;
		if (minor_rdev_size > padding->file_minor_rdev)
			padding->file_minor_rdev = minor_rdev_size;
		if (major_rdev_size + minor_rdev_size > padding->file_size) {
			padding->file_size = major_rdev_size + minor_rdev_size;
		}
	}
	return (EXIT_SUCCESS);
}

void print_file_l_flag(t_file *file, t_padding *padding)
{
	size_t major_rdev_padding;

	major_rdev_padding = 0;
	if (padding->file_major_rdev > 0) {
		major_rdev_padding = padding->file_major_rdev + 1;
		padding->file_size += 1;
	}
	if (file->mode.type == 'c' || file->mode.type == 'b')
	{
		ft_printf("%s %*d %-*r %-*r %*d,%*d %s %r%s%r\n",
		          &file->mode,
		          padding->file_links,
		          file->hard_links,
		          padding->file_uid,
		          file->properties->usr_owner,
		          padding->file_gid,
		          file->properties->grp_owner,
		          padding->file_major_rdev,
		          file->properties->major_rdev,
		          padding->file_minor_rdev,
		          file->properties->minor_rdev,
		          file->properties->date,
		          file->name,
		          file->mode.type == 'l' ? " -> " : "",
		          file->properties->link
		);
	}
	else {
		ft_printf("%s %*d %-*r %-*r %*d %s %r%s%r\n",
		          &file->mode,
		          padding->file_links,
		          file->hard_links,
		          padding->file_uid,
		          file->properties->usr_owner,
		          padding->file_gid,
		          file->properties->grp_owner,
		          padding->file_size,
		          file->properties->size,
		          file->properties->date,
		          file->name,
		          file->mode.type == 'l' ? " -> " : "",
		          file->properties->link
		);
	}
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
		ft_printf("%r\n", file->name);
	else
		print_file_l_flag(file, &padding);
}
