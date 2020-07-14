/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_piece.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 09:20:02 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/14 11:15:57 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

/*
** offset_left gets the left offset
*/

void		offset_left(t_piece *pc)
{
	int		left;
	int		x;
	int		y;

	left = 0;
	x = 0;
	y = 0;
	while (x < (pc->w))
	{
		y = 0;
		while (y < (pc->h))
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

/*
** offset_top gets the top offset
*/

void		offset_top(t_piece *pc)
{
	int		top;
	int		x;
	int		y;

	top = 0;
	x = 0;
	y = 0;
	while (y < (pc->h))
	{
		x = 0;
		while (x < (pc->w))
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

/*
** get_corners searches for the top left and bottom right
** corners that will define the pieces shape.
*/

void		get_corners(t_piece *pc)
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	while (y < pc->h)
	{
		while (x < pc->w)
		{
			if (pc->pcmap[y][x] == '*' && pc->topleftset == 0)
			{
				pc->toplefty = y;
				pc->topleftx = x;
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

/*
** define_piece gets and writes the dimensions and shape of the piece.
*/

int			define_piece(t_map *map, t_piece *pc)
{
	pc->horizontal = 0;
	pc->vertical = 0;
	pc->x = 0;
	pc->y = 0;
	get_corners(pc);
	if (pc->bottomrightx - pc->topleftx > pc->bottomrighty - pc->toplefty)
		pc->horizontal = 1;
	else if (pc->bottomrightx - pc->topleftx < pc->bottomrighty - pc->toplefty)
		pc->vertical = 1;
	else if (map->round % 2 == 0)
		pc->horizontal = 1;
	else
		pc->vertical = 1;
	offset_top(pc);
	offset_left(pc);
	return (1);
}
