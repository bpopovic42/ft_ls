#include "ft_ls.h"

int main(int ac, char **av)
{
  t_store  store;
  int error_status;

  (void)ac;
  error_status = 0;
  if (!(error_status = init_store(&store)))
  {
    if (!(error_status = parse_arguments(av + 1, &store) > 0))
    {
      sort_files(store.folders_queue);
      process_folders(&store);
    }
  }
  clean_store(&store);
  //ft_lstiter(store.folders_queue, tmp_print_folder);
  return (error_status);
}
