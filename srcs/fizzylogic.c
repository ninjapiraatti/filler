/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fizzylogic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:42:16 by tlouekar          #+#    #+#             */
/*   Updated: 2020/06/29 09:54:19 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int     entercoordinates(t_map *map, t_piece *pc)
{
    if (map->strategy == STRATEGY_INITIAL) // Initial strategy builds towards the opponent
    {
        map->tempX = map->osX;
        map->tempY = map->osY;
    }
    else
    {
        map->tempX = map->targetX;
        map->tempY = map->targetY;
    }
    return (1);
}

/* Branchstrategy grows two branches from the pieces and tries to contain the opponent */

int     branchstrategy(t_map *map, t_piece *pc)
{
    if (map->psX <= map->osX && (map->dirh == 0 || map->dirv == 0))
    {
        if (map->psY <= map->osY)
        {
            map->dirh = 2; // 4?
            map->dirv = 7; // 10?
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
        if (map->psY >= map->osY)
        {
            map->dirh = 8;
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
    if (map->mapW < 40)
        map->dirh = map->dirv;
    if (pc->horizontal == 1)
        direction(map, pc, map->dirh);
    else
        direction(map, pc, map->dirv);
    ping(map, pc, map->targetX, map->targetY, map->psymbol, 2);
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
    ping(map, pc, map->targetX, map->targetY, map->psymbol, 6);
    if (map->round % 90 == 0)
        map->raytrace = 0;
    if (map->round < 90 && map->mapW > 80)
    {
        if (map->raytrace == 0)
            raytrace(map, pc);
        map->targetX = map->rttargetX;
        map->targetY = map->rttargetY;
    }
    else
    {
        if (map->raytrace == 0)
            raytrace(map, pc);
        map->targetX = map->lastpcopX;
        map->targetY = map->lastpcopY;
        if (map->raytrace == 1 && map->mapW > 30)
        {
            map->targetX = map->rttargetX;
            map->targetY = map->rttargetY;
        }
    } 
    ping(map, pc, map->rttargetX, map->rttargetY, map->psymbol, 2);
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

    turns = TURNS_THRESHOLD_SMALL; // Best guess so far 15: 43/50 and 33/50 against Carli
    if (map->mapW > 30)
        turns = TURNS_THRESHOLD_MEDIUM; // Best guess so far 40: 43/50 and 26/50 against Carli
    if (map->mapW > 90)
        turns = TURNS_THRESHOLD_LARGE; // Best guess so far 200
    if (map->round < ((map->mapH * map->mapW) / (TURNS_MULTIPLIER * turns))) // Smaller = Initial state stays longer
        map->strategy = 1;
    else if (map->round > ((map->mapH * map->mapW) / turns)) // Bigger = late comes earlier
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
    return (0);
}