/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:22:51 by msodor            #+#    #+#             */
/*   Updated: 2023/09/09 16:08:04 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_map_comp(char c)
{
	if (c == '1' || c == '0' || c == ' ')
		return (1);
	return (0);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	wall(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	check_map_closed(void)
{
	int	i;
	int	j;

	i = 0;
	while (g_inf.map[i])
	{
		j = 0;
		while (g_inf.map[i][j])
		{
			if (g_inf.map[i][j] == '0')
			{
				if ((ft_strlen(g_inf.map[i]) >= j && !wall(g_inf.map[i][j + 1]))
				|| (ft_strlen(g_inf.map[i]) >= j && !wall(g_inf.map[i][j - 1]))
				|| (g_inf.map[i + 1] && !wall(g_inf.map[i + 1][j]))
				|| (g_inf.map[i - 1][j] && !wall(g_inf.map[i - 1][j])))
					ft_err("Invalid map\n");
			}
			j++;
		}
		i++;
	}
	return (0);
}
