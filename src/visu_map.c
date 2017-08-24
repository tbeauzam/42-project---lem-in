/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauzam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 13:10:47 by tbeauzam          #+#    #+#             */
/*   Updated: 2017/04/02 00:03:31 by chkropok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		draw_line(WINDOW *map, t_room *cur, t_room *dest)
{
	double		slope;

	slope = 0.0;
	if (cur->printed_x == dest->printed_x)
		line_octant3(map, cur, dest);
	slope = (double)(dest->printed_y - cur->printed_y)
/ (dest->printed_x - cur->printed_x);
	if (slope >= 0 && slope < 1)
		line_octant1(map, cur, dest);
	else if (slope >= 1)
		line_octant2(map, cur, dest);
	else if (slope < -1)
		line_octant3(map, cur, dest);
	else if (slope >= -1 && slope < 0)
		line_octant4(map, cur, dest);
}

static void		print_paths(WINDOW *map, t_path *cur, int wid, int hei)
{
	int			i;
	int			x1;
	int			x2;
	int			y1;
	int			y2;

	while (cur)
	{
		i = 0;
		wcolor_set(map, (cur->shortest ? 6 : 5), NULL);
		while (i < cur->nb_rooms)
		{
			x1 = cur->path[i]->printed_x;
			x2 = cur->path[i + 1]->printed_x;
			y1 = cur->path[i]->printed_y;
			y2 = cur->path[i + 1]->printed_y;
			if ((x1 > 0 && x1 < wid && y1 > 0 && y1 < hei)
					|| (x2 > 0 && x2 < wid && y2 > 0 && y2 < hei))
				draw_line(map, cur->path[i], cur->path[i + 1]);
			i += 1;
		}
		cur = cur->next;
	}
}

static void		print_links(WINDOW *map, t_room *cur, int wid, int hei)
{
	int			i;
	int			x1;
	int			x2;
	int			y1;
	int			y2;

	while (cur)
	{
		i = 0;
		while (cur->links && cur->links[i])
		{
			x1 = cur->printed_x;
			x2 = cur->links[i]->printed_x;
			y1 = cur->printed_y;
			y2 = cur->links[i]->printed_y;
			if (cur->id < cur->links[i]->id
					&& ((x1 > 0 && x1 < wid && y1 > 0 && y1 < hei)
					|| (x2 > 0 && x2 < wid && y2 > 0 && y2 < hei)))
				draw_line(map, cur, cur->links[i]);
			i += 1;
		}
		cur = cur->next;
	}
}

static void		print_rooms(t_data *d, t_room *cur, int wid, int hei)
{
	WINDOW		*map;

	map = d->info->map;
	print_links(map, cur, wid, hei);
	print_paths(map, d->paths_head, wid, hei);
	while (cur)
	{
		if (d->start == cur || d->end == cur)
			wcolor_set(d->info->map, (cur == d->start ? 8 : 9 ), NULL);
		else if (d->info->output_cur->line
				&& check_room_name(d->info->output_cur->split, cur->name))
			wcolor_set(d->info->map, 10, NULL);
		if (cur->printed_x > 0 && cur->printed_x < wid
				&& cur->printed_y > 0 && cur->printed_y < hei)
			mvwprintw
(map, cur->printed_y, cur->printed_x, "[%c]", cur->name[0]);
		wcolor_set(d->info->map, 1, NULL);
		cur = cur->next;
	}
	print_legend(d, hei);
}

void			print_map(t_data *d, WINDOW *map, int wid, int hei)
{
	t_room		*cur;

	cur = d->head;
	mvwprintw(map, 0, 0, "%*s", wid / 2 * hei, "");
	if (!d->info->can_print)
			mvwprintw(map, (hei - 15) / 2, wid / 4 - 8, "Can't print that!");
	else
		print_rooms(d, cur, wid / 2 - 2, hei);
	wborder(map, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
ACS_TTEE, ACS_URCORNER, ACS_BTEE, ACS_LRCORNER);
	wrefresh(map);
}
