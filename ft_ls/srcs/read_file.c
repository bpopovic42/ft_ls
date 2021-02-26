#include "ft_ls.h"

void get_file_mode(t_mode *mode, struct stat *file_stat)
{
	if (S_ISBLK(file_stat->st_mode))
		mode->type = 'b';
	else if (S_ISCHR(file_stat->st_mode))
		mode->type = 'c';
	else if (S_ISDIR(file_stat->st_mode))
		mode->type = 'd';
	else if (S_ISLNK(file_stat->st_mode))
		mode->type = 'l';
	else if (S_ISFIFO(file_stat->st_mode))
		mode->type = 'p';
	else if (S_ISSOCK(file_stat->st_mode))
		mode->type = 's';
	mode->usr_read = (S_IRUSR & file_stat->st_mode ? 'r' : '-');
	mode->usr_write = (S_IWUSR & file_stat->st_mode ? 'w' : '-');
	mode->usr_exec = (S_IXUSR & file_stat->st_mode ? 'x' : '-');
	mode->usr_exec = (S_ISUID & file_stat->st_mode ? 's' : mode->usr_exec);
	mode->grp_read = (S_IRGRP & file_stat->st_mode ? 'r' : '-');
	mode->grp_write = (S_IWGRP & file_stat->st_mode ? 'w' : '-');
	mode->grp_exec = (S_IXGRP & file_stat->st_mode ? 'x' : '-');
	mode->grp_exec = (S_ISGID & file_stat->st_mode ? 's' : mode->grp_exec);
	mode->oth_read = (S_IROTH & file_stat->st_mode ? 'r' : '-');
	mode->oth_write = (S_IWOTH & file_stat->st_mode ? 'w' : '-');
	mode->oth_exec = (S_IXOTH & file_stat->st_mode ? 'x' : '-');
	mode->oth_exec = (S_ISVTX & file_stat->st_mode ? 't' : mode->oth_exec);
}

int read_file_properties(t_file *file)
{
	struct stat file_stat;

	if (lstat(file->path, &file_stat) < 0)
		return (EXIT_FAILURE);
	get_file_mode(&file->mode, &file_stat);
	return (EXIT_SUCCESS);
}

