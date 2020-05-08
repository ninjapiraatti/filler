/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fizzylogic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:42:16 by tlouekar          #+#    #+#             */
/*   Updated: 2020/05/08 09:36:49 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int     entercoordinates(t_map *map, t_piece *pc)
{
    if (map->strategy == 10 || map->strategy == 30)
    {
        if (pc->horizontal == 1)
        {
            map->tempX = map->rbranchX;
            map->tempY = map->rbranchY;
        }
        else if (pc->vertical == 1)
        {
            map->tempX = map->lbranchX;
            map->tempY = map->lbranchY;
        }
    }
    else if (map->strategy == 20 || map->strategy == 40)
    {
        if (pc->horizontal == 1)
        {
            map->tempX = map->lbranchX;
            map->tempY = map->lbranchY;
        }
        else if (pc->vertical == 1)
        {
            map->tempX = map->rbranchX;
            map->tempY = map->rbranchY;
        }
    }
    else if (map->strategy == 1)
    {
        map->tempX = map->osX;
        map->tempY = map->osY;
    }
    else if (map->strategy == 2)
    {
        map->tempX = map->lastpcopX;
        map->tempY = map->lastpcopY;
    }
    return (1);
}

int     branchstrategy(t_map *map)
{
    if (map->psX <= map->osX)
    {
        if (map->psY <= map->osY)
        {
            map->lbranchX = map->mapW - 1;
            map->lbranchY = map->psY;
            map->rbranchX = map->psX;
            map->rbranchY = map->mapH - 1;
            map->strategy = 20;
        }
        else
        {
            map->lbranchX = map->psX;
            map->lbranchY = 0;
            map->rbranchX = map->mapW - 1;
            map->rbranchY = map->psY;
            map->strategy = 10;
        }
    }
    else
    {
        if (map->psY >= map->osY)
        {
            map->lbranchX = 0;
            map->lbranchY = map->psY;
            map->rbranchX = map->psX;
            map->rbranchY = 0;
            map->strategy = 40;
        }
        else
        {
            map->rbranchX = 0;
            map->rbranchY = map->psY;
            map->lbranchX = map->psX;
            map->lbranchY = map->mapH - 1;
            map->strategy = 30;
        }
    }
    if (map->map[map->lbranchY][map->lbranchX] == map->psymbol)
    {
        map->lbranchX = map->rbranchX;
        map->lbranchY = map->rbranchY;
        map->lwallreached = 1;
    }
    else if(map->map[map->lbranchY][map->lbranchX] == map->osymbol)
    {
        map->lwallreached = 2;
    }
    if (map->map[map->rbranchY][map->rbranchX] == map->psymbol)
    {
        map->rbranchX = map->lbranchX;
        map->rbranchY = map->lbranchY;
        map->rwallreached = 1;
    }
    else if(map->map[map->rbranchY][map->rbranchX] == map->osymbol)
    {
        map->rwallreached = 2;
    } 
    return (0);
}

int     latestrategy(t_map *map)
{
    if (map->lwallreached == 1 && map->rwallreached == 1)
    {
        map->tempX = map->psX;
        map->tempY = map->psY;
    }
    else
    {
        map->tempX = map->lastpcopX;
        map->tempY = map->lastpcopY;
    }
    map->strategy = 2;
    return (0);
}

int     checkdiagonals(t_map *map, t_piece *pc)
{
    return (0);
}

int     updatestrategy(t_map *map, t_piece *pc)
{
    ft_putnbr_fd(map->round, 2);
    if (map->round < (map->mapH + map->mapW) / 1000) // 20 for mid. Smaller = Initial state stays longer
        map->strategy = 1;
    else if (map->round > ((map->mapH * map->mapW) / 80)) // (0 for small), 40 for mid, (80 for large). Smaller = late comes earlier
        latestrategy(map);
    else
        branchstrategy(map);
    checkdiagonals(map, pc);
    return (0);
}

int     fizzylogic(t_map *map, t_piece *pc)
{
    updatestrategy(map, pc);
    entercoordinates(map, pc);
    return (0);
}