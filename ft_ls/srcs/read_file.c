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

int get_file_time(t_file *file, struct stat *file_stat)
{
	file->properties->timestamp = file_stat->st_mtime;
	return (EXIT_SUCCESS);
}

int allocate_properties(t_file *file, char *pw_name, char *gr_name, char *link)
{
	ulong sizeof_pw_name;
	ulong sizeof_gr_name;
	ulong sizeof_link;
	ulong allocation_size;
	void *memory_block;

	sizeof_pw_name = ft_strlen(pw_name) + 1;
	sizeof_gr_name = ft_strlen(gr_name) + 1;
	sizeof_link = ft_strlen(link) + 1;
	allocation_size = sizeof(t_properties) + sizeof_pw_name + sizeof_gr_name
	                  + sizeof_link;
	if (!(memory_block = ft_memalloc(allocation_size)))
		return (EXIT_FAILURE);
	file->properties = memory_block;
	file->properties->usr_owner = memory_block + sizeof(t_properties);
	file->properties->grp_owner = file->properties->usr_owner + sizeof_pw_name;
	file->properties->link = file->properties->grp_owner + sizeof_gr_name;
	file->properties->struct_size = allocation_size;
	return (EXIT_SUCCESS);
}

int read_link(t_file *file, char *link)
{
	ssize_t link_size;

	if (file->mode.type != 'l')
		return (EXIT_SUCCESS);
	if ((link_size = readlink(file->path, link, PATH_MAX - 1)) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int get_file_properties(t_file *file, struct stat *file_stat)
{
	struct passwd *pwuid;
	struct group *grgid;
	char link[PATH_MAX];

	ft_bzero(link, PATH_MAX);
	if (!(pwuid = getpwuid(file_stat->st_uid)))
		return (EXIT_FAILURE);
	if (!(grgid = getgrgid(file_stat->st_gid)))
		return (EXIT_FAILURE);
	if (read_link(file, link) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	allocate_properties(file, pwuid->pw_name, grgid->gr_name, link);
	ft_strcpy(file->properties->usr_owner, pwuid->pw_name);
	ft_strcpy(file->properties->grp_owner, grgid->gr_name);
	ft_strcpy(file->properties->link, link);
	get_file_time(file, file_stat);
	file->properties->size = file_stat->st_size;
	return (EXIT_SUCCESS);
}

int read_file_properties(t_file *file)
{
	struct stat file_stat;

	if (lstat(file->path, &file_stat) < 0)
		return (EXIT_FAILURE);
	get_file_mode(&file->mode, &file_stat);
	get_file_properties(file, &file_stat);
	return (EXIT_SUCCESS);
}

