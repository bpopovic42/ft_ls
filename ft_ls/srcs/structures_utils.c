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

  file = malloc(sizeof(t_file));
  file->name = ft_strdup(name);
  file->files = ft_lstnew();
  if (parent_path)
  {
    file->path = ft_strdup(parent_path);
    file->path = ft_strjoin(parent_path, "/");
    file->path = ft_strjoin(file->path, name);
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
