/*
** extra.c for my_irc in /home/xxx/Epitech/2015/PSU_2014_myirc
** 
** Made by 
** Login   <xxx@epitech.eu>
** 
** Started on  Fri Apr 24 04:29:07 2015 
** Last update Fri Apr 24 05:13:39 2015 
*/

#include		"../include/defs.h"

void		init_usr(t_user	*new_user, char *str,
                         t_hash_table *hashtable, int fd)
{
  unsigned int	hashval;

  hashval = hash(hashtable, str);
  new_user->name = strdup(str);
  new_user->fd = fd;
  new_user->h = new_user->buff;
  new_user->c = new_user->buff;
  new_user->hsh = hashval;
  hashtable->table[hashval] = new_user;
  return ;
}

void		init_group(t_group *new_group, char *str,
                         t_hash_table *hashtable)
{
  unsigned int	hashval;

  hashval = hash(hashtable, str);
  new_group->name = strdup(str);
  new_group->usrs = create_hshtbl(255, 'u');
  hashtable->table[hashval] = new_group;
  return ;
}

void		*add_elem(t_hash_table *hashtable, char *str,
                         int fd, size_t size)
{
  void		*new_elem;

  if (lookup_table(hashtable, str)
      || !(new_elem = calloc(1, size)))
    {
      printf("add_name: %s item already exist\n", str);
      return (NULL);
    }
  if (size == sizeof(t_user))
    {
      init_usr(new_elem, str, hashtable, fd);
    }
  else
    {
      init_group(new_elem, str, hashtable);
    }
  return (new_elem);
}

int			list(char *buff, t_env *e, int fd)
{
  UNUSED(buff);
  UNUSED(e);
  UNUSED(fd);
  return (0);
}
