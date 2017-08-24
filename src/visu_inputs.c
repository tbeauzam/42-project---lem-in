/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chkropok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:05:45 by chkropok          #+#    #+#             */
/*   Updated: 2017/03/31 23:49:18 by chkropok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		move_map(t_room *cur, int x, int y)
{
	while (cur)
	{
		cur->printed_x += x;
		cur->printed_y += y;
		cur = cur->next;
	}
}

int				handle_input(t_data *d)
{
	int		ch;

	ch = getch();
	mvprintw(0, 0, "Input: %5d", ch);
	if (ch == 113)
		return (0);
	else if (ch == 338 && d->info->output_cur != d->info->output_tail)
		d->info->output_cur = d->info->output_cur->next;
	else if (ch == 339 && d->info->output_cur != d->info->output_head)
		d->info->output_cur = d->info->output_cur->prev;
	else if (ch == 258)
		move_map(d->head, 0, 3);
	else if (ch == 259)
		move_map(d->head, 0, -3);
	else if (ch == 260)
		move_map(d->head, -5, 0);
	else if (ch == 261)
		move_map(d->head, 5, 0);
	return (1);
}
