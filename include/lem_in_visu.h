/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_visu.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chkropok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 10:38:29 by chkropok          #+#    #+#             */
/*   Updated: 2017/04/01 01:11:39 by chkropok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_VISU_H
# define LEM_IN_VISU_H

# include "lem_in.h"
# include <curses.h>
# include <locale.h>

# define MIN_WID		120
# define MIN_HEI		40

typedef struct		s_calc
{
	int				x_diff;
	int				y_diff;
	int				x1;
	int				x2;
	int				y1;
	int				y2;
}					t_calc;

typedef struct			s_info
{
	struct s_content	*output_head;
	struct s_content	*output_tail;
	struct s_content	*output_cur;
	WINDOW				*header;
	WINDOW				*console;
	WINDOW				*map;
	WINDOW				*ui;
	int					can_print;
	int					used_wid;
	int					used_hei;
	int					term_wid;
	int					term_hei;
}						t_info;

#endif
