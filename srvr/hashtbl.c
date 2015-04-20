/*
** hashtbl.c for  in /home/xxx/Epitech/2015/PSU_2014_myirc
** 
** Made by 
** Login   <xxx@epitech.eu>
** 
** Started on  Wed Apr 15 15:59:03 2015 
** Last update Mon Apr 20 15:39:30 2015 
*/

#include		"../include/ring_buffer.h"

unsigned long		hash(t_hash_table *h, char *str)
{
  unsigned long		hash;
  int			c;

  hash = 5381;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;
  return (hash % h->size);
}

t_hash_table		*create_hshtbl(int size)
{
  t_hash_table		*new_table;

  if (size < 1)
    return (NULL);
  if ((new_table = malloc(sizeof(t_hash_table))) == NULL)
    {
    return (NULL);
    }
  if ((new_table->table = malloc(sizeof(void*) * size)) == NULL)
    {
      return (NULL);
    }
  memset(new_table->table, 0, sizeof(void*) * size);
  new_table->size = size;
  return (new_table);
}

void			*lookup_table(t_hash_table *hashtable, char *str)
{
  unsigned int		hashval;

  if (str == NULL)
    return (NULL);
  hashval = hash(hashtable, str);
  if (hashtable->table[hashval] != NULL)
    if (strcmp(str, ((t_user**)hashtable->table)[hashval]->name) == 0)
      return (hashtable->table[hashval]);
  return (NULL);
}

void            add_fd(char **arr, char *usr)
{
  int		i;

  i = 0;
  while (i < 255)
    {
      if (!arr[i])
        {
          arr[i] = strdup(usr);
          return ;
        }
      i++;
    }
  return ;
}

void		*add_elem(t_hash_table *hashtable, char *str,
                         int fd, size_t size)
{
  void		*new_elem;
  void		*current_elem;
  unsigned int	hashval;

  hashval = hash(hashtable, str);
  current_elem = lookup_table(hashtable, str);
  if (current_elem != NULL)
    {
      printf("add_name: %s item already exist\n", str);
      return (NULL);
    }
  if ((new_elem = calloc(1, size)) == NULL)
    return (NULL);
  ((t_user*)new_elem)->name = strdup(str);
  if (size == sizeof(t_user))
    {
      write(1, "ddd\n", 4); /* dddd */
      ((t_user*)new_elem)->fd = fd;
      ((t_user*)new_elem)->h = ((t_user*)new_elem)->buff;
      ((t_user*)new_elem)->c = ((t_user*)new_elem)->buff;
      /* printf("point b %p point c %p\n", ((t_user*)new_elem)->buff, ((t_user*)new_elem)->c); /\* DEBUG *\/ */
    }
  else
    {
      printf("Weirddd: group requested %lu\n", sizeof(t_user));  /* DEBUG */
      add_fd(((t_group*)new_elem)->usrs, str);
    }
  hashtable->table[hashval] = new_elem;
  return (new_elem);
}

void			del_elem(t_hash_table *hashtable, char *str)
{
  unsigned int		hashval;

  if (!str || !hashtable)
    return ;
  hashval = hash(hashtable, str);
  if (((t_user**)hashtable->table)[hashval])
    if (strcmp(str, ((t_user**)hashtable->table)[hashval]->name) == 0)
      {
        free(((t_user**)hashtable->table)[hashval]->name);
        free(hashtable->table[hashval]);
        hashtable->table[hashval] = NULL;
        return ;
      }
  return ;
}

void			free_table(t_hash_table *hashtable)
{
  int			i;

  i = 0;
  while(i < hashtable->size)
    {
      if (hashtable->table[i] != NULL)
        {
          free(((t_user**)hashtable->table)[i]->name);
          free(hashtable->table[i]);
        }
      i++;
    }
  free(hashtable);
  return ;
}
