#include "ft_ls.h"

int is_file_a_valid_subfolder(t_node *file_node)
{
	t_file *original_file;

	original_file = file_node->data;
	return (
			!ft_strequ(original_file->name, ".") &&
			!ft_strequ(original_file->name, "..") &&
			original_file->mode.type	== 'd'
	);
}

int register_subfolders(t_file *parent_folder)
{
	if (g_flags[3] == 'R')
	{
		ft_lst_filter(parent_folder->files, &parent_folder->sub_folders,
		              &is_file_a_valid_subfolder);
		sort_files(parent_folder->sub_folders);
	}
	return (EXIT_SUCCESS);
}

int process_folder_files(t_store *store, struct s_file *folder)
{
	if (folder->files)
	{
		sort_files(folder->files);
		print_parent_folder(store, folder);
		ft_lstiter(folder->files, &print_file_from_node);
		if (register_subfolders(folder) != EXIT_SUCCESS)
			return (handle_error(store, FT_LS_FATAL_ERROR));
	}
	return (EXIT_SUCCESS);
}
