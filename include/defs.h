/*
** PSU_2014_myirc/defs.h for my_irc in /home/xxx/Epitech/2015/PSU_2014_myirc
** 
** Made by 
** Login   <xxx@epitech.eu>
** 
** Started on  Tue Apr 14 20:01:47 2015 
** Last update Fri Apr 24 05:11:00 2015 
*/

#ifndef				DEFS_H_
# define			DEFS_H_
# define			FD_FREE 0
# define			FD_CLIENT 1
# define			FD_SERVER 2 
# define			MAX_FD  255
# define			GUEST (void*)-1
# define			UNUSED(x) (void)(x)
# include			<unistd.h>
# include			<stdio.h>
# include			<stdlib.h>
# include			<strings.h>
# include			<string.h>
# include			<sys/types.h>
# include			<sys/socket.h>
# include			<netinet/in.h>
# include			<arpa/inet.h>
# include			<time.h>
# include			<errno.h>
# include			<sys/socket.h>
# include			<netdb.h>
# include			"ring_buffer.h"
# include			<signal.h>
typedef struct		s_listen
{
  struct sockaddr_in	s_in;
  socklen_t		size;
  int			port;
  int			socket_fd;
}			t_listen;

typedef 			void(*fct)();

typedef struct		s_env
{
  char			fd_type[MAX_FD];
  fct			fct_read[MAX_FD];
  fct			fct_write[MAX_FD];
  int			fd_max;
  fd_set		fd_read;
  fd_set		fd_write;
  t_hash_table		*users;
  t_hash_table		*groups;
  char			*guest_buff[MAX_FD];
  char			*nicks[MAX_FD];
}			t_env;

typedef int (*t_action)(char *buff, t_env *e, int fd);

int			list(char *buff, t_env *e, int fd);
int			send_to_user(char *from, char *msg, t_user *u);
int			send_to_group(char *from, char *msg, t_env *e, t_group *g);
int			nick(char *buff, t_env *e, int fd);
int			user(char *buff, t_env *e, int fd);
int			part(char *buff, t_env *e, int fd);
int			join(char *buff, t_env *e, int fd);
int			privmsg(char *buff, t_env *e, int fd);
int			start_listen(int p);
void			client_write(t_env *e, int fd);
void			client_read(t_env *e, int fd);
void			add_client(t_env *e, int s);
void			server_read(t_env *e, int fd);
void			add_server(int p, t_env *e);
int                     do_actions(char *buff, int i, t_env *e, int fd);
int                     do_handle(char *buff, t_env *e, int fd);
void			client_read(t_env *e, int fd);
#endif
