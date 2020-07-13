/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placepiece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 09:36:29 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/13 12:53:57 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		isitonmap(t_map *map, t_piece *pc, int px, int py)
{
	if (pc->y + py >= map->h
	|| pc->x + (pc->bottomrightx - pc->topleftx + 1) > map->w
	|| (pc->y + py) < 0 || (pc->x + px) < 0)
	{
		pc->isvaliddot = 0;
		pc->isvalidx = 0;
		return (0);
	}
	return (1);
}

int		placepiece(t_map *map, t_piece *pc, int px, int py)
{
	if (pc->pcmap[py][px] == '*')
	{
		if (map->map[pc->y + py][pc->x + px] == '.')
		{
			pc->isvaliddot = 1;
			pc->bestvaluetemp += map->heatmap[pc->y + py][pc->x + px];
			return (1);
		}
		else if (map->map[pc->y + py][pc->x + px] == map->psymbol)
		{
			pc->isvalidx++;
			return (1);
		}
		else
		{
			pc->isvaliddot = 0;
			pc->isvalidx = 0;
			return (0);
		}
	}
	else
		return (1);
}

int		end_operations(t_map *map, t_piece *pc, int x, int y)
{
	if (pc->isvaliddot == 0 || pc->isvalidx == 0 || pc->isvalidx > 1)
	{
		pc->isvaliddot = 0;
		pc->isvalidx = 0;
		return (0);
	}
	if (pc->bestvaluetemp < pc->bestvalue && pc->bestvaluetemp > 0)
	{
		pc->bestvalue = pc->bestvaluetemp;
		pc->bestvaluex = x;
		pc->bestvaluey = y;
		pc->placey = pc->bestvaluey;
		pc->placex = pc->bestvaluex;
	}
	else if (pc->bestvalue != 1000000)
	{
		pc->placey = pc->bestvaluey;
		pc->placex = pc->bestvaluex;
	}
	else
	{
		pc->placey = y;
		pc->placex = x;
	}
	return (1);
}

int		isplacevalid(t_map *map, t_piece *pc, int x, int y)
{
	int	py;
	int	px;

	py = pc->offset_top;
	px = pc->offset_left;
	pc->bestvaluetemp = 0;
	pc->isvalidx = 0;
	pc->x = x;
	pc->y = y;
	while (py < pc->h)
	{
		while (px < pc->w)
		{
			if (isitonmap(map, pc, px, py) == 0)
				return (0);
			if (placepiece(map, pc, px, py) == 0)
				return (0);
			else
				px++;
		}
		px = pc->offset_left;
		py++;
	}
	return (end_operations(map, pc, pc->x, pc->y));
}
