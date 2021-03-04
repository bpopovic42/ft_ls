#include "ft_ls.h"

int exit_error(t_file **file_to_clean)
{
	if (*file_to_clean)
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

// TODO: Notify which mistake lead to this function in README
int get_number_of_subfolders(t_file **folder)
{
	struct dirent *direntry;
	DIR           *dirstream;

	if ((*folder)->mode.type != 'd')
		return (EXIT_SUCCESS);
	if (!(dirstream  = opendir((*folder)->path)))
		return (EXIT_FAILURE);
	while ((direntry = readdir(dirstream)))
	{
		if (direntry->d_type == DT_DIR)
			(*folder)->nbr_of_subfolders += 1;
	}
	closedir(dirstream);
	return (EXIT_SUCCESS);
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
	if (parent_path)
		ft_strcatn((*new_file)->path, 3, parent_path, "/\0", name);
	else
		ft_strncat((*new_file)->path, name, ft_strlen(name) + 1);
	if (read_file_properties(*new_file) != EXIT_SUCCESS)
		return exit_error(new_file);
	if (get_number_of_subfolders(new_file) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void del_file(t_file *file, size_t folder_size)
{
	//ft_printf("cleaning : %s\n", file->name);
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