/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chkropok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 23:18:16 by chkropok          #+#    #+#             */
/*   Updated: 2017/04/01 01:52:40 by chkropok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			print_path_list(t_data *d, t_path *cur, int wid, int hei)
{
	int				i;
	int				ret;

	while (cur && hei < d->info->term_hei - 6)
	{
		i = 0;
		wcolor_set(d->info->ui, (cur->shortest ? 6 : 5), NULL);
		ret = 0 * mvwprintw
(d->info->ui, hei, 3, "[%3d turns] : ", cur->nb_rooms);
		wcolor_set(d->info->ui, 1, NULL);
		while (cur->path[i])
		{
			if ((ret += 12) + (int)ft_strlen(cur->path[i]->name) > wid)
			{
				wprintw(d->info->ui, "...");
				break ;
			}
			ret += wprintw(d->info->ui, "%s", cur->path[i]->name);
			i += 1;
			if (cur->path[i])
				ret += wprintw(d->info->ui, " --> ");
		}
		hei += 1;
		cur = cur->next;
	}
}

static void			highlight_cur(t_content *cur, WINDOW *ui, int i, int wid)
{
	wcolor_set(ui, 4, NULL);
	if (cur->line && (int)ft_strlen(cur->line) > wid / 2 - 13)
		mvwprintw
(ui, 8 + i, 1, "%6d - %.*s...", cur->turn, wid / 2 - 16, cur->line);
	else if (cur->line)
		mvwprintw
(ui, 8 + i, 1, "%6d - %-*s", cur->turn, wid / 2 - 13, cur->line);
	else
		mvwprintw
(ui, 8 + i, 1, "%6d - %-*s", cur->turn, wid / 2 - 13, "~ beginning ~");
	wcolor_set(ui, 1, NULL);
}

static t_content	*find_first_line(t_data *d, t_content *cur, int max)
{
	t_content		*best;

	if (d->info->output_tail->turn < max)
		return (cur);
	best = d->info->output_tail;
	while (max > 1)
	{
		best = best->prev;
		max -= 1;
	}
	if (d->info->output_cur->turn < best->turn)
		while (d->info->output_cur->turn < best->turn)
			best = best->prev;
	return (best);
}

static void			print_move_list
	(t_data *d, WINDOW *ui, int wid, int hei_limit)
{
	int			i;
	t_content	*cur;

	i = 0;
	cur = find_first_line(d, d->info->output_head, hei_limit);
	while (i < hei_limit)
	{
		if (cur)
		{
			if (cur == d->info->output_cur)
				highlight_cur(cur, ui, i, wid);
			else if (cur->line && (int)ft_strlen(cur->line) > wid / 2 - 13)
				mvwprintw
(ui, 8 + i, 1, "%6d - %.*s...", cur->turn, wid / 2 - 16, cur->line);
			else if (cur->line)
				mvwprintw
(ui, 8 + i, 1, "%6d - %-*s", cur->turn, wid / 2 - 13, cur->line);
			else
				mvwprintw
(ui, 8 + i, 1, "%6d - %-*s", cur->turn, wid / 2 - 13, "~ beginning ~");
			cur = cur->next;
		}
		i += 1;
	}
}

void				print_ui(t_data *d, WINDOW *ui, int wid, int hei)
{
	int			bottom_hei;

	bottom_hei = hei - 16 - (0.1 * hei);
	wborder(ui, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
ACS_LTEE, ACS_HLINE, ACS_LTEE, ACS_HLINE);
	wcolor_set(ui, 1, NULL);
	mvwprintw(ui, 2, 2, "%10s", "NB ROOMS:");
	mvwprintw(ui, 5, 2, "%10s", "ANTS SENT:");
	mvwprintw(ui, 6, 2, "LIST OF MOVES:");
	mvwprintw(ui, bottom_hei, 2, "LIST OF PATHS:");
	wcolor_set(ui, 7, NULL);
	mvwprintw(ui, 2, 12, "  %d", d->nb_rooms);
	mvwprintw(ui, 5, 12, "  %12d / %d"
, d->info->output_cur->highest_ant, d->ant_amount);
	mvwprintw(ui, 6, 16, "  %8d / %d"
, d->info->output_cur->turn, d->info->output_tail->turn);
	if (d->nb_paths == 1)
		mvwprintw(ui, bottom_hei, 18, "%d path found!", d->nb_paths);
	else
		mvwprintw(ui, bottom_hei, 18, "%d paths found!", d->nb_paths);
	wcolor_set(ui, 1, NULL);
	print_move_list(d, ui, wid, bottom_hei - 10);
	print_path_list(d, d->paths_head, wid / 2 - 15, bottom_hei + 1);
	wrefresh(ui);
}
