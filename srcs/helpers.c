/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 12:36:28 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/14 11:14:36 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

/*
** Ping and its buddy ping_circle takes coordinates
** from the map, the "needle" character and radius.
** Ping returns the number of occurrences of that
** character within the radius.
*/

void		ping_circle(t_map *map, int x, int y, char c)
{
	if (!((map->ping->y + y >= map->h - 1) || (map->ping->x + x >= map->w - 1)))
		if (map->map[map->ping->y + y][map->ping->x + x] == c)
			map->ping->count++;
	if (!((map->ping->y + x >= map->h - 1) || (map->ping->x + y >= map->w - 1)))
		if (map->map[map->ping->y + x][map->ping->x + y] == c)
			map->ping->count++;
	if (!((map->ping->y + x >= map->h - 1) || (map->ping->x - y < 0)))
		if (map->map[map->ping->y + x][map->ping->x - y] == c)
			map->ping->count++;
	if (!((map->ping->y + y >= map->h - 1) || (map->ping->x - x < 0)))
		if (map->map[map->ping->y + y][map->ping->x - x] == c)
			map->ping->count++;
	if (!((map->ping->y - y < 0) || (map->ping->x - x < 0)))
		if (map->map[map->ping->y - y][map->ping->x - x] == c)
			map->ping->count++;
	if (!((map->ping->y - x < 0) || (map->ping->x - y < 0)))
		if (map->map[map->ping->y - x][map->ping->x - y] == c)
			map->ping->count++;
	if (!((map->ping->y - x < 0) || (map->ping->x + y >= map->w - 1)))
		if (map->map[map->ping->y - x][map->ping->x + y] == c)
			map->ping->count++;
	if (!((map->ping->y - y < 0) || (map->ping->x + x >= map->w - 1)))
		if (map->map[map->ping->y - y][map->ping->x + x] == c)
			map->ping->count++;
}

t_ping		*ping(t_map *map, int pingx, int pingy, char c)
{
	int		x;
	int		y;
	int		err;

	x = map->radius;
	y = 0;
	err = 0;
	map->ping->count = 0;
	map->ping->x = pingx;
	map->ping->y = pingy;
	while (x >= y)
	{
		ping_circle(map, x, y, c);
		if (err <= 0)
		{
			y += 1;
			err += 2 * y + 1;
		}
		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}
	return (map->ping);
}

/*
** strategy_to_dir gets the player's starting position in
** relation to the opponent and adjusts the directions of
** the "tentacles" accordingly.
*/

void		strategy_to_dir(t_map *map)
{
	if (map->psx <= map->osx && map->psy <= map->osy)
	{
		map->dirh = 2;
		map->dirv = 7;
		map->strategy = STRATEGY_TO_SE;
	}
	else if (map->psx <= map->osx)
	{
		map->dirh = 3;
		map->dirv = 12;
		map->strategy = STRATEGY_TO_NE;
	}
	else if (map->psy >= map->osy && map->psy >= map->osy)
	{
		map->dirh = 9;
		map->dirv = 1;
		map->strategy = STRATEGY_TO_NW;
	}
	else
	{
		map->dirh = 9;
		map->dirv = 6;
		map->strategy = STRATEGY_TO_SW;
	}
}

/*
** Direction takes an integer as a direction (like "bogey at your six")
** and turns it into coordinate on the map
*/

int			direction(t_map *map, int dir)
{
	if (dir == 11 || dir == 12 || dir == 1)
	{
		map->targety = 0;
		if (dir == 1)
			map->targetx = (map->w / 4) * 3;
		else
			map->targetx = (map->w / 4) * (dir - 10);
	}
	else if (dir == 2 || dir == 3 || dir == 4)
	{
		map->targetx = map->w - 1;
		map->targety = (map->h / 4) * (dir - 1);
	}
	else if (dir == 5 || dir == 6 || dir == 7)
	{
		map->targety = map->h - 1;
		map->targetx = (map->w / 4) * (8 - dir);
	}
	else if (dir == 8 || dir == 9 || dir == 10)
	{
		map->targetx = 0;
		map->targety = (map->h / 4) * (11 - dir);
	}
	return (0);
}
