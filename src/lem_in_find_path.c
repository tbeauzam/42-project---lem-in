/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_find_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauzam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:22:57 by tbeauzam          #+#    #+#             */
/*   Updated: 2017/03/28 12:04:35 by tbeauzam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		verify_path(t_data *d, t_room *cur, int nb)
{
	int			i;

	while (nb > 0)
	{
		i = 0;
		while (i < cur->nb_links)
		{
			if ((cur->links[i] != d->end && cur->links[i]->path == nb - 1
					&& cur->links[i]->used_in_path == 0)
					|| (cur->links[i] == d->start && nb - 1 == 0))
				break ;
			i += 1;
		}
		if (i == cur->nb_links)
			return (0);
		cur = cur->links[i];
		nb -= 1;
	}
	return (1);
}

static void		dig_for_path(t_data *d, t_path *new, t_room *cur, int nb)
{
	int			i;

	if (nb == cur->path)
		new->shortest = 1;
	while (nb > 0)
	{
		new->path[nb] = cur;
		if (cur != d->end && cur != d->start)
			cur->used_in_path = 1;
		i = 0;
		while (i < cur->nb_links)
		{
			if ((cur->links[i] != d->end && cur->links[i]->path == nb - 1
					&& cur->links[i]->used_in_path == 0)
					|| (cur->links[i] == d->start && nb - 1 == 0))
				break ;
			i += 1;
		}
		cur = cur->links[i];
		nb -= 1;
	}
	new->path[0] = d->start;
}

static int		memorize_path(t_data *d, t_room *t, t_room *cur, int nb_rooms)
{
	t_path		*new;
	t_path		*tmp;

	if (!(new = create_path(nb_rooms + 1)))
		return (0);
	new->nb_rooms = nb_rooms;
	dig_for_path(d, new, cur, nb_rooms);
	if (!d->paths_head)
		d->paths_head = new;
	else
	{
		tmp = d->paths_head;
		while (tmp->next)
			tmp = tmp->next;
		new->id = tmp->id + 1;
		tmp->next = new;
		new->prev = tmp;
	}
	d->nb_paths += 1;
	clean_things(d, d->head, t);
	return (1);
}

static int		mark_the_links(t_data *d, t_room *cur, int max, int i)
{
	int			j;

	j = 0;
	while (j < max)
	{
		if (!cur->links[j]->reached && cur->links[j] != d->end
				&& !cur->links[j]->used_in_path)
		{
			cur->links[j]->reached += 1;
			cur->links[j]->path = i;
		}
		else if (cur->links[j] == d->end)
		{
			if (cur->links[j]->path == -1 || i == cur->links[j]->path)
				cur->links[j]->path = i;
			cur->links[j]->reached += 1;
			if (verify_path(d, d->end, i))
			{
				memorize_path(d, cur, d->end, i);
				return (1);
			}
		}
		j += 1;
	}
	return (0);
}

int				find_path(t_data *d, t_room *cur)
{
	int			j;

	j = 0;
	while (!d->end->reached || d->i <= d->nb_rooms)
	{
		cur = d->head;
		j = 0;
		while (cur)
		{
			if (cur->path == d->i && cur != d->end && !cur->used_in_path)
				if (mark_the_links(d, cur, cur->nb_links, d->i + 1))
					break ;
			cur = cur->next;
		}
		d->i += 1;
		if (d->i > d->nb_rooms
				|| (d->paths_head && d->paths_head->nb_rooms == 1))
			break ;
	}
	if (!d->end->reached)
		return (0);
	return (1);
}
