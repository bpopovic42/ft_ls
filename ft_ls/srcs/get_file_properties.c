#include "ft_ls.h"
#include <sys/sysmacros.h>

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
		return (ENOMEM);
	file->properties = memory_block;
	file->properties->usr_owner = memory_block + sizeof(t_properties);
	file->properties->grp_owner = file->properties->usr_owner + sizeof_pw_name;
	file->properties->link = file->properties->grp_owner + sizeof_gr_name;
	file->properties->struct_size = allocation_size;
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
	read_link(file, link);
	if (get_usr_and_grp_info(file_stat, &usr_name, &grp_name) != EXIT_SUCCESS)
		return (ENOMEM);
	if (allocate_properties(file, usr_name, grp_name, link) != EXIT_SUCCESS)
		return (ENOMEM);
	read_link_properties(file);
	ft_strcpy(file->properties->usr_owner, usr_name);
	ft_strcpy(file->properties->grp_owner, grp_name);
	ft_strcpy(file->properties->link, link);
	get_file_time(file, file_stat);
	file->hard_links         = file_stat->st_nlink;
	file->properties->size   = file_stat->st_size;
	file->properties->blocks = file_stat->st_blocks / 2;
	file->properties->major_rdev = major(file_stat->st_rdev);
	file->properties->minor_rdev = minor(file_stat->st_rdev);
	ft_strdel(&usr_name);
	ft_strdel(&grp_name);
	return (EXIT_SUCCESS);
}
