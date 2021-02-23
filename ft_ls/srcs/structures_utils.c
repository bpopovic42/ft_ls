#include "ft_ls.h"

int read_file_properties(t_file *file)
{
  struct stat file_stat;

  lstat(file->path, &file_stat);
  file->type = file_stat.st_mode;
  return (0);
}

t_file *create_new_file(char *name, char *parent_path) {
  t_file *file;

  file = ft_memalloc(sizeof(t_file));
  file->name = ft_strdup(name);
  file->files = ft_lstnew();
  if (parent_path)
  {
    file->path = ft_strdup(parent_path);
    file->path = ft_strappendn(file->path, 2, "/", name);
  }
  else
    file->path = ft_strdup(name);
  read_file_properties(file);
  return (file);
}

int init_store(t_store *store)
{
  ft_bzero(store, sizeof(t_store));
  store->folders_queue = ft_lstnew();
  return (1);
}

int del_file(t_file *file, size_t folder_size)
{
  ft_printf("cleaning : %s\n", file->name);
  if (file->files)
    ft_lstdel(file->files, (void (*)(void *, size_t))del_file);
  if (file->sub_folders)
    ft_lstdel(file->sub_folders, (void (*)(void *, size_t))del_file);
  ft_strdel(&file->name);
  ft_strdel(&file->path);
  ft_bzero(file, folder_size);
  ft_memdel((void**)&file);
  return (0);
}

int clean_store(t_store *store)
{
  ft_lstdel(store->folders_queue, (void (*)(void *, size_t))del_file);
  return (0);
}