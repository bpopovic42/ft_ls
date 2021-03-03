#include "ft_ls.h"

int get_folder_files(struct s_file *folder)
{
	t_node        *new_node;
	t_file        *new_file;
	struct dirent *fe;
	DIR           *f;

	new_node   = NULL;
	new_file   = NULL;
	if (!(f = opendir(folder->path)))
		return (EXIT_FAILURE);
	while ((fe = readdir(f)))
	{
		if (fe->d_name[0] != '.' || g_flags[0] == 'a') {
			if (create_new_file(&new_file, fe->d_name, folder->path) != EXIT_SUCCESS) {
				closedir(f);
				return (EXIT_FAILURE);
			}
			if (!(new_node = ft_node_new(NULL, 0))) {
				del_file(new_file, new_file->struct_size);
				closedir(f);
				return (1);
			}
			new_node->data      = new_file;
			new_node->data_size = new_file->struct_size;
			ft_lstadd(folder->files, new_node);
		}
	}
	closedir(f);
	return (0);
}
