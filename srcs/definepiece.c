/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definepiece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:16:21 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/12 18:29:55 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void		offset_left(t_piece *pc)
{
	int		left;
	int		x;
	int		y;

	left = 0;
	x = 0;
	y = 0;
	while (x < (pc->piecew))
	{
		y = 0;
		while (y < (pc->pieceh))
		{
			if (pc->pcmap[y][x] == '*' && pc->offset_left == -1)
			{
				pc->offset_left = left;
				y++;
			}
			else
				y++;
		}
		x++;
		left++;
	}
}

void		offset_top(t_piece *pc)
{
	int		top;
	int		x;
	int		y;

	top = 0;
	x = 0;
	y = 0;
	while (y < (pc->pieceh))
	{
		x = 0;
		while (x < (pc->piecew))
		{
			if (pc->pcmap[y][x] == '*' && pc->offset_top == -1)
			{
				pc->offset_top = top;
				x++;
			}
			else
				x++;
		}
		y++;
		top++;
	}
}

void		get_corners(t_map *map, t_piece *pc)
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	while (y < pc->pieceh)
	{
		while (x < pc->piecew)
		{
			if (pc->pcmap[y][x] == '*' && pc->topleftset == 0)
			{
				pc->toplefty = y;
				pc->topleftX = x;
				pc->topleftset = 1;
			}
			else if (pc->pcmap[y][x] == '*')
			{
				pc->bottomrighty = y;
				pc->bottomrightx = x;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

int			definepiece(t_map *map, t_piece *pc)
{
	pc->horizontal = 0;
	pc->vertical = 0;
	pc->diagonal = 0;
	get_corners(map, pc);
	if (pc->bottomrightx - pc->topleftX > pc->bottomrighty - pc->toplefty)
		pc->horizontal = 1;
	else if (pc->bottomrightx - pc->topleftX < pc->bottomrighty - pc->toplefty)
		pc->vertical = 1;
	else if (map->round % 2 == 0)
		pc->horizontal = 1;
	else
		pc->vertical = 1;
	offset_top(pc);
	offset_left(pc);
	return (1);
}
