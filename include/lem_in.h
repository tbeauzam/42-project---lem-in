/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chkropok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 12:40:51 by chkropok          #+#    #+#             */
/*   Updated: 2017/04/01 23:42:19 by chkropok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/include/libft.h"
# include "lem_in_visu.h"

# define MAX_ANT_AMOUNT		1000000000
# define MAX_COORD			500

typedef struct				s_content
{
	struct s_content		*next;
	struct s_content		*prev;
	char					**split;
	char					*line;
	int						highest_ant;
	int						turn;
}							t_content;

typedef struct				s_path
{
	struct s_room			**path;
	struct s_path			*next;
	struct s_path			*prev;
	int						nb_rooms;
	int						shortest;
	int						shorter;
	int						id;
}							t_path;

typedef struct				s_room
{
	struct s_room			**links;
	struct s_room			*next;
	struct s_room			*prev;
	char					*name;
	int						id;
	int						reached;
	int						path;
	int						used_in_path;
	int						x;
	int						y;
	int						printed_x;
	int						printed_y;
	int						nb_links;
	int						f;
}							t_room;

typedef struct				s_data
{
	t_info					*info;
	t_room					*head;
	t_room					*tail;
	t_room					*start;
	t_room					*end;
	t_path					*paths_head;
	t_content				*content;
	int						parsing_phase;
	int						ant_amount;
	int						ant_sent;
	int						processed;
	int						get_start;
	int						get_end;
	int						start_id;
	int						end_id;
	int						nb_rooms;
	int						nb_paths;
	int						i;
}							t_data;

int							read_input(t_data *d);
int							parsing_hub(t_data *d);
int							look_for_ant_amount(t_data *d, char *s);
int							acquire_room(t_data *d, char *s);
t_room						*create_room(void);
t_path						*create_path(int nb);
int							check_room_duplicate(t_data *d, char *s, int i);
int							get_link(t_data *d, char *s, t_room *cur, int res);
int							find_path(t_data *d, t_room *cur);
void						clean_things(t_data *d, t_room *cur, t_room *tmp);
void						print_result(t_data *d);

int							check_output(t_data *d);
int							handle_visu(t_data *d);
void						handle_windows(t_data *d, int wid, int hei);
int							handle_input(t_data *d);
void						print_title(t_data *d, int wid, int hei);
void						print_ui(t_data *d, WINDOW *ui, int wid, int hei);
void						print_map(t_data *d, WINDOW *map, int wid, int hei);
void						line_octant1(WINDOW *map, t_room *cur, t_room *dst);
void						line_octant2(WINDOW *map, t_room *cur, t_room *dst);
void						line_octant3(WINDOW *map, t_room *cur, t_room *dst);
void						line_octant4(WINDOW *map, t_room *cur, t_room *dst);
int							check_room_name(char **split, char *s);
void						print_legend(t_data *d, int hei);

#endif
