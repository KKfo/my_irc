/*
** actions.c for my_irc in /home/xxx/Epitech/2015/PSU_2014_myirc
** 
** Made by 
** Login   <xxx@epitech.eu>
** 
** Started on  Thu Apr 16 09:42:57 2015 
** Last update Mon Apr 20 22:49:06 2015 
*/

#include		"../include/defs.h"

int			nick(char *buff, t_env *e, int fd)
{
  char			*nick;
  char			*found;

  if (!buff || e->nicks[fd] != GUEST
      || !(nick = strtok(NULL, "\r")))
    return (0);
  if ((found = lookup_table(e->users, nick)))
    {
      printf("NICKNAME IN USE\n"); /* DEBUG */
      e->guest_buff[fd] = strdup(":my_irc 433 * xxx "
                                 ":Nickname is already in use.\r\n");
    }
  else
    {
      e->nicks[fd] = strdup(nick);
      if (e->guest_buff[fd])
        {
          free(e->guest_buff[fd]);
          e->guest_buff[fd] = NULL;
        }
    }
  return (0);
}

int			user(char *buff, t_env *e, int fd)
{
  t_user		*added;

  UNUSED(buff);
  if (e->nicks[fd] == GUEST)
    return (0);
  added = add_elem(e->users, e->nicks[fd], fd, sizeof(t_user));
  if (added)
    snprintf(added->buff, 1023, ":my_irc 001 %s :Welcome"
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
  char			*tmp;
  char                  *m;
  char			*to;
  void			*found;

  m = buff;
  if (e->nicks[fd] == GUEST || !buff
      || !(tmp = strtok(NULL, " ")))
    return (0);
  printf("tmp %s\n", tmp);
  to = strdup(tmp);
  buff[strlen(buff)] = ' ';
  tmp[strlen(tmp)] = ' ';
  if ((found = lookup_table(e->groups, to)))
    {
      send_to_group(buff, e, (t_group*)found);
    }
  else if ((found = lookup_table(e->users, to)))
    {
      printf("Send message: %s\n", m); /* DEBUG */
      send_to_user(e->nicks[fd], m, (t_user*)found);
    }
  else
    {
      found = lookup_table(e->users, e->nicks[fd]);
      snprintf(((t_user*)found)->buff, 1023, ":my_irc 401 %s"
               " %s :No such nick/channel\r\n", e->nicks[fd], to);
    }
  free(to);  
  return (0);
}
