/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_title.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauzam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 14:18:01 by tbeauzam          #+#    #+#             */
/*   Updated: 2017/03/28 23:20:35 by chkropok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_lemin(WINDOW *win, int wid)
{
	wcolor_set(win, 2, NULL);
	mvwprintw(win, 1, (wid / 4) - 15, "(         )          (       )");
	mvwprintw(win, 2, (wid / 4) - 15, ")\\ )     (  `(       )\\ ) ( /(");
	mvwprintw(win, 3, (wid / 4) - 15, "( )/( (   )\\ )(     (()/( )\\())");
	mvwprintw(win, 4, (wid / 4) - 15, "/(_)))\\ ((_)()\\     )/(_)|(_)\\");
	mvwprintw(win, 5, (wid / 4) - 15, "(_)) ((_)(_()((_)   (_))  _((_)");
	mvwprintw(win, 6, (wid / 4) - 20, "   `)%31s\\", "");
	mvwprintw(win, 7, (wid / 4) - 20, "  )((%31s))?", "");
	mvwprintw(win, 8, (wid / 4) - 20, ")_))(%30s)() )(", "");
	wcolor_set(win, 3, NULL);
	mvwprintw(win, 6, (wid / 4) - 15, "| |  | __|  \\/  |___|_ _|| \\| |");
	mvwprintw(win, 7, (wid / 4) - 15, "| |__| _|| |\\/| |___ | | | .` |");
	mvwprintw(win, 8, (wid / 4) - 15, "|____|___|_|  |_|   |___||_|\\_|");
}

void			print_title(t_data *d, int wid, int hei)
{
	hei = 0;
	print_lemin(d->info->header, wid);
	wrefresh(d->info->header);
}
