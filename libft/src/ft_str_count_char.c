/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_count_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauzam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 10:46:52 by tbeauzam          #+#    #+#             */
/*   Updated: 2017/03/22 10:50:15 by tbeauzam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_str_count_char(const char *s, char target)
{
	int		result;
	int		i;

	result = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == target)
			result += 1;
		i += 1;
	}
	return (result);
}
