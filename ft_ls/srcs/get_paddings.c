#include "ft_ls.h"

void set_special_file_padding(t_padding *padding,
							  size_t major_rdev_size, size_t minor_rdev_size)
{
	if (major_rdev_size > padding->file_major_rdev)
		padding->file_major_rdev = major_rdev_size;
	if (minor_rdev_size > padding->file_minor_rdev)
		padding->file_minor_rdev = minor_rdev_size;
	if (major_rdev_size + minor_rdev_size > padding->file_size) {
		padding->file_size = major_rdev_size + minor_rdev_size;
	}
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
		set_special_file_padding(padding, major_rdev_size, minor_rdev_size);
	return (EXIT_SUCCESS);
}