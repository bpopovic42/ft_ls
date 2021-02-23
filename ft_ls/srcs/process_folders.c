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
      new_folder = create_new_file(file->name, folder->path);
      new_node = ft_node_new(new_folder, sizeof(t_file));
      if (folder->sub_folders == NULL)
      {
        if (!(folder->sub_folders = ft_lstnew()))
          return (1);
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
    new_file = create_new_file(fe->d_name, folder->path);
    new_node = ft_node_new(NULL, 0);
    new_node->data = new_file;
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
    get_folder_files(folder);
    if (folder->files) {
      sort_files(folder->files);
      process_folder_files(folder);
      if (folder->sub_folders != NULL) {
        sort_files(folder->sub_folders);
        ft_lstinsert_after(folder->sub_folders, folders_queue_ptr);
        folder->sub_folders->head = NULL;
      }
    }
    folders_queue_ptr = folders_queue_ptr->next;
  }
  return (0);
}