/*
** read_actions.c for my_irc in /home/xxx/Epitech/2015/PSU_2014_myirc
** 
** Made by 
** Login   <xxx@epitech.eu>
** 
** Started on  Wed Apr 15 22:33:18 2015 
** Last update Mon Apr 20 23:06:22 2015 
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
      printf("error: %s comand not recognized\n", buff);
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
  if ((str = strtok(buff, " ")) == NULL)
    return (EXIT_FAILURE);
  if (buff[0] == ':')
    if ((str = strtok(NULL, " ")) == NULL)
      return (EXIT_FAILURE);
  while (cmds[i] && strcmp(cmds[i], str))
    i++;
  if (do_actions(buff, i, e, fd))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

char			**to_tok(char *str, char **res)
{
  int			i;
  char			**send;

  res[0] = str;
  send = res;
  res++;
  i = 0;
  while (*str && i < 511)
    {
      if (*str == '\n' && *(str - 1) == '\r')
        {
          *str = '\0';
          if (*(str + 1))
            {
              *res = str + 1;
              res++;
            }
        }
      str++;
      i++;
    }
  *res = NULL;
  return (send);
}

void			client_read(t_env *e, int fd)
{
  char			**tok;
  int			r;
  char			buf[1024];
  char			*res[512];

  r = read(fd, buf, 512);
  if (r > 0)
    {
      buf[r] = '\0';
      tok = to_tok(buf, res);
      while(tok && *tok)
        {
          if (do_handle(*tok, e, fd))
            printf("Do handle %u\n", (unsigned int)r);
          tok++;
        }
    }
  else
    {
      printf("%s: Connection closed\n", e->nicks[fd]);
      close(fd);
      del_elem(e->users, e->nicks[fd]);
      free(e->nicks[fd]);
      e->nicks[fd] = NULL;
      e->fd_type[fd] = FD_FREE;
    }
}
