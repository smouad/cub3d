/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:02:20 by msodor            #+#    #+#             */
/*   Updated: 2023/08/03 15:12:38 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int main(int ac, char **av)
{
	t_elems map;

	if (ac != 2)
	{
		printf("Error\n");
		return 1;
	}
	init_info(&map, av[1]);
	get_game_info(&map);
	if (!map.ea || !map.no || !map.so || !map.we)
	{
		perror("Error\n");
		return 1;
	}
	printf("EA: %s\n", map.ea);
	printf("NO: %s\n", map.no);
	printf("SO: %s\n", map.so);
	printf("WE: %s\n", map.we);
}