/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chkropok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 16:03:47 by chkropok          #+#    #+#             */
/*   Updated: 2017/03/30 14:09:47 by tbeauzam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_content	*init_content(char *s)
{
	t_content		*c;

	c = NULL;
	if (!(c = (t_content *)malloc(sizeof(t_content))))
		return (NULL);
	c->line = NULL;
	if (!(c->line = ft_strdup(s)))
		return (NULL);
	c->next = NULL;
	c->prev = NULL;
	c->split = NULL;
	c->highest_ant = 0;
	c->turn = 0;
	return (c);
}

static int			add_to_content(t_data *d, char *line)
{
	t_content		*new;
	t_content		*tmp;

	if (!(new = init_content(line)))
		return (0);
	if (!d->content)
		d->content = new;
	else
	{
		tmp = d->content;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (1);
}

int					read_input(t_data *d)
{
	int		ret;
	char	*line;

	ret = 0;
	line = NULL;
	while ((ret = get_next_line(0, &line)) == 1)
	{
		add_to_content(d, line);
		ft_strdel(&line);
	}
	return (1);
}
