/*
** handlers.c for my_irc in /home/xxx/Epitech/2015/PSU_2014_myirc
** 
** Made by 
** Login   <xxx@epitech.eu>
** 
** Started on  Tue Apr 14 21:00:39 2015 
** Last update Thu Apr 16 12:38:51 2015 
*/

#include		"../include/defs.h"

void			client_write(t_env *e, int fd)
{
  if (e->nicks[fd])
    if (strcmp(e->nicks[fd], "guest") == 0)
    {
      if (e->guest_buff[fd])
        write(fd, e->guest_buff[fd], strlen(e->guest_buff[fd]));
      free(e->guest_buff[fd]);
    }
  return ;
}
 
void			add_client(t_env *e, int s)
{
  int			cs;
  struct sockaddr_in	client_sin;
  socklen_t			client_sin_len;

  client_sin_len = sizeof(client_sin);
  cs = accept(s, (struct sockaddr *)&client_sin, &client_sin_len);
  e->fd_type[cs] = FD_CLIENT;
  e->fct_read[cs] = client_read;
  e->fct_write[cs] = client_write;
  e->nicks[cs] = strdup("guest");
}
 
void			server_read(t_env *e, int fd)
{
  printf("New client\n");
  add_client(e, fd);
}

void			add_server(int p, t_env *e)
{
  int			s;

  s = start_listen(p);
  e->fd_type[s] = FD_SERVER;
  e->fct_read[s] = server_read;
  e->fct_write[s] = NULL;
  return ;
}
