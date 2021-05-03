#include "ft_ls.h"

int read_link(t_file *file, char *link)
{
	if (file->mode.type == 'l') {
		if (readlink(file->path, link, PATH_MAX - 1) < 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int read_link_properties(t_file *file)
{
	struct stat link_stat;

	if (file->mode.type != 'l')
		return (EXIT_SUCCESS);
	if (stat(file->path, &link_stat) < 0)
		return (EXIT_FAILURE);
	get_file_mode(&file->properties->link_mode, &link_stat);
	return (EXIT_SUCCESS);
}

