/*
** ring_buffer.h for my_irc in /home/xxx/Epitech/2015/PSU_2014_myirc
** 
** Made by 
** Login   <xxx@epitech.eu>
** 
** Started on  Wed Apr 15 12:28:24 2015 
** Last update Sun Apr 19 20:34:07 2015 
*/

#ifndef			RING_BUFFER_H_
# define		RING_BUFFER_H_
#include                <stddef.h>
#include                <stdio.h>
#include                <unistd.h>
#include                <stdlib.h>
#include                <string.h>

typedef struct	s_ring_buffer
{
  char *buffer;
  int length;
  int start;
  int end;
} t_ring_buffer;

typedef struct	s_user
{
  char		*name;
  char          buff[1024];
  char		*h;
  char		*c;
  int		fd;
} t_user;

typedef struct	s_group
{
  char		*name;
  char		*usrs[255];
} t_group;

typedef struct	s_hash_table
{
  int		size;
  void		**table;
} t_hash_table;

t_hash_table		*create_hshtbl(int size);
void			*lookup_table(t_hash_table *hashtable, char *str);
void			*add_elem(t_hash_table *hashtable, char *str,
                                 int fd, size_t size);
void			del_elem(t_hash_table *hashtable, char *str);
void			free_table(t_hash_table *hashtable);
#endif
