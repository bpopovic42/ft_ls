#include "ft_ls.h"

int init_store(t_store *store)
{
  ft_bzero(store, sizeof(t_store));
  if (!(store->folders_queue = ft_lstnew()))
    return (1);
  return (0);
}

int clean_store(t_store *store)
{
  ft_lstdel(store->folders_queue, (void (*)(void *, size_t))del_file);
  return (0);
}
