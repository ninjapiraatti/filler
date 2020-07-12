/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fizzylogic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:42:16 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/12 14:46:06 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int     entercoordinates(t_map *map, t_piece *pc)
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

/* Branchstrategy grows two branches from the pieces and tries to contain the opponent */

int     branchstrategy(t_map *map, t_piece *pc)
{
    if (map->psx <= map->osx && (map->dirh == 0 || map->dirv == 0))
    {
        if (map->psy <= map->osy)
        {
            map->dirh = 2;
            map->dirv = 7;
            map->strategy = STRATEGY_TO_SE; 
        }
        else
        {
            map->dirh = 3;
            map->dirv = 12;
            map->strategy = STRATEGY_TO_NE;
        }
    }
    else if (map->dirh == 0 || map->dirv == 0)
    {
        if (map->psy >= map->osy)
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

/* Latestrategy switches between building close to the opponent and using the raytrace function to
close gaps on the map thus containing the opponent into smaller sections */

int     latestrategy(t_map *map, t_piece *pc)
{
    if (map->round % 100 == 0)
        map->raytrace = 0;
	if (map->round < 2000)
    {	
		map->threshold = 100;
        map->targetx = map->lastpcopx;
        map->targety = map->lastpcopy;
		map->strategy = STRATEGY_LATE;
		return (0);
    }
    else
    {
		map->threshold = 1;
        if (map->raytrace == 0)
            raytrace(map, pc);
        map->targetx = map->lastpcopx;
        map->targety = map->lastpcopy;
        if (map->raytrace == 1 && map->w > 30)
        {
            map->targetx = map->rttargetx;
        	map->targety = map->rttargety;
        }
    }
	map->radius = 2;
    ping(map, map->rttargetx, map->rttargety, map->psymbol);
    if (map->ping->count > 2)
        map->raytrace = 2;
    map->strategy = STRATEGY_LATE;
    return (0);
}

/* Updatestrategy, well, updates strategy. Different settings are used for different map sizes and
the beginning of the late strategy. */

int     updatestrategy(t_map *map, t_piece *pc)
{
    int     turns;

    turns = TURNS_THRESHOLD_SMALL;
    if (map->w > 30)
        turns = TURNS_THRESHOLD_MEDIUM;
    if (map->w > 90)
        turns = TURNS_THRESHOLD_LARGE; // Best guess so far 200
    if (map->round < ((map->h * map->w) / (TURNS_MULTIPLIER * turns)))
        map->strategy = 1;
    else if (map->round > ((map->h * map->w) / turns))
        latestrategy(map, pc);
    else
        branchstrategy(map, pc);
    return (0);
}

/* Fizzylogic doesn't really do much anymore */

int     fizzylogic(t_map *map, t_piece *pc)
{
    updatestrategy(map, pc);
    entercoordinates(map, pc);
	heatmap(map);
    return (0);
}