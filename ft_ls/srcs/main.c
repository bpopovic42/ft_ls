#include "ft_ls.h"

int main(int ac, char **av)
{
  t_store  store;

  (void)ac;
  init_store(&store);
  parse_arguments(av + 1, &store);
  sort_files(store.folders_queue);
  process_folders(&store);
  clean_store(&store);
  //ft_lstiter(store.folders_queue, tmp_print_folder);
  return (0);
}
