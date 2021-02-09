#include "libft.h"

void ft_lstinsert_after(t_list *src, t_node *dest)
{
  t_node *list_tail;

  list_tail = ft_lstget_tail(src);
  list_tail->next = dest->next;
  dest->next = src->head;
}
