/*
** send.c for my_irc in /home/xxx/Epitech/2015/PSU_2014_myirc
** 
** Made by 
** Login   <xxx@epitech.eu>
** 
** Started on  Thu Apr 16 12:39:41 2015 
** Last update Fri Apr 24 03:31:47 2015 
*/

#include		"../include/defs.h"

int			send_to_user(char *from, char *msg, t_user *u)
{
  size_t		r;

  if ((u->c + strlen(msg) + strlen(from)) > (u->h + 1020))
    {
      u->c = u->h;
    }
  r = snprintf(u->c, 511, ":%s %s\n", from, msg);
  printf("Send message definitive : %s\n", u->buff);
  if ((u->c + r) < (u->h + 1023))
    u->c += r;
  else
    {
      u->c = u->h;
    }
  return (0);
}

int			respond(char *msg, t_user *u)
{
  size_t		r;

  if ((u->c + strlen(msg)) > (u->h + 1020))
    {
      u->c = u->h;
    }
  r = snprintf(u->c, 511, "%s\r\n", msg);
  if ((u->c + r) < (u->h + 1023))
    u->c += r;
  else
    {
      u->c = u->h;
    }
  return (0);
}

int			send_to_group(char *from, char *msg,
                                      t_env *e, t_group *g)
{
  int			i;
  t_user		**users;
  t_user		*us;

  i = 0;
  us = lookup_table(e->users, from);
  users = (t_user**)g->usrs->table;
  while (i < 244)
    {
      if (users[i] && i != us->hsh)
        send_to_user(from, msg, users[i]);
      ++i;
    }
  return (0);
}

void			set_nicks(char *b, t_user** users)
{
  int			r;
  int			i;

  i = 0;
  while (i < 255 && r < 510)
    {
      if (users[i])
        {
          r = snprintf(b, 10, "%s ", users[i]->name);
          b += r;
        }
      ++i;
    }
  return ;
}

void			send_join(char *usr, t_user** users,
                                  char *name, t_user *u)
{
  char			nicks[512];
  char			b[512];

  snprintf(b, 511, ":%s!~user@host JOIN %s", usr, name);
  respond(b, u);
  snprintf(b, 511, ":my_irc 332 %s "
           "%s :No topic", usr, name);
  respond(b, u);
  set_nicks(nicks, users);
  snprintf(b, 511, ":my_irc 353 %s = %s :%s", usr, name, nicks);
  respond(b, u);
  snprintf(b, 511, ":my_irc 366 %s %s :End of /NAMES list.", usr, name);
  respond(b, u);
  return ;
}
