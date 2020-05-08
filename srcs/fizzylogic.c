/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fizzylogic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:42:16 by tlouekar          #+#    #+#             */
/*   Updated: 2020/05/08 12:14:35 by tlouekar         ###   ########.fr       */
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
    else
        return (0);
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
    int     x;
    int     y;

    x = 5;
    y = 5;
    while (y < (map->mapH - 5))
    {
        while (x < (map->mapW - 5))
        {
            if(map->map[y][x] == '.' && map->map[y][x + 1] == map->osymbol)
            {
                if (map->map[y + 1][x] == map->osymbol && map->map[y + 1][x + 1] == '.')
                {
                    map->tempY = y;
                    map->tempX = x;
                    map->strategy = 100;
                    /*
                    ft_putstr_fd("FOUND DIAGONAL\n", 2);
                    ft_putstr_fd(map->map[y], 2);
                    ft_putstr_fd("\n", 2);
                    ft_putstr_fd(map->map[y + 1], 2);
                    */
                }
            }
            else if (map->map[y][x] == map->osymbol && map->map[y][x + 1] == '.')
            {
                if (map->map[y + 1][x] == '.' && map->map[y + 1][x + 1] == map->osymbol)
                {
                    map->tempY = y;
                    map->tempX = x;
                    map->strategy = 100;
                    /*
                    ft_putstr_fd("FOUND DIAGONAL\n", 2);
                    ft_putstr_fd(map->map[y], 2);
                    ft_putstr_fd("\n", 2);
                    ft_putstr_fd(map->map[y + 1], 2);
                    */
                }
            }
            x++;
        }
        y++;
        x = 5;
    }
    return (0);
}

int     ping(t_map *map, t_piece *pc)
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
    //checkdiagonals(map, pc);
    return (0);
}

int     fizzylogic(t_map *map, t_piece *pc)
{
    updatestrategy(map, pc);
    entercoordinates(map, pc);
    return (0);
}