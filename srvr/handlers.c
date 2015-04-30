/*
** handlers.c for my_irc in /home/xxx/Epitech/2015/PSU_2014_myirc
** 
** Made by 
** Login   <xxx@epitech.eu>
** 
** Started on  Tue Apr 14 21:00:39 2015 
** Last update Sat Apr 25 19:02:54 2015 
*/

#include		"../include/defs.h"

int			is_guest(t_env *e, int fd)
{
  if (e->guest_buff[fd])
    {
      write(fd, e->guest_buff[fd], strlen(e->guest_buff[fd]));
      free(e->guest_buff[fd]);
      e->guest_buff[fd] = NULL;
    }
  return (9);
}

int			is_registered(t_env *e, int fd)
{
  t_user		*u;

  u = lookup_table(e->users, e->nicks[fd]);
  if (u && u->buff[0])
    {
      write(fd, u->buff, 1024/* strlen(u->buff) */);
      u->c = u->h;
      memset(u->buff, 0, strlen(u->buff));
    }
  return (0);
}

void			client_write(t_env *e, int fd)
{
  if (!e->nicks[fd])
    return ;
  if (e->nicks[fd] == GUEST)
    {
      is_guest(e, fd);
    }
  else
    {
      is_registered(e, fd);
    }
  return ;
}
 
void			add_client(t_env *e, int s)
{
  int			cs;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;

  client_sin_len = sizeof(client_sin);
  cs = accept(s, (struct sockaddr *)&client_sin, &client_sin_len);
  e->fd_type[cs] = FD_CLIENT;
  e->fct_read[cs] = client_read;
  e->fct_write[cs] = client_write;
  e->nicks[cs] = GUEST;
  printf("New client\n");
  return ;
}

void			add_server(int p, t_env *e)
{
  int			s;

  s = start_listen(p);
  if (s == -1)
    exit(1);
  e->fd_type[s] = FD_SERVER;
  e->fct_read[s] = add_client;
  e->fct_write[s] = NULL;
  return ;
}
