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
		if (!(parent_folder->sub_folders = ft_lstnew()))
			return (EXIT_FAILURE);
		ft_lst_filter(parent_folder->files, &parent_folder->sub_folders,
				&is_file_a_valid_subfolder);
	}
	return (EXIT_SUCCESS);
}

int process_folder_files(t_store *store, struct s_file *folder)
{
	print_parent_folder(store, folder);
	ft_lstiter(folder->files, &print_file_from_node);
	return (register_subfolders(folder));
}

int get_folder_files(struct s_file *folder)
{
	t_node        *new_node;
	t_file        *new_file;
	struct dirent *fe;
	DIR           *f;

	new_node   = NULL;
	new_file   = NULL;
	if (!(f    = opendir(folder->path))) {
		ft_printf("Failed to open %s\n", folder->name);
		return 1;
	}
	while ((fe = readdir(f))) {
		if (fe->d_name[0] != '.' || g_flags[0] == 'a') {
			if (create_new_file(&new_file, fe->d_name, folder->path) > 0) {
				closedir(f);
				return (1);
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

int process_folders(t_store *store)
{
	t_node *folders_queue_ptr;
	t_file *folder;

	folders_queue_ptr = store->folders_queue->head;
	folder            = NULL;
	while (folders_queue_ptr) {
		folder = folders_queue_ptr->data;
		if (should_process_file(folder)) {
			if (get_folder_files(folder) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
			if (folder->files) {
				sort_files(folder->files);
				if (process_folder_files(store, folder) != EXIT_SUCCESS)
					return (EXIT_FAILURE);
				if (folder->sub_folders->size > 0) {
					sort_files(folder->sub_folders);
					ft_lstinsert_after(folder->sub_folders, folders_queue_ptr);
					folder->sub_folders->head = NULL;
				}
			}
		}
		folders_queue_ptr = folders_queue_ptr->next;
	}
	return (EXIT_SUCCESS);
}