/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fizzylogic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:42:16 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/14 11:17:57 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		entercoordinates(t_map *map)
{
	if (map->strategy == STRATEGY_INITIAL)
	{
		map->tempx = map->osx;
		map->tempy = map->osy;
	}
	else
	{
		map->tempx = map->targetx;
		map->tempy = map->targety;
	}
	return (1);
}

/*
** Branchstrategy grows two branches from the
** pieces and tries to contain the opponent
*/

int		branchstrategy(t_map *map, t_piece *pc)
{
	if (map->dirh == 0 || map->dirv == 0)
		strategy_to_dir(map);
	if (map->w < MAP_M)
		map->dirh = map->dirv;
	if (pc->horizontal == 1)
		direction(map, map->dirh);
	else
		direction(map, map->dirv);
	map->radius = 2;
	ping(map, map->targetx, map->targety, map->psymbol);
	if (map->ping->count > 2 && map->strategy % 10 == 0)
	{
		if (pc->horizontal == 1)
			map->dirh = map->dirv;
		else
			map->dirv = map->dirh;
	}
	return (0);
}

/*
** Latestrategy uses heatmap to annihilate the
** opponent.
*/

int		latestrategy(t_map *map)
{
	if (map->w > MAP_M)
		map->threshold = 30;
	else if (map->w > MAP_L)
		map->threshold = 100;
	else
		map->threshold = 15;
	map->targetx = map->lastpcopx;
	map->targety = map->lastpcopy;
	map->strategy = STRATEGY_LATE;
	return (0);
}

/*
** Updatestrategy, well, updates strategy. Different settings
** are used for different map sizes and
** the beginning of the late strategy.
*/

int		updatestrategy(t_map *map, t_piece *pc)
{
	int		turns;

	turns = TURNS_THRESHOLD_SMALL;
	if (map->w > MAP_M)
		turns = TURNS_THRESHOLD_MEDIUM;
	if (map->w > MAP_L)
		turns = TURNS_THRESHOLD_LARGE;
	if (map->round < ((map->h * map->w) / (TURNS_MULTIPLIER * turns)))
		map->strategy = 1;
	else if (map->round > ((map->h * map->w) / turns))
		latestrategy(map);
	else
		branchstrategy(map, pc);
	return (0);
}

/*
** Fizzylogic doesn't really do much anymore. It runs
** the algorithm part by part.
*/

int		fizzylogic(t_map *map, t_piece *pc)
{
	updatestrategy(map, pc);
	entercoordinates(map);
	heatmap(map);
	return (0);
}
