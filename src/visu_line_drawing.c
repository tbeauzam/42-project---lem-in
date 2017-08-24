/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_line_drawing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chkropok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 01:12:25 by chkropok          #+#    #+#             */
/*   Updated: 2017/04/01 01:48:20 by chkropok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_calc	*initialize_coords(t_room *cur, t_room *dest, int a)
{
	t_calc		*c;

	c = NULL;
	if (!(c = (t_calc *)malloc(sizeof(t_calc))))
		return (NULL);
	if (a)
	{
		c->x1 = cur->printed_x + 1;
		c->x2 = dest->printed_x + 1;
		c->y1 = cur->printed_y;
		c->y2 = dest->printed_y;
	}
	else
	{
		c->x1 = dest->printed_x + 1;
		c->x2 = cur->printed_x + 1;
		c->y1 = dest->printed_y;
		c->y2 = cur->printed_y;
	}
	return (c);
}

void			line_octant1(WINDOW *map, t_room *cur, t_room *dest)
{
	t_calc		*c;
	int			error;
	int			a;

	if (cur->printed_x >= dest->printed_x)
		c = initialize_coords(cur, dest, 0);
	else
		c = initialize_coords(cur, dest, 1);
	c->x_diff = c->x2 - c->x1;
	c->y_diff = c->y2 - c->y1;
	error = -c->x_diff >> 1;
	a = c->x1;
	while (c->x1 <= c->x2)
	{
		mvwaddch(map, c->y1, c->x1, ACS_DIAMOND);
		if ((error += c->y_diff) > 0)
		{
			error -= c->x_diff;
			c->y1 += 1;
		}
		c->x1 += 1;
	}
	free(c);
}

void			line_octant2(WINDOW *map, t_room *cur, t_room *dest)
{
	t_calc		*c;
	int			error;
	int			a;

	if (cur->printed_y >= dest->printed_y)
		c = initialize_coords(cur, dest, 0);
	else
		c = initialize_coords(cur, dest, 1);
	c->x_diff = c->x2 - c->x1;
	c->y_diff = c->y2 - c->y1;
	error = -c->y_diff >> 1;
	a = c->y1;
	while (c->y1 <= c->y2)
	{
		mvwaddch(map, c->y1, c->x1, ACS_DIAMOND);
		if ((error += c->x_diff) > 0)
		{
			error -= c->y_diff;
			c->x1 += 1;
		}
		c->y1 += 1;
	}
	free(c);
}

void			line_octant3(WINDOW *map, t_room *cur, t_room *dest)
{
	t_calc		*c;
	int			error;
	int			a;

	if (cur->printed_y >= dest->printed_y)
		c = initialize_coords(cur, dest, 0);
	else
		c = initialize_coords(cur, dest, 1);
	c->x_diff = c->x1 - c->x2;
	c->y_diff = c->y2 - c->y1;
	error = -c->y_diff >> 1;
	a = c->y1;
	while (c->y1 <= c->y2)
	{
		mvwaddch(map, c->y1, c->x1, ACS_DIAMOND);
		if ((error += c->x_diff) > 0)
		{
			error -= c->y_diff;
			c->x1 -= 1;
		}
		c->y1 += 1;
	}
	free(c);
}

void			line_octant4(WINDOW *map, t_room *cur, t_room *dest)
{
	t_calc		*c;
	int			error;
	int			a;

	if (cur->printed_x >= dest->printed_x)
		c = initialize_coords(cur, dest, 0);
	else
		c = initialize_coords(cur, dest, 1);
	c->x_diff = c->x2 - c->x1;
	c->y_diff = c->y1 - c->y2;
	error = -c->x_diff >> 1;
	a = c->x1;
	while (c->x1 <= c->x2)
	{
		mvwaddch(map, c->y1, c->x1, ACS_DIAMOND);
		if ((error += c->y_diff) > 0)
		{
			error -= c->x_diff;
			c->y1 -= 1;
		}
		c->x1 += 1;
	}
	free(c);
}

