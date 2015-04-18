/*
** actions.c for my_irc in /home/xxx/Epitech/2015/PSU_2014_myirc
** 
** Made by 
** Login   <xxx@epitech.eu>
** 
** Started on  Thu Apr 16 09:42:57 2015 
** Last update Sat Apr 18 23:34:00 2015 
*/

#include		"../include/defs.h"

int			nick(char *buff, t_env *e, int fd)
{
  char			*nick;
  char			*found;

  if (buff != NULL)
    {
      nick = strdup(strtok(NULL, "\r"));
      if (!nick)
        return (0);
      printf("nick to search %s\n", nick);  /* DEBUG */
      found = lookup_table(e->users, nick);
      if (found != NULL)
        {
          printf("NICKNAME IN USE\n"); /* DEBUG */
          e->guest_buff[fd] = strdup(":my_irc 433 * xxx "
                                   ":Nickname is already in use.\r\n");
        }
      else
        {
          add_elem(e->users, nick, fd, sizeof(t_user));
          free(e->nicks[fd]); /* ADDED */
          e->nicks[fd] = nick;
          if (e->guest_buff[fd])
            {
              free(e->guest_buff[fd]);
              e->guest_buff[fd] = NULL;
            }
        }
    }
  return (0);
}

int			user(char *buff, t_env *e, int fd)
{
  t_user		*found;

  UNUSED(buff);
  if (e->guest_buff[fd])
    return (0);
  found = lookup_table(e->users, e->nicks[fd]);
  snprintf(found->buff, 1023, ":my_irc 001 %s :Welcome"
           " to the my_irc server %s\r\n", e->nicks[fd], e->nicks[fd]);
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
  char                  *m;
  char			*to;
  void			*found;

  if (strcmp(e->nicks[fd], "guest") == 0)
    return (0);
  if (buff != NULL)
    {
      buff[strlen(buff)] = ' ';
      m = strdup(buff);
      to = strtok(NULL, " ");
      if (!to)
        return (0);
      if ((found = lookup_table(e->groups, to)))
        {
          send_to_group(buff, e, (t_group*)found);
        }
      else if ((found = lookup_table(e->users, to)))
        {
          send_to_user(e->nicks[fd], m, (t_user*)found);
        }
      else
        {
          found = lookup_table(e->users, e->nicks[fd]);
          snprintf(((t_user*)found)->buff, 1023, ":my_irc 401 %s"
                   " %s :No such nick/channel\r\n", e->nicks[fd], to);
        }
      free(m);  
    }
  return (0);
}
