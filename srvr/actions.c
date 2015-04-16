/*
** actions.c for my_irc in /home/xxx/Epitech/2015/PSU_2014_myirc
** 
** Made by 
** Login   <xxx@epitech.eu>
** 
** Started on  Thu Apr 16 09:42:57 2015 
** Last update Thu Apr 16 12:41:52 2015 
*/

#include		"../include/defs.h"

int			nick(char *buff, t_env *e, int fd)
{
  char			*nick;
  char			*found;

  if (buff != NULL)
    {
      nick = strtok(NULL, "\r");
      if (!nick)
        return (0);
      printf("nick to search %s\n", nick);  /* DEBUG */
      found = lookup_table(e->users, nick);
      if (found != NULL)
        e->guest_buff[fd] = strdup(":my_irc 433 * xxx "
                                   ":Nickname is already in use.\r\n");
      else
        {
          add_elem(e->users, nick, fd, sizeof(t_user));
          e->nicks[fd] = nick;
        }
    }
  return (0);
}

int			user(char *buff, t_env *e, int fd)
{
  UNUSED(buff);
  UNUSED(e);
  write(fd, ":my_irc 001 xxx1 :Welcome to the my_irc server xxx1\r\n"
        , strlen(":my_irc 001 xxx1 :Welcome to the my_irc server xxx1\r\n"));
  return (0);
}

int			part(char *buff, t_env *e, int fd)
{
  UNUSED(buff);
  UNUSED(e);
  UNUSED(fd);
  return (0);
}

int			join(char *buff, t_env *e, int fd)
{
  UNUSED(buff);
  UNUSED(e);
  UNUSED(fd);
  return (0);
}

int			privmsg(char *buff, t_env *e, int fd)
{
  char			*to;
  char			*found;

  if (buff != NULL)
    {
      to = strtok(NULL, " ");
      if (!to)
        return (0);
      if ((found = lookup_table(e->groups, to)))
        {
          send_to_group(buff, e, to);
        }
      else if ((found = lookup_table(e->users, to)))
        {
          send_to_user(buff, e, to);
        }
      else
        e->guest_buff[fd] = strdup(":my_irc 433 * xxx "
                                   ":Nickname is already in use.\r\n");
    }
  return (0);
}
