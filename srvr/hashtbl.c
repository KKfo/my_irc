/*
** hashtbl.c for  in /home/xxx/Epitech/2015/PSU_2014_myirc
** 
** Made by 
** Login   <xxx@epitech.eu>
** 
** Started on  Wed Apr 15 15:59:03 2015 
** Last update Fri Apr 24 04:29:16 2015 
*/

#include		"../include/ring_buffer.h"

unsigned long		hash(t_hash_table *h, char *str)
{
  unsigned long		hash;
  int			c;

  hash = 5381;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;
  return (hash % (h->size - 1) + 1);
}

t_hash_table		*create_hshtbl(int size, char type)
{
  t_hash_table		*new_table;

  if (size < 1)
    return (NULL);
  if (!(new_table = malloc(sizeof(t_hash_table)))
      || !(new_table->table = malloc(sizeof(void*) * size)))
    {
      return (NULL);
    }
  memset(new_table->table, 0, sizeof(void*) * size);
  new_table->size = size;
  new_table->type = type;
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
        if (hashtable->type == 'g')
          free_table(((t_group**)hashtable->table)[hashval]->usrs);
        free(hashtable->table[hashval]);
        hashtable->table[hashval] = NULL;
        return ;
      }
  return ;
}

void			free_table(t_hash_table *hashtable)
{
  char			g;
  int			i;

  i = 0;
  g = 0;
  if (hashtable->type == 'g')
    g = 1;
  while(i < hashtable->size)
    {
      if (hashtable->table[i] != NULL)
        {
          free(((t_user**)hashtable->table)[i]->name);
          if (g)
            free_table(((t_group**)hashtable->table)[i]->usrs);
          free(hashtable->table[i]);
        }
      i++;
    }
  free(hashtable);
  return ;
}
