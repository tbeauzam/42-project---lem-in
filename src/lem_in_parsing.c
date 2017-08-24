/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chkropok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 22:47:38 by chkropok          #+#    #+#             */
/*   Updated: 2017/03/28 00:27:30 by chkropok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		set_start_end(t_data *d, t_room *cur)
{
	while (cur)
	{
		if (cur->id == d->start_id)
		{
			d->start = cur;
			d->start->path = 0;
			d->start->reached = 1;
		}
		else if (cur->id == d->end_id)
			d->end = cur;
		cur = cur->next;
	}
}

static void		clean_content(t_content *cur)
{
	char	*tmp;

	tmp = cur->line;
	if (tmp)
	{
		ft_strdel(&tmp);
		cur->line = NULL;
	}
}

static int		treat_content(t_data *d, t_content *cur)
{
	if (d->parsing_phase == 2)
		if (!acquire_room(d, cur->line))
			return (0);
	if (d->parsing_phase == 3)
		if (d->nb_rooms < 2 || !get_link(d, cur->line, d->head, 0))
		{
			d->parsing_phase = 4;
			return (0);
		}
	if (d->parsing_phase == 1)
		if (!look_for_ant_amount(d, cur->line))
			return (0);
	return (1);
}

int				parsing_hub(t_data *d)
{
	t_content		*cur;

	cur = d->content;
	while (cur)
	{
		if (!treat_content(d, cur))
		{
			clean_content(cur);
			break ;
		}
		cur = cur->next;
	}
	if (d->parsing_phase == 3)
		d->parsing_phase = 4;
	if (d->parsing_phase != 4)
		return (0);
	if (d->start_id == d->end_id || !d->start_id || !d->end_id
			|| d->nb_rooms <= 1)
		return (0);
	set_start_end(d, d->head);
	if (!(find_path(d, d->start)))
		return (0);
	return (1);
}
