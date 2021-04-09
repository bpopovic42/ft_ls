#include "ft_ls.h"

int exit_error(t_file **file_to_clean)
{
	if (*file_to_clean && errno != ENOENT)
		del_file(*file_to_clean, (*file_to_clean)->struct_size);
	return (EXIT_FAILURE);
}

int allocate_new_file(t_file **new_file, char *name, char *parent_path)
{
	ulong sizeof_name;
	ulong sizeof_path;
	ulong sizeof_parent_path;
	ulong allocation_size;
	void  *memory_block;

	sizeof_name        = ft_strlen(name) + 1;
	sizeof_parent_path = !parent_path ? 0 : ft_strlen(parent_path) + 1;
	sizeof_path        = sizeof_name + sizeof_parent_path + 1;
	allocation_size    = sizeof(t_file) + sizeof_name + sizeof_path;
	if (!(memory_block = ft_memalloc(allocation_size)))
		return exit_error(new_file);
	*new_file = memory_block;
	(*new_file)->name        = memory_block + sizeof(t_file);
	(*new_file)->path        = memory_block + sizeof(t_file) + sizeof_name;
	(*new_file)->struct_size = allocation_size;
	ft_memset(&(*new_file)->mode, '-', sizeof(t_mode));
	return (EXIT_SUCCESS);
}

void build_file_path(char *file_path, char *parent_file_path, char *file_name)
{
	size_t i;

	i = 0;
	if (parent_file_path)
	{
		i = ft_strlen(parent_file_path);
		while (i > 0) {
			if (parent_file_path[i] != '/' && parent_file_path[i] != '\0')
				break;
			i--;
		}
		ft_strncpy(file_path, parent_file_path, i + 1);
		ft_strcatn(file_path, 2, "/\0", file_name);
	}
	else
		ft_strncat(file_path, file_name, ft_strlen(file_name) + 1);
}

int create_new_file(t_file **new_file, char *name, char *parent_path)
{
	if (allocate_new_file(new_file, name, parent_path) != EXIT_SUCCESS)
		return exit_error(new_file);
	if (!((*new_file)->files       = ft_lstnew()))
		return exit_error(new_file);
	if (!((*new_file)->sub_folders = ft_lstnew()))
		return exit_error(new_file);
	ft_strcpy((*new_file)->name, name);
	build_file_path((*new_file)->path, parent_path, name);
	if (read_file_properties(*new_file) != EXIT_SUCCESS)
		return exit_error(new_file);
	return (EXIT_SUCCESS);
}

void del_file(t_file *file, size_t folder_size)
{
	if (file != NULL) {
		if (file->files)
			ft_lstdel(file->files, (void (*)(void *, size_t))del_file);
		if (file->sub_folders)
			ft_lstdel(file->sub_folders, (void (*)(void *, size_t))del_file);
		if (file->properties)
		{
			ft_bzero(file->properties, file->properties->struct_size);
			ft_memdel((void **)&file->properties);
		}
		ft_bzero(file, folder_size);
		ft_memdel((void **)&file);
	}
}