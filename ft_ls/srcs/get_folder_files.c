#include "ft_ls.h"

int add_file_to_node(t_file *file, t_node **node)
{
	if (!(*node = ft_node_new(NULL, 0)))
		return (EXIT_FAILURE);
	(*node)->data      = file;
	(*node)->data_size = file->struct_size;
	return (EXIT_SUCCESS);
}

int add_new_file_to_folder(t_file *folder, struct dirent *direntry)
{
	int error_status;
	t_node        *new_node;
	t_file        *new_file;
	char            *parent_path;

	new_node = NULL;
	new_file   = NULL;
	parent_path = ft_strequ(folder->path, "/") ? "" : folder->path;
	if (direntry->d_name[0] == '.' && !g_flags.option_a)
		return (EXIT_SUCCESS);
	if ((error_status = create_new_file(&new_file, direntry->d_name,
									 parent_path)) != EXIT_SUCCESS)
		return (error_status);
	if ((error_status = add_file_to_node(new_file, &new_node)) != EXIT_SUCCESS)
	{
		del_file(new_file, new_file->struct_size);
		return (error_status);
	}
	new_file->parent_folder = folder;
	folder->properties->total_blocks += new_file->properties->blocks;
	ft_lstadd(folder->files, new_node);
	return (EXIT_SUCCESS);
}

int handle_opendir_failure(t_file *file)
{
	if (file && errno == EACCES)
	{
		file->error = errno;
		file->error_msg = "cannot open directory";
	}
	return (errno);
}

int get_folder_files(struct s_file *folder)
{
	struct dirent *direntry;
	DIR           *dirstream;
	int           error_status;

	if (!(dirstream  = opendir(folder->path)))
		return (handle_opendir_failure(folder));
	while ((direntry = readdir(dirstream)))
	{
		error_status = add_new_file_to_folder(folder, direntry);
		if (error_status != EXIT_SUCCESS)
				break;
	}
	closedir(dirstream);
	return (error_status);
}
