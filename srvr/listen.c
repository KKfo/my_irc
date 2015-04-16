/*
** listen.c for my_irc in /home/xxx/Epitech/2015/PSU_2014_myirc
** 
** Made by 
** Login   <xxx@epitech.eu>
** 
** Started on  Tue Apr 14 19:58:08 2015 
** Last update Thu Apr 16 11:40:54 2015 
*/

#include			"../include/defs.h"

static char			init_socket(t_listen *v)
{
  struct protoent		*s_p;

  if (!(s_p = getprotobyname("TCP")))
    {
      perror("getprotobyname");
      return (EXIT_FAILURE);
    }
  if ((v->socket_fd = socket(AF_INET, SOCK_STREAM, s_p->p_proto)) == -1)
    {
      perror("socket");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

static char			do_bind(t_listen *v)
{
  v->size = sizeof(v->s_in);
  memset(&v->s_in, 0, v->size);
  v->s_in.sin_family = AF_INET;
  v->s_in.sin_port = htons(v->port);
  v->s_in.sin_addr.s_addr = INADDR_ANY;
  if ((bind(v->socket_fd,
            (struct sockaddr *)&v->s_in,
            v->size)) == -1)
    {
      if ((close(v->socket_fd)) == -1)
        {
          perror("close");
          return (EXIT_FAILURE);
        }
      perror("bind");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);  
}

static char			do_listen(t_listen *v)
{
  if (listen(v->socket_fd, 42) == -1)
    {
      if ((close(v->socket_fd)) == -1)
        {
          perror("close");
          return (EXIT_FAILURE);
        }
      perror("listen");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

int				start_listen(int p)
{
  t_listen			v;

  v.port = p;
  if ((init_socket(&v))
      || do_bind(&v)
      || do_listen(&v))
    return (-1);
  return (v.socket_fd);
}
