/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_place.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 09:20:38 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/14 11:13:52 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

/*
** loopcircle fires the placement in all directions
*/

void	loopcircle(t_map *map, t_piece *pc, int x, int y)
{
	if (placement(map, pc, map->tempx + x, map->tempy + y))
		map->validplaces++;
	if (placement(map, pc, map->tempx + y, map->tempy + x))
		map->validplaces++;
	if (placement(map, pc, map->tempx - y, map->tempy + x))
		map->validplaces++;
	if (placement(map, pc, map->tempx - x, map->tempy + y))
		map->validplaces++;
	if (placement(map, pc, map->tempx - x, map->tempy - y))
		map->validplaces++;
	if (placement(map, pc, map->tempx - y, map->tempy - x))
		map->validplaces++;
	if (placement(map, pc, map->tempx + y, map->tempy - x))
		map->validplaces++;
	if (placement(map, pc, map->tempx + x, map->tempy - y))
		map->validplaces++;
}

/*
** midpoint uses mid-point-algorithm to search for good spots
** in a circular, expanding pattern.
*/

int		midpoint(t_map *map, t_piece *pc, int tries, int threshold)
{
	int	x;
	int	y;
	int	err;

	x = map->radius;
	y = 0;
	err = 0;
	while (x >= y)
	{
		if (map->validplaces > threshold)
			return (1);
		loopcircle(map, pc, x, y);
		err <= 0 ? y += 1 : 0;
		err <= 0 ? err += 2 * y + 1 : 0;
		err > 0 ? x -= 1 : 0;
		err > 0 ? err -= 2 * x + 1 : 0;
	}
	map->radius++;
	if (tries % TRIES_INTERVAL == 0)
		map->tempx++;
	return (0);
}

/*
** recursion tries to find the optimal spot for the piece
** and if everything else fails, searches through the entire map.
** Magic number -80 is there to account for pieces with large top offset.
*/

int		recursion(t_map *map, t_piece *pc, int tries)
{
	int	x;
	int	y;

	y = -80;
	x = -80;
	tries++;
	if (tries > TRIES)
	{
		while (y < map->h)
		{
			x = -80;
			while (x++ < map->w)
			{
				if (placement(map, pc, x, y) == 1)
					return (1);
			}
			y++;
		}
		return (0);
	}
	if (midpoint(map, pc, tries, map->threshold) == 1)
		return (1);
	if (recursion(map, pc, tries) == 0)
		return (0);
	return (1);
}

/*
** search_place runs the recursion and frees the piece.
*/

int		search_place(t_map *map, t_piece *pc)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	map->radius = 0;
	map->validplaces = 0;
	if (recursion(map, pc, 2) == 1)
	{
		while (j < pc->h)
		{
			free(pc->pcmap[j]);
			j++;
		}
		return (1);
	}
	return (0);
}
