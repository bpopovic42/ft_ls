#include "ft_ls.h"

int process_folder_files(struct s_file *folder)
{
  t_node *folder_files_ptr;
  t_node *new_node;
  t_file *file;
  t_file *new_folder;

  folder_files_ptr = folder->files->head;
  new_folder = NULL;
  ft_printf("%s:\n", folder->path);
  while (folder_files_ptr)
  {
    file = folder_files_ptr->data;
    ft_printf("%s ", file->name);
    if (S_ISDIR(file->type) && file->name[0] != '.')
    {
      if (create_new_file(&new_folder, file->name, folder->path) > 0)
        return (1);
      if (!(new_node = ft_node_new(NULL, sizeof(t_file))))
      {
        del_file(new_folder, sizeof(t_file));
        return (1);
      }
      new_node->data = new_folder;
      if (folder->sub_folders == NULL)
      {
        if (!(folder->sub_folders = ft_lstnew()))
        {
          ft_node_del(&new_node, (void (*)(void *, size_t))del_file);
          return (1);
        }
      }
      ft_lstadd(folder->sub_folders, new_node);
    }
    folder_files_ptr = folder_files_ptr->next;
  }
  ft_putchar('\n');
  ft_putchar('\n');
  return (0);
}

int get_folder_files(struct s_file *folder) {
  t_node *new_node;
  t_file *new_file;
  struct dirent *fe;
  DIR *f;

  new_node = NULL;
  new_file = NULL;
  if (!(f = opendir(folder->path))) {
    ft_printf("Failed to open %s\n", folder->name);
    return 1;
  }
  while ((fe = readdir(f)))
  {
    if (create_new_file(&new_file, fe->d_name, folder->path) > 0)
    {
      closedir(f);
      return (1);
    }
    if (!(new_node = ft_node_new(NULL, 0)))
    {
      del_file(new_file, new_file->size);
      closedir(f);
      return (1);
    }
    new_node->data = new_file;
    new_node->data_size = new_file->size;
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
  folder = NULL;
  while (folders_queue_ptr)
  {
    folder = folders_queue_ptr->data;
    if (get_folder_files(folder) > 0)
      return (1);
    if (folder->files) {
      sort_files(folder->files);
      if (process_folder_files(folder) > 0)
        return (1);
      if (folder->sub_folders->size > 0) {
        sort_files(folder->sub_folders);
        ft_lstinsert_after(folder->sub_folders, folders_queue_ptr);
        folder->sub_folders->head = NULL;
      }
    }
    folders_queue_ptr = folders_queue_ptr->next;
  }
  return (0);
}