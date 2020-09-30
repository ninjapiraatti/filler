/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 10:24:12 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/12 18:23:19 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		doping(t_map *map, int x, int y)
{
	map->radius = 0;
	ping(map, x, y, map->osymbol);
	while (map->ping->count < 1 && map->radius < 40)
	{
		map->radius++;
		ping(map, x, y, map->osymbol);
	}
	return (map->radius);
}

/*
** Heatmap goes through the map but doesn't
** go to edges to avoid segfaults.
*/

void	heatmap(t_map *map)
{
	int	x;
	int	y;

	x = 1;
	y = 1;
	while (y < map->h - 1)
	{
		while (x < map->w - 1)
		{
			if (map->map[y][x] == '.')
				map->heatmap[y][x] = doping(map, x, y);
			else
				map->heatmap[y][x] = 0;
			x++;
		}
		y++;
		x = 1;
	}
}
