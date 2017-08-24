/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lem_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chkropok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 12:37:55 by chkropok          #+#    #+#             */
/*   Updated: 2017/03/28 11:58:51 by tbeauzam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_data	*init_data(void)
{
	t_data *d;

	d = NULL;
	if (!(d = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	d->content = NULL;
	d->info = NULL;
	d->parsing_phase = 1;
	d->ant_amount = 0;
	d->ant_sent = 0;
	d->processed = 0;
	d->get_start = 0;
	d->get_end = 0;
	d->start_id = 0;
	d->end_id = 0;
	d->head = NULL;
	d->tail = NULL;
	d->start = NULL;
	d->end = NULL;
	d->nb_rooms = 0;
	d->paths_head = NULL;
	d->nb_paths = 0;
	d->i = 0;
	return (d);
}

int				main(void)
{
	t_data		*data;

	data = NULL;
	if (!(data = init_data()) || !(read_input(data)))
		return (ft_putendl("ERROR"));
	if (!(parsing_hub(data)))
		return (ft_putendl("ERROR"));
	print_result(data);
	return (0);
}
