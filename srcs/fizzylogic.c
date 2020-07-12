/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fizzylogic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:42:16 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/12 18:14:49 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		entercoordinates(t_map *map, t_piece *pc)
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
	strategy_to_dir(map);
	if (map->w < 40)
		map->dirh = map->dirv;
	if (pc->horizontal == 1)
		direction(map, pc, map->dirh);
	else
		direction(map, pc, map->dirv);
	map->radius = 2;
	ping(map, map->targetx, map->targety, map->psymbol);
	if (map->ping->count > 2 && map->strategy % 10 == 0)
	{
		if (pc->horizontal == 1)
			map->dirh = map->dirv;
		else
			map->dirv = map->dirh;
		ft_putstr_fd("END OF BRANCH!", 2);
	}
	return (0);
}

/*
** Latestrategy switches between building close to the opponent
** and using the raytrace function to
** close gaps on the map thus containing the opponent into smaller sections
*/

int		latestrategy(t_map *map, t_piece *pc)
{
	map->threshold = 100;
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
	if (map->w > 30)
		turns = TURNS_THRESHOLD_MEDIUM;
	if (map->w > 90)
		turns = TURNS_THRESHOLD_LARGE;
	if (map->round < ((map->h * map->w) / (TURNS_MULTIPLIER * turns)))
		map->strategy = 1;
	else if (map->round > ((map->h * map->w) / turns))
		latestrategy(map, pc);
	else
		branchstrategy(map, pc);
	return (0);
}

/*
** Fizzylogic doesn't really do much anymore
*/

int		fizzylogic(t_map *map, t_piece *pc)
{
	updatestrategy(map, pc);
	entercoordinates(map, pc);
	heatmap(map);
	return (0);
}
