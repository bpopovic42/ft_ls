#include "ft_ls.h"
#include <sys/sysmacros.h>

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
	char *date;
	t_uint64 current_time;

	current_time = time(0);
	date = ctime(&file_stat->st_mtime);
	file->properties->mtime = file_stat->st_mtim.tv_sec * 1000 +
			file_stat->st_mtim.tv_nsec / 1000000;
	ft_strncpy(file->properties->date, date + 4, 7);
	if ((current_time - file_stat->st_mtim.tv_sec) >
		(t_uint64)(SECONDS_IN_A_YEAR / 2))
		ft_strncpy(file->properties->date + 7, date + 19, 5);
	else
		ft_strncpy(file->properties->date + 7, date + 11, 5);
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
	struct stat link_stat;

	if (file->mode.type != 'l')
		return (EXIT_SUCCESS);
	if ((link_size = readlink(file->path, link, PATH_MAX - 1)) < 0)
		return (EXIT_FAILURE);
	if (stat(file->path, &link_stat) < 0)
		return (EXIT_FAILURE);
	get_file_mode(&file->properties->link_mode, &link_stat);
	return (EXIT_SUCCESS);
}

int get_usr_name(struct stat *file_stat, char **usr_name)
{
	struct passwd *pwuid;

	pwuid = getpwuid(file_stat->st_uid);
	if (pwuid == NULL || pwuid->pw_name == NULL)
	{
		if (!(*usr_name = ft_itoa(file_stat->st_uid)))
			return (EXIT_FAILURE);
	}
	else
	{
		if (!(*usr_name = ft_strdup(pwuid->pw_name)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int get_grp_name(struct stat *file_stat, char **grp_name)
{
	struct group *grgid;

	grgid = getgrgid(file_stat->st_gid);
	if (grgid == NULL || grgid->gr_name == NULL)
	{
		if (!(*grp_name = ft_itoa(file_stat->st_gid)))
			return (EXIT_FAILURE);
	}
	else
	{
		if (!(*grp_name = ft_strdup(grgid->gr_name)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int get_usr_and_grp_info(struct stat *file_stat, char **usr_name, char
		**grp_name)
{
	if (get_usr_name(file_stat, usr_name) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (get_grp_name(file_stat, grp_name) != EXIT_SUCCESS)
	{
		ft_strdel(usr_name);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*
** GNU ls uses 1024 bytes blocks
** but st_blocks uses 512 bytes blocks on Linux (defined in S_BLKSIZE)
** Therefore we divide the value of st_blocks by 2 in order to reproduce
** GNU ls's behavior
*/

int get_file_properties(t_file *file, struct stat *file_stat)
{
	char *usr_name;
	char *grp_name;
	char link[PATH_MAX];

	ft_bzero(link, PATH_MAX);
	if (get_usr_and_grp_info(file_stat, &usr_name, &grp_name) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (allocate_properties(file, usr_name, grp_name, link) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	read_link(file, link);
	ft_strcpy(file->properties->usr_owner, usr_name);
	ft_strcpy(file->properties->grp_owner, grp_name);
	ft_strcpy(file->properties->link, link);
	get_file_time(file, file_stat);
	file->hard_links         = file_stat->st_nlink;
	file->properties->size   = file_stat->st_size;
	file->properties->blocks = file_stat->st_blocks / 2;
	if (file->mode.type == 'c' || file->mode.type == 'b')
	{
		file->properties->major_rdev = major(file_stat->st_rdev);
		file->properties->minor_rdev = minor(file_stat->st_rdev);
	}
	ft_strdel(&usr_name);
	ft_strdel(&grp_name);
	return (EXIT_SUCCESS);
}

int read_file_properties(t_file *file)
{
	struct stat file_stat;

	if (lstat(file->path, &file_stat) < 0)
		return (EXIT_FAILURE);
	get_file_mode(&file->mode, &file_stat);
	if (get_file_properties(file, &file_stat) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

