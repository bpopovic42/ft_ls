#include "ft_ls.h"

int read_file_properties(t_file *file)
{
	struct stat file_stat;

	if (lstat(file->path, &file_stat) < 0)
		return (EXIT_FAILURE);
	file->type = file_stat.st_mode;
	return (EXIT_SUCCESS);
}

