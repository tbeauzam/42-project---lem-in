/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chkropok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 22:53:01 by chkropok          #+#    #+#             */
/*   Updated: 2017/03/29 00:22:39 by chkropok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		cant_handle_my_swag(int code)
{
	clear();
	refresh();
	endwin();
	ft_putendl("CAN'T HANDLE MY SWAG");
	if (code == 1)
		ft_putendl("(your terminal does not support custom colors)");
	if (code == 2)
		ft_putendl("(your terminal is too small)");
	if (code == 3)
		ft_putendl("(please do not resize term while visualizer is running)");
	return (1);
}

static t_info	*init_info(void)
{
	t_info		*info;

	info = NULL;
	if (!(info = (t_info *)malloc(sizeof(t_info))))
		return (NULL);
	info->term_wid = 0;
	info->term_hei = 0;
	info->used_wid = 0;
	info->used_hei = 0;
	info->output_head = NULL;
	info->output_tail = NULL;
	info->output_cur = NULL;
	info->header = NULL;
	info->console = NULL;
	info->map = NULL;
	return (info);
}

static t_data	*init_data(void)
{
	t_data		*d;

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
	int			ret;

	data = NULL;
	if (!(data = init_data()) || !(read_input(data)))
		return (ft_putendl("ERROR"));
	if (!(parsing_hub(data)))
		return (ft_putendl("ERROR"));
	if (!(data->info = init_info()))
		return (ft_putendl("ERROR"));
	if (!(check_output(data)))
		return (ft_putendl("ERROR"));
	if ((ret = handle_visu(data)))
		return (cant_handle_my_swag(ret));
	ft_printf("Pas error.\n");
	return (0);
}
