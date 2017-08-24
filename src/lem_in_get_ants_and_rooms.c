/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_get_ants_and_rooms.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chkropok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 23:16:41 by chkropok          #+#    #+#             */
/*   Updated: 2017/03/23 23:56:01 by chkropok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		add_room(t_data *d, char *s, int i)
{
	t_room		*new;

	if (!(new = create_room()))
		return (0);
	while (s[i] != ' ')
		i += 1;
	new->name = ft_strndup(s, i);
	s = ft_strchr(s, ' ');
	new->x = ft_strtol(s, &s, 10);
	new->y = ft_strtol(s, NULL, 10);
	if (!d->head)
	{
		new->id = 1;
		d->head = new;
		d->tail = new;
	}
	else
	{
		new->id = d->tail->id + 1;
		d->tail->next = new;
		new->prev = d->tail;
		d->tail = new;
	}
	return (1);
}

static int		next_check(t_data *d, char *s, int i)
{
	if (s[i] == '-')
		i += 1;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i += 1;
	}
	if (check_room_duplicate(d, s, 0))
		return (1);
	if (!add_room(d, s, 0))
		return (0);
	d->nb_rooms += 1;
	if (d->get_start)
	{
		d->start_id = d->tail->id;
		d->get_start = 0;
	}
	if (d->get_end)
	{
		d->end_id = d->tail->id;
		d->get_end = 0;
	}
	return (1);
}

static int		check_room_declaration(t_data *d, char *s)
{
	int		i;

	if (ft_str_count_char(s, ' ') != 2 || ft_strchr(" L", s[0]))
		return (0);
	i = 0;
	while (s[i] != ' ')
	{
		if (!ft_isprint(s[i]) || s[i] == '-')
			return (0);
		i += 1;
	}
	i += 1;
	if (s[i] == '-')
		i += 1;
	while (s[i] != ' ')
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i += 1;
	}
	i += 1;
	if (!next_check(d, s, i))
		return (0);
	return (1);
}

int				acquire_room(t_data *d, char *s)
{
	if (s && s[0] != '#' && ft_strchr(s, '-') && !ft_strchr(s, ' '))
	{
		d->parsing_phase = 3;
		if (!d->start_id || !d->end_id)
			return (0);
		return (1);
	}
	else if (ft_strequ(s, "##start"))
		return (d->get_start = 1);
	else if (ft_strequ(s, "##end"))
		return (d->get_end = 1);
	else if (s[0] == '#')
		return (1);
	else if (check_room_declaration(d, s))
		return (1);
	return (0);
}

int				look_for_ant_amount(t_data *d, char *s)
{
	int		i;

	i = 0;
	if (!s || ft_strequ(s, "##start") || ft_strequ(s, "##end"))
		return (0);
	else if (s[0] == '#')
		return (1);
	else if (ft_isdigit(s[0]))
	{
		while (s[i])
		{
			if (!ft_isdigit(s[i]))
				return (0);
			i += 1;
		}
		d->ant_amount = ft_strtol(s, NULL, 10);
		if (d->ant_amount > MAX_ANT_AMOUNT || d->ant_amount <= 0)
			return (0);
		d->parsing_phase = 2;
		return (1);
	}
	return (0);
}
