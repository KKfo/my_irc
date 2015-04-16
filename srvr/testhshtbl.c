
#include                "include/ring_buffer.h"

int             main()
{
  void                  *found;
  void                  *found1;
  t_hash_table		*hshtbl;

  hshtbl = create_hshtbl(255);
  add_elem(hshtbl, "hello world", 10, sizeof(t_group));
  add_elem(hshtbl, "hello world1", 20, sizeof(t_group));
  found = lookup_table(hshtbl, "hello world");
  found1 = lookup_table(hshtbl, "hello world1");
  printf("%s\n", ((t_user*)found)->name);
  printf("%i\n", ((t_group*)found1)->fds[0]);
  del_elem(hshtbl, "hello world");
  found = lookup_table(hshtbl, "hello world");
  if (found != NULL)
    printf("%s\n", ((t_user*)found)->name);
  free_table(hshtbl);
  return (0);
}
