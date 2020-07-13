/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchplace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:39:54 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/13 10:57:50 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	loopcircle(t_map *map, t_piece *pc, int x, int y)
{
	if (isplacevalid(map, pc, map->tempx + x, map->tempy + y))
		map->validplaces++;
	if (isplacevalid(map, pc, map->tempx + y, map->tempy + x))
		map->validplaces++;
	if (isplacevalid(map, pc, map->tempx - y, map->tempy + x))
		map->validplaces++;
	if (isplacevalid(map, pc, map->tempx - x, map->tempy + y))
		map->validplaces++;
	if (isplacevalid(map, pc, map->tempx - x, map->tempy - y))
		map->validplaces++;
	if (isplacevalid(map, pc, map->tempx - y, map->tempy - x))
		map->validplaces++;
	if (isplacevalid(map, pc, map->tempx + y, map->tempy - x))
		map->validplaces++;
	if (isplacevalid(map, pc, map->tempx + x, map->tempy - y))
		map->validplaces++;
}

int		drawcircle(t_map *map, t_piece *pc, int tries, int threshold)
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

int		recursion(t_map *map, t_piece *pc, int tries)
{
	int	x;
	int	y;

	y = -80;
	x = -80;
	tries++;
	if (tries > 2000)
	{
		while (y < map->h)
		{
			x = -80;
			while (x++ < map->w)
			{
				if (isplacevalid(map, pc, x, y) == 1)
					return (1);
			}
			y++;
		}
		return (0);
	}
	if (drawcircle(map, pc, tries, map->threshold) == 1)
		return (1);
	if (recursion(map, pc, tries) == 0)
		return (0);
	return (1);
}

int		searchplace(t_map *map, t_piece *pc, int strategy)
{
	int	i;

	i = 0;
	map->radius = 0;
	map->validplaces = 0;
	if (recursion(map, pc, 2) == 1)
		return (1);
	ft_putstr_fd("Failed to place a piece:\n", 2);
	while (i < pc->h)
	{
		ft_putstr_fd(pc->pcmap[i], 2);
		ft_putstr_fd("\n", 2);
		i++;
	}
	return (0);
}
