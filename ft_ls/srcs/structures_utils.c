#include "ft_ls.h"

int read_file_properties(t_file *file)
{
  struct stat file_stat;

  if (lstat(file->path, &file_stat) < 0)
    return (1);
  file->type = file_stat.st_mode;
  return (0);
}

int create_new_file(t_file **dst, char *name, char *parent_path) {
  int error;

  error = 0;
  if (!(*dst = ft_memalloc(sizeof(t_file))))
      return (1);
  if (!((*dst)->name = ft_strdup(name)))
    error++;
  if (!((*dst)->files = ft_lstnew()))
    error++;
  if (parent_path)
  {
    if (!((*dst)->path =
              ft_strappendn((*dst)->path, 3, parent_path, "/", name)))
      error++;
  }
  else
  {
    if (!((*dst)->path = ft_strdup(name)))
      error++;
  }
  error += read_file_properties(*dst);
  if (error > 0)
    del_file(*dst, sizeof(t_file));
  return (error);
}

int init_store(t_store *store)
{
  ft_bzero(store, sizeof(t_store));
  if (!(store->folders_queue = ft_lstnew()))
    return (1);
  return (0);
}

int del_file(t_file *file, size_t folder_size)
{
  ft_printf("cleaning : %s\n", file->name);
  if (file != NULL)
  {
    if (file->files)
      ft_lstdel(file->files, (void (*)(void *, size_t))del_file);
    if (file->sub_folders)
      ft_lstdel(file->sub_folders, (void (*)(void *, size_t))del_file);
    if (file->name)
      ft_strdel(&file->name);
    if (file->path)
      ft_strdel(&file->path);
    ft_bzero(file, folder_size);
    ft_memdel((void **)&file);
  }
  return (0);
}

int clean_store(t_store *store)
{
  ft_lstdel(store->folders_queue, (void (*)(void *, size_t))del_file);
  return (0);
}