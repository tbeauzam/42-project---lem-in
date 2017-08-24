/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chkropok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:09:39 by chkropok          #+#    #+#             */
/*   Updated: 2017/04/01 23:12:42 by chkropok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		create_some_colors(void)
{
	init_color(100, 402, 700, 282);
	init_color(101, 750, 400, 150);
	init_color(102, 950, 700, 150);
	init_color(103, 202, 900, 182);
	init_color(104, 750, 600, 100);
	init_color(105, 250, 450, 950);
	init_color(106, 850, 150, 150);
}

static int		handle_colors(void)
{
	start_color();
	if (!(can_change_color()))
		return (0);
	create_some_colors();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, 100, COLOR_BLACK);
	init_pair(3, 101, COLOR_BLACK);
	init_pair(4, COLOR_BLACK, 102);
	init_pair(5, 102, COLOR_BLACK);
	init_pair(6, 103, COLOR_BLACK);
	init_pair(7, 104, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, 105);
	init_pair(9, COLOR_BLACK, 106);
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
	return (1);
}

static int		init_display(t_info *info)
{
	setlocale(LC_ALL, "");
	initscr();
	if (!handle_colors())
		return (1);
	if (LINES < MIN_HEI || COLS < MIN_WID)
		return (2);
	info->term_hei = LINES;
	info->term_wid = COLS;
	info->used_hei = ((int)(LINES * 0.9) % 2 ? LINES * 0.9 + 1 : LINES * 0.9);
	info->used_wid = ((int)(COLS * 0.9) % 2 ? COLS * 0.9 + 1 : COLS * 0.9);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	color_set(1, NULL);
	refresh();
	freopen("/dev/tty", "rw", stdin);
	return (0);
}

static void		get_print_coord(t_room *cur, int wid, int hei)
{
	while (cur)
	{
		cur->printed_x = (cur->x * 3) + wid / 4;
		cur->printed_y = (cur->y * 2) + (hei - 16) / 2;
		cur = cur->next;
	}
}

int				handle_visu(t_data *d)
{
	int			ret;
	int			wid;
	int			hei;

	if ((ret = init_display(d->info)))
		return (ret);
	wid = d->info->used_wid;
	hei = d->info->used_hei;
	get_print_coord(d->head, wid, hei);
	d->info->header = newwin(10, wid, 0, (COLS / 2 - wid / 2));
	d->info->console = newwin(6, wid, hei - 5, (COLS / 2 - wid / 2));
	d->info->map = newwin(hei - 14, wid / 2, 9, (COLS / 2));
	d->info->ui = newwin(hei - 14, wid / 2 + 1, 9, (COLS / 2) - (wid / 2));
	while (1)
	{
		if (d->info->term_hei != LINES || d->info->term_wid != COLS)
			return (3);
		handle_windows(d, d->info->used_wid, d->info->used_hei);
		if (!handle_input(d))
			break ;
	}
	endwin();
	return (0);
}
