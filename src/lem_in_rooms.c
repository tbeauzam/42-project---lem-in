/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauzam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 13:52:03 by tbeauzam          #+#    #+#             */
/*   Updated: 2017/03/28 12:03:52 by tbeauzam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			clean_things(t_data *d, t_room *cur, t_room *tmp)
{
	while (cur)
	{
		if (cur != d->end && cur != d->start && !cur->used_in_path)
		{
			cur->path = -1;
			cur->reached = 0;
		}
		cur = cur->next;
	}
	tmp = d->head;
	d->i = -1;
}

int				check_room_duplicate(t_data *d, char *s, int i)
{
	t_room		*tmp;

	if (!(tmp = d->head))
		return (0);
	while (s[i] != ' ')
		i += 1;
	while (tmp)
	{
		if (ft_strnequ(s, tmp->name, i))
		{
			s = ft_strchr(s, ' ');
			tmp->x = ft_strtol(s, &s, 10);
			tmp->y = ft_strtol(s, &s, 10);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_path			*create_path(int nb)
{
	t_path		*new;
	int			i;

	new = NULL;
	if (!(new = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	new->path = NULL;
	if (!(new->path = (t_room **)malloc(sizeof(t_room *) * (nb + 1))))
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->nb_rooms = nb;
	new->shortest = 0;
	new->shorter = 0;
	new->id = 0;
	i = 0;
	while (i <= nb)
	{
		new->path[i] = NULL;
		i += 1;
	}
	return (new);
}

t_room			*create_room(void)
{
	t_room		*new;

	new = NULL;
	if (!(new = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	new->links = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->name = NULL;
	new->id = 1;
	new->reached = 0;
	new->path = -1;
	new->used_in_path = 0;
	new->x = 0;
	new->y = 0;
	new->nb_links = 0;
	new->f = 0;
	return (new);
}
