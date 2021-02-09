#include "ft_ls.h"

void tmp_print_file(t_node *node)
{
  t_file *file;

  file = (t_file*)node->data;
  ft_printf("%s ", file->name);
}

void tmp_print_folder(t_node *node)
{
  t_file *folder;

  folder = (t_file *)node->data;
  ft_putendl(folder->name);
  if (folder->files)
    ft_lstiter(folder->files, tmp_print_file);
}
