/*
** read_actions.c for my_irc in /home/xxx/Epitech/2015/PSU_2014_myirc
** 
** Made by 
** Login   <xxx@epitech.eu>
** 
** Started on  Wed Apr 15 22:33:18 2015 
** Last update Thu Apr 16 12:35:14 2015 
*/

#include		"../include/defs.h"

int			do_actions(char *buff, int i, t_env *e, int fd)
{
  t_action		ptr_action[5] = {nick, user, part,
                                         join, privmsg};

  if (i < 5)
    {
      if (ptr_action[i](buff, e, fd) == EXIT_FAILURE)
        {
          return (EXIT_FAILURE);
        }
    }
  else
    {
      printf("error: comand not recognized\n");
    }
  return (0);
}

int			do_handle(char *buff, t_env *e, int fd)
{
  char			*str;
  int			i;
  char			*cmds[10] = {"NICK", "USER", "PART",
                                    "JOIN", "PRIVMSG", "",
                                    "", "", "",
                                    NULL};

  i = 0;
  str = strtok(buff, " ");
  if (buff[0] != ':')
    str = strtok(NULL, " ");
  while (cmds[i] && strcmp(cmds[i], str))
    i++;
  if (do_actions(buff, i, e, fd))
    return (EXIT_FAILURE);
  return (0);
}

void			client_read(t_env *e, int fd)
{
  size_t		r;
  char			buf[1024];

  r = read(fd, buf, 1023);
  if (r > 0)
    {
      buf[r] = '\0';
      do_handle(buf, e, fd);
    }
  else
    {
      printf("%d: Connection closed\n", fd);
      close(fd);
      e->fd_type[fd] = FD_FREE;
    }
}
