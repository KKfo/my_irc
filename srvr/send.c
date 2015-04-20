/*
** send.c for my_irc in /home/xxx/Epitech/2015/PSU_2014_myirc
** 
** Made by 
** Login   <xxx@epitech.eu>
** 
** Started on  Thu Apr 16 12:39:41 2015 
** Last update Mon Apr 20 01:11:40 2015 
*/

#include		"../include/defs.h"

int			send_to_user(char *from, char *msg, t_user *u)
{
  /* char                  *t; */
  size_t		r;

  /* t = strtok(msg, "\n"); */
  if ((u->c + strlen(msg)) > (u->h + 1023))
    {
      printf("reset\n");
      u->c = u->h;
    }
  r = snprintf(u->c, 512, ":%s %s\n", from, msg) + 1;
  printf("cc %c\n", u->c[strlen(u->c)]);
  u->c[strlen(u->c)] = ' ';
  printf("Send message definitive : %s\n", u->buff);
  if ((u->c + r) < (u->h + 1023))
    u->c += r;
  else
    {
      printf("reset2\n");
      u->c = u->h;
    }
  return (0);
}

int			send_to_group(char *msg, t_env *e, t_group *g)
{
  UNUSED(msg);
  UNUSED(e);
  UNUSED(g);
  return (0);
}
