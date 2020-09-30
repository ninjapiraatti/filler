/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 10:24:12 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/01 09:24:51 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		adjacent(t_map *map, int x, int y)
{
	if (map->map[y][x + 1] == map->osymbol ||
	map->map[y][x - 1] == map->osymbol ||
	map->map[y + 1][x] == map->osymbol ||
	map->map[y - 1][x] == map->osymbol)
		return (1);
	return (0);
}

int		doping(t_map *map, int x, int y)
{
	int	radius;

	radius = 0;
	ping(map, x, y, map->osymbol, radius);
	while (map->ping->count < 1 && radius < 40)
	{
		radius++;
		ping(map, x, y, map->osymbol, radius);
	}
	return (radius);
}

/* Iterate_map goes through the map but doesn't go to edges to avoid segfaults. */

int		iterate_map(t_map *map)
{
	int	x;
	int	y;

	x = 1;
	y = 1;
	while (y < map->mapH - 1)
	{
		while (x < map->mapW - 1)
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
	return (0);
}

void	heatmap(t_map *map)
{
	iterate_map(map);
}