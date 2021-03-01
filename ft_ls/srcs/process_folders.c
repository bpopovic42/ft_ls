#include "ft_ls.h"

int add_subfolder(t_file *folder, t_file *subfolder)
{
	t_file *new_folder;
	t_node *new_node;

	new_folder = NULL;
	if (create_new_file(&new_folder, subfolder->name, folder->path) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (!(new_node = ft_node_new(NULL, sizeof(t_file)))) {
		del_file(new_folder, sizeof(t_file));
		return (EXIT_FAILURE);
	}
	new_node->data = new_folder;
	if (folder->sub_folders == NULL && !(folder->sub_folders = ft_lstnew())) {
		ft_node_del(&new_node, (void (*)(void *, size_t))del_file);
		return (EXIT_FAILURE);
	}
	ft_lstadd(folder->sub_folders, new_node);
	return (EXIT_SUCCESS);
}

int add_file_if_folder(t_store *store, t_file *parent_folder, t_file *file)
{
	if (store->flags[3] == 'R' && file->mode.type == 'd'
	    && !ft_strequ(file->name, ".") && !ft_strequ(file->name, ".."))
	{
		if (add_subfolder(parent_folder, file) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int process_folder_files(t_store *store, struct s_file *folder)
{
	t_file *file;
	t_node *folder_files_ptr;

	folder_files_ptr = folder->files->head;
	print_parent_folder(store, folder);
	while (folder_files_ptr)
	{
		file = folder_files_ptr->data;
		if (file->name[0] != '.' || store->flags[0] == 'a')
		{
			print_file(store, file, folder_files_ptr->next == NULL);
			if (add_file_if_folder(store, folder, file) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
		}
		folder_files_ptr = folder_files_ptr->next;
	}
	return (0);
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
		if (get_folder_files(folder) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		if (folder->files) {
			sort_files(store, folder->files);
			if (process_folder_files(store, folder) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
			if (folder->sub_folders->size > 0) {
				sort_files(store, folder->sub_folders);
				ft_lstinsert_after(folder->sub_folders, folders_queue_ptr);
				folder->sub_folders->head = NULL;
			}
		}
		folders_queue_ptr = folders_queue_ptr->next;
	}
	return (0);
}