/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 10:24:12 by tlouekar          #+#    #+#             */
/*   Updated: 2020/06/29 10:56:32 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		checkadjacent(t_map *map, int x, int y)
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
	while (ping(map, x, y, map->psymbol, radius) < 1)
		radius++;
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
			if (map->map[y][x] == '.' && checkadjacent(map, x, y) == 1)
				map->heatmap[y][x] = doping(map, x, y);
			x++;
		}
		y++;
		x = 1;
	}
}

void	heatmap(t_map *map)
{
	iterate_map(map);
}