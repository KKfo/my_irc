/*
** PSU_2014_myirc/main.c for my_irc in /home/xxx/Epitech/2015/PSU_2014_myirc
** 
** Made by 
** Login   <xxx@epitech.eu>
** 
** Started on  Tue Apr 14 20:34:12 2015 
** Last update Mon Apr 20 22:28:10 2015 
*/

#include	"../include/defs.h"

int		prepare_fds(t_env *e)
{
  t_user		*u;
  int		i;

  FD_ZERO(&e->fd_read);
  FD_ZERO(&e->fd_write);     
  e->fd_max = 0;
  for (i = 0; i < MAX_FD; i++)
    {
      if (e->fd_type[i] != FD_FREE)
        {
          FD_SET(i, &e->fd_read);
          if (e->nicks[i] != GUEST)
          u = lookup_table(e->users, e->nicks[i]);
          if ((u && u->buff[0]) || e->guest_buff[i])
            {
              FD_SET(i, &e->fd_write);
            }
          e->fd_max = i;
        }
    }
  return (0);
}

int		execute_reads(t_env *e)
{
  int		i;

  for (i = 0; i < MAX_FD; i++)
    {
      if (FD_ISSET(i, &e->fd_read))
        e->fct_read[i](e, i);
    }
  return (0);
}

int			execute_writes(t_env *e)
{
  int			i;

  for (i = 0; i < MAX_FD; i++)
    {
      if (FD_ISSET(i, &e->fd_write))
        e->fct_write[i](e, i);
    }
  return (0);
}

int			main(int argc, char **argv)
{
  int			nr;
  struct timeval	tv;
  t_env         	e;
  int			p;

  nr = 1;
  memset(&e, 0, sizeof(e));
  e.users = create_hshtbl(255);
  e.groups = create_hshtbl(255);
  if (argc != 2 || !(p = atoi(argv[1])))
    {
      printf("Usage: %s port", argv[0]);
      return (0);
    }
  add_server(p, &e);
  while (1)
    {
      printf("Waiting for connections...\n");
      tv.tv_sec = 1000;
      tv.tv_usec = 11;
      if (nr)
        prepare_fds(&e);
      if ((nr = select(e.fd_max + 1, &e.fd_read,
                       &e.fd_write, NULL, &tv)) == -1)
        perror("select");
      if (nr)
        {
          execute_reads(&e);
          execute_writes(&e);
        }
    }
  return (0);
}
