#include "ft_ls.h"

int add_new_file_to_folder(t_file *folder, struct dirent *entry)
{
	t_node        *new_node;
	t_file        *new_file;

	new_node   = NULL;
	new_file   = NULL;
	if (entry->d_name[0] == '.' && g_flags[0] != 'a')
		return (EXIT_SUCCESS);
	if (create_new_file(&new_file, entry->d_name, folder->path) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (!(new_node = ft_node_new(NULL, 0)))
	{
		del_file(new_file, new_file->struct_size);
		return (EXIT_FAILURE);
	}
	new_node->data      = new_file;
	new_node->data_size = new_file->struct_size;
	ft_lstadd(folder->files, new_node);
	return (EXIT_SUCCESS);
}

int get_folder_files(struct s_file *folder)
{
	struct dirent *fe;
	DIR           *f;

	if (!(f = opendir(folder->path)))
		return (EXIT_FAILURE);
	while ((fe = readdir(f)))
	{
		if (add_new_file_to_folder(folder, fe) != EXIT_SUCCESS)
		{
			closedir(f);
			return (EXIT_FAILURE);
		}
	}
	closedir(f);
	return (0);
}
