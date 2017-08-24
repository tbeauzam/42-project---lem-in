/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_windows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chkropok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 15:56:03 by chkropok          #+#    #+#             */
/*   Updated: 2017/04/01 23:57:57 by chkropok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_legend(t_data *d, int hei)
{
	wcolor_set(d->info->map, 8, NULL);
	mvwprintw(d->info->map, hei - 18, 1, "[%c]", d->start->name[0]);
	wcolor_set(d->info->map, 9, NULL);
	mvwprintw(d->info->map, hei - 17, 1, "[%c]", d->end->name[0]);
	wcolor_set(d->info->map, 5, NULL);
	mvwaddch(d->info->map, hei - 16, 24, ACS_DIAMOND);
	waddch(d->info->map, ACS_DIAMOND);
	waddch(d->info->map, ACS_DIAMOND);
	wcolor_set(d->info->map, 6, NULL);
	mvwaddch(d->info->map, hei - 17, 24, ACS_DIAMOND);
	waddch(d->info->map, ACS_DIAMOND);
	waddch(d->info->map, ACS_DIAMOND);
	wcolor_set(d->info->map, 1, NULL);
	mvwaddch(d->info->map, hei - 18, 24, ACS_DIAMOND);
	waddch(d->info->map, ACS_DIAMOND);
	waddch(d->info->map, ACS_DIAMOND);
	mvwprintw(d->info->map, hei - 18, 4, "%-20s", " : Starting room");
	mvwprintw(d->info->map, hei - 17, 4, "%-20s", " : Destination");
	mvwprintw(d->info->map, hei - 16, 1, "%-23s", "");
	mvwprintw(d->info->map, hei - 18, 27, "%-25s", " : A Link between Worlds");
	mvwprintw(d->info->map, hei - 17, 27, "%-25s", " : Shortest Path(s)");
	mvwprintw(d->info->map, hei - 16, 27, "%-25s", " : Longer Path(s)");
}

int				check_room_name(char **split, char *s)
{
	int			i;
	char		*tmp;

	i = 0;
	while (split[i])
	{
		tmp = ft_strchr(split[i], '-') + 1;
		if (ft_strequ(tmp, s))
			return (1);
		i += 1;
	}
	return (0);
}

static void		print_console(t_data *d, WINDOW *log, int wid, t_content *cur)
{
	(void)d;
	mvwprintw(log, 1, 5, "> ");
	if (cur->line)
		wprintw(log, "%-*s", (wid * 4), cur->line);
	else
		wprintw(log, "%-*s", (wid * 4), "");
	wrefresh(log);
}

void			handle_windows(t_data *d, int wid, int hei)
{
	print_title(d, wid, hei);
	print_ui(d, d->info->ui, wid, hei);
	print_console(d, d->info->console, wid, d->info->output_cur);
	print_map(d, d->info->map, wid, hei);
}
