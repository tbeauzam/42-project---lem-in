/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chkropok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 11:28:56 by chkropok          #+#    #+#             */
/*   Updated: 2017/03/25 22:15:56 by chkropok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		init_links(t_room **links, t_room **tmp)
{
	int		i;

	i = 0;
	while (links[i])
	{
		tmp[i] = links[i];
		i += 1;
	}
	free(links);
	links = NULL;
	return (1);
}

static t_room	**handle_link_tab(t_room *cur, t_room *dest, int i)
{
	t_room		**tmp;

	tmp = NULL;
	cur->nb_links += 1;
	if (!(tmp = (t_room **)malloc(sizeof(t_room *) * (cur->nb_links + 1))))
		return (NULL);
	while (i < cur->nb_links + 1)
	{
		tmp[i] = NULL;
		i += 1;
	}
	if (!cur->links)
	{
		cur->links = tmp;
		tmp[0] = dest;
	}
	else
	{
		init_links(cur->links, tmp);
		tmp[i - 2] = dest;
	}
	return (tmp);
}

static int		check_link_duplicate(t_room **links, t_room *dest)
{
	int			i;

	i = 0;
	if (!links)
		return (0);
	while (links[i])
	{
		if (links[i] == dest)
			return (1);
		i += 1;
	}
	return (0);
}

static int		establish_link(t_data *d, char *s, char *tmp, int len)
{
	t_room		*cur;
	t_room		*dest;

	cur = d->head;
	dest = d->head;
	while (dest)
	{
		if (ft_strequ(tmp, dest->name))
			break ;
		dest = dest->next;
	}
	while (cur)
	{
		if (ft_strnequ(s, cur->name, len))
			break ;
		cur = cur->next;
	}
	if (!dest || !cur)
		return (0);
	if (check_link_duplicate(cur->links, dest))
		return (1);
	cur->links = handle_link_tab(cur, dest, 0);
	dest->links = handle_link_tab(dest, cur, 0);
	return (1);
}

int				get_link(t_data *d, char *s, t_room *cur, int result)
{
	char		*tmp;
	char		tmp2[ft_strlen(s)];
	int			len;

	if (s[0] == '#')
		return (1);
	if (!(tmp = ft_strchr(s, '-')) || s[0] == '-')
		return (0);
	len = ft_strlen(s) - ft_strlen(tmp);
	tmp += 1;
	ft_bzero(tmp2, len + 1);
	ft_memmove(tmp2, s, len);
	while (cur)
	{
		if (ft_strequ(tmp2, cur->name))
			result += 1;
		else if (ft_strequ(tmp, cur->name))
			result += 1;
		cur = cur->next;
	}
	if (result != 2)
		return (0);
	if (!establish_link(d, s, tmp, len))
		return (0);
	return (1);
}
