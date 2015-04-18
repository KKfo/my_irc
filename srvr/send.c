/*
** send.c for my_irc in /home/xxx/Epitech/2015/PSU_2014_myirc
** 
** Made by 
** Login   <xxx@epitech.eu>
** 
** Started on  Thu Apr 16 12:39:41 2015 
** Last update Sat Apr 18 21:29:37 2015 
*/

#include		"../include/defs.h"

int			send_to_user(char *from, char *msg, t_user *u)
{
  snprintf(u->buff, 1023, ":%s %s", from, msg);
  /* memcpy(u->buff, msg, strlen(msg)); */
  /* memcpy(u->buff, msg, strlen(msg)); */
  return (0);
}

int			send_to_group(char *msg, t_env *e, t_group *g)
{
  UNUSED(msg);
  UNUSED(e);
  UNUSED(g);
  return (0);
}
