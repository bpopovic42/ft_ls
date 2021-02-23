#include "ft_ls.h"

int parse_arguments(char **arguments, t_store *store) {
  int i;
  t_node *new_node;
  t_file *new_folder;

  i = 0;
  new_node = NULL;
  new_folder = NULL;
  while (arguments[i])
  {
    if (create_new_file(&new_folder, arguments[i], NULL) > 0)
      return (1);
    if (!(new_node = ft_node_new(NULL, 0)))
      return (1);
    new_node->data = new_folder;
    ft_lstadd(store->folders_queue, new_node);
    i++;
  }
  return (0);
}
