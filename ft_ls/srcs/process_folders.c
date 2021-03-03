#include "ft_ls.h"


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
		return (EXIT_FAILURE);
	}
	while ((fe = readdir(f))) {
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

void add_subfolders_to_queue(t_node *folders_queue, t_file *parent_folder)
{
	if (parent_folder->sub_folders->size > 0) {
		ft_lstinsert_after(parent_folder->sub_folders, folders_queue);
		parent_folder->sub_folders->head = NULL;
	}
}

int process_folders(t_store *store)
{
	t_node *folders_queue_ptr;
	t_file *folder;

	folders_queue_ptr = store->folders_queue->head;
	folder            = NULL;
	while (folders_queue_ptr)
	{
		folder = folders_queue_ptr->data;
		if (should_process_file(folder)) {
			if (get_folder_files(folder) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
			if (process_folder_files(store, folder) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
			add_subfolders_to_queue(folders_queue_ptr, folder);
		}
		folders_queue_ptr = folders_queue_ptr->next;
	}
	return (EXIT_SUCCESS);
}