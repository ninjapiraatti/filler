/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placepiece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 09:36:29 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/13 11:11:42 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

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
	int	ph;
	int	pw;

	py = pc->offset_top;
	px = pc->offset_left;
	pw = pc->bottomrightx - pc->topleftX + 1;
	ph = pc->bottomrighty - pc->toplefty + 1;
	pc->bestvaluetemp = 0;
	pc->isvalidx = 0;
	while (py < pc->h)
	{
		while (px < pc->w)
		{
			if (y + py >= map->h || x + pw > map->w
			|| (y + py) < 0 || (x + px) < 0)
			{
				pc->isvaliddot = 0;
				pc->isvalidx = 0;
				return (0);
			}
			if (pc->pcmap[py][px] == '*')
			{
				if (map->map[y + py][x + px] == '.')
				{
					pc->isvaliddot = 1;
					pc->bestvaluetemp += map->heatmap[y + py][x + px];
					px++;
				}
				else if (map->map[y + py][x + px] == map->psymbol)
				{
					pc->isvalidx++;
					px++;
				}
				else
				{
					pc->isvaliddot = 0;
					pc->isvalidx = 0;
					return (0);
				}
			}
			else
				px++;
		}
		px = pc->offset_left;
		py++;
	}
	return (end_operations(map, pc, x, y));
}
