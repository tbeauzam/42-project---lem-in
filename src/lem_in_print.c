/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chkropok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:36:31 by chkropok          #+#    #+#             */
/*   Updated: 2017/04/02 00:22:35 by chkropok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		move_ants(t_data *d, t_path *cur, int i)
{
	while (cur)
	{
		i = cur->nb_rooms;
		while (i > 1)
		{
			if (cur->path[i - 1]->f)
			{
				ft_printf("L%d-%s ", cur->path[i - 1]->f, cur->path[i]->name);
				if (i != cur->nb_rooms)
					cur->path[i]->f = cur->path[i - 1]->f;
				else if (i == cur->nb_rooms)
					d->processed += 1;
				cur->path[i - 1]->f = 0;
			}
			i -= 1;
		}
		cur = cur->next;
	}
}

static void		send_with_method(t_data *d, t_path *cur)
{
	move_ants(d, d->paths_head, 0);
	if (d->ant_sent < d->ant_amount)
	{
		cur = d->paths_head;
		while (cur && d->ant_sent < d->ant_amount)
		{
			if (cur->shortest)
			{
				d->ant_sent += 1;
				cur->path[1]->f = d->ant_sent;
				ft_printf("L%d-%s ", cur->path[1]->f, cur->path[1]->name);
			}
			else if (d->ant_amount - d->ant_sent + d->paths_head->nb_rooms
					>= cur->nb_rooms + (cur->nb_rooms - cur->prev->nb_rooms))
			{
				d->ant_sent += 1;
				cur->path[1]->f = d->ant_sent;
				ft_printf("L%d-%s ", cur->path[1]->f, cur->path[1]->name);
			}
			cur = cur->next;
		}
	}
	ft_printf("\n");
}

static void		put_everything_here(t_data *d)
{
	int			i;

	i = 0;
	while (i < d->ant_amount)
	{
		ft_printf("L%d-%s ", i + 1, d->end->name);
		i += 1;
	}
	ft_printf("\n");
}

static void		print_treated_input(t_content *cur, t_path *tmp)
{
	while (cur)
	{
		if (cur->line)
			ft_printf("%s\n", cur->line);
		else
			break ;
		cur = cur->next;
	}
	while (tmp)
	{
		if (tmp->prev)
		{
			if (tmp->prev->nb_rooms < tmp->nb_rooms)
				tmp->shorter = tmp->prev->nb_rooms;
			else
				tmp->shorter = tmp->prev->nb_rooms;
		}
		tmp = tmp->next;
	}
	ft_printf("\n");
}

void			print_result(t_data *d)
{
	print_treated_input(d->content, d->paths_head);
	if (d->paths_head->shortest && d->paths_head->nb_rooms == 1)
		put_everything_here(d);
	else
		while (d->processed < d->ant_amount)
			send_with_method(d, d->paths_head);
}
