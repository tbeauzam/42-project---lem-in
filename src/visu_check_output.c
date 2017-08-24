/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_check_output.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chkropok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 23:14:35 by chkropok          #+#    #+#             */
/*   Updated: 2017/03/31 13:35:08 by tbeauzam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		parse_word(t_data *d, t_content *c, char *s)
{
	int			nb;
	t_room		*cur;

	if ((nb = ft_strtol(s, &s, 10)) < 1 || nb > d->ant_amount || s[0] != '-')
		return (0);
	if (c->highest_ant < nb)
		c->highest_ant = nb;
	s += 1;
	cur = d->head;
	while (cur)
	{
		if (ft_strequ(s, cur->name))
			break ;
		cur = cur->next;
	}
	if (!cur)
		return (0);
	return (1);
}

static int		analyse_split(t_data *d, t_content *cur, char **split, int i)
{
	while (split[i])
	{
		if (split[i][0] != 'L' || ft_str_count_char(split[i], '-') != 1)
			return (0);
		if (!parse_word(d, cur, split[i] + 1))
			return (0);
		i += 1;
	}
	return (1);
}

static int		carefully_check_lines(t_data *d, t_content *cur, int i)
{
	char		*tmp;
	int			len;

	while (cur)
	{
		tmp = cur->line;
		if ((len = ft_strlen(tmp)) < 4)
			return (0);
		if (tmp[len - 1] == ' ')
			tmp[len - 1] = '\0';
		if (!cur->line || !(cur->split = ft_strsplit(tmp, ' ')))
			return (0);
		if (!(analyse_split(d, cur, cur->split, 0)))
			return (0);
		cur->turn = i;
		i += 1;
		if (!cur->next)
			d->info->output_tail = cur;
		cur = cur->next;
	}
	return (1);
}
static int		can_print_rooms(t_room *cur)
{
	while (cur)
	{
		if (cur->x > MAX_COORD || cur->y > MAX_COORD)
			return (0);
		if (cur->x < -MAX_COORD || cur->y < -MAX_COORD)
			return (0);
		cur = cur->next;
	}
	return (1);
}

int				check_output(t_data *d)
{
	t_content	*cur;

	cur = d->content;
	while (cur)
	{
		if (!cur->line)
		{
			d->info->output_head = cur;
			d->info->output_cur = cur;
			cur = cur->next;
			break ;
		}
		cur = cur->next;
	}
	if (!cur)
		return (0);
	if (!(carefully_check_lines(d, cur, 1)))
		return (0);
	d->info->can_print = can_print_rooms(d->head);
	return (1);
}
