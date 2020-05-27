/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fizzylogic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:42:16 by tlouekar          #+#    #+#             */
/*   Updated: 2020/05/27 19:33:44 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int     entercoordinates(t_map *map, t_piece *pc)
{
    if (map->founddiagonal != 1)
    {
        map->tempX = map->targetX;
        map->tempY = map->targetY;
    }
    if (map->strategy == 1) // Initial strategy builds towards the opponent
    {
        map->tempX = map->osX;
        map->tempY = map->osY;
    }
    else if (map->strategy == 2)
    {
        map->tempX = map->targetX;
        map->tempY = map->targetY;
        /*
        ping(map, pc, pc->placeX, pc->placeY, map->psymbol, 5);
        if(map->ping->count > 12)
        {
            map->tempX = map->lastpcopX;
            map->tempY = map->lastpcopY;
        }
        else {
            map->tempX = map->lastpcX;
            map->tempY = map->lastpcY;
        }
        */
    }
    return (1);
}

int     branchstrategy(t_map *map, t_piece *pc)
{
    if (map->psX <= map->osX && (map->dirh == 0 || map->dirv == 0))
    {
        if (map->psY <= map->osY)
        {
            /*
            map->lbranchX = map->mapW - 1;
            map->lbranchY = map->psY;
            map->rbranchX = map->psX;
            map->rbranchY = map->mapH - 1;
            */
            map->dirh = 2; // 4?
            map->dirv = 7; // 10?
            map->strategy = 20; 
        }
        else
        {
            /*
            map->lbranchX = map->psX;
            map->lbranchY = 0;
            map->rbranchX = map->mapW - 1;
            map->rbranchY = map->psY;
            */
            map->dirh = 3;
            map->dirv = 12;
            map->strategy = 10;
        }
    }
    else if (map->dirh == 0 || map->dirv == 0)
    {
        if (map->psY >= map->osY)
        {
            /*
            map->lbranchX = 0;
            map->lbranchY = map->psY;
            map->rbranchX = map->psX;
            map->rbranchY = 0;
            */
            map->dirh = 8;
            map->dirv = 1;
            map->strategy = 40;
        }
        else
        {
            /*
            map->rbranchX = 0;
            map->rbranchY = map->psY;
            map->lbranchX = map->psX;
            map->lbranchY = map->mapH - 1;
            */
            map->dirh = 9;
            map->dirv = 6;
            map->strategy = 30;
        }
    }
    if (map->mapW < 40)
        map->dirh = map->dirv;
    /*
    ping(map, pc, map->lastpcX, map->lastpcY, map->osymbol, 5);
    if (map->ping->count > 1 && map->strategy % 10 == 0)
    {
        if (pc->horizontal == 1)
            if (map->strategy ==  40 && map->strategy == 20)
                map->dirh--;
            else
                map->dirh++;
        else
            if (map->strategy ==  40 && map->strategy == 20)
                map->dirv++;
            else
                map->dirv++;
        //map->strategy += 2;
    }
    */
    if (pc->horizontal == 1)
        direction(map, pc, map->dirh);
    else
        direction(map, pc, map->dirv);
    ping(map, pc, map->targetX, map->targetY, map->psymbol, 5);
    if (map->ping->count > 8 && map->strategy % 10 == 0)
    {
        if (pc->horizontal == 1)
            map->dirh = map->dirv;
        else
            map->dirv = map->dirh;
        //map->strategy++;
    }
    /*
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
    */
    return (0);
}

int     latestrategy(t_map *map, t_piece *pc)
{
    ping(map, pc, map->targetX, map->targetY, map->psymbol, 6);
    if (map->round % 200 == 0)
        map->raytrace = 0;
    if (map->round < 120 && map->mapW > 80) // This magic number seems to work only on bigger maps
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
        if (map->raytrace == 1 && map->mapW > 50)
        {
            map->targetX = map->rttargetX;
            map->targetY = map->rttargetY;
        }
        //map->targetX = 0;
        //map->targetY = 0;
        //map->targetX = map->osX;
        //map->targetY = map->osY;
    }
    /*
    ping(map, pc, map->tempX, map->tempY, map->psymbol, 8);
    if (map->ping->count > 15)
    {
        if (map->raytrace == 1)
        {
            map->targetX = map->rttargetX;
            map->targetY = map->rttargetY;
        }
        else 
        {
            map->targetX = map->lastpcopX;
            map->targetY = map->lastpcopY;
        }
        ft_putstr_fd("Disregarded as too full position.\n", 2);
    }
    */  
    ping(map, pc, map->rttargetX, map->rttargetY, map->psymbol, 4);
    if (map->ping->count > 5)
        map->raytrace = 2;
    map->strategy = 2;
    return (0);
}

int     checkdiagonals(t_map *map, t_piece *pc)
{
    int     x;
    int     y;
    int     i;

    x = 5;
    y = 5;
    i = 0;
    if (pc->diagonal == 0)
        return (0);
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
                    //ft_putstr_fd(map->map[y], 2);
                    //ft_putstr_fd("\n", 2);
                    //ft_putstr_fd(map->map[y + 1], 2);
                    if (drawcircle(map, pc, 0, 2) == 1)
                    {
                        /*
                        ft_putstr_fd("PLACED DIAGONAL AT: ", 2);
                        ft_putnbr_fd(x, 2);
                        ft_putstr_fd(", ", 2);
                        ft_putnbr_fd(y, 2);
                        ft_putstr_fd("\n\n\n\n\n\n\n\n\n\n", 2);
                        */
                        map->founddiagonal = 1;
                        return (1);
                    }
                }
            }
            else if (map->map[y][x] == map->osymbol && map->map[y][x + 1] == '.')
            {
                if (map->map[y + 1][x] == '.' && map->map[y + 1][x + 1] == map->osymbol)
                {
                    map->tempY = y;
                    map->tempX = x;
                    //ft_putstr_fd(map->map[y], 2);
                    //ft_putstr_fd("\n", 2);
                    //ft_putstr_fd(map->map[y + 1], 2);
                    if (drawcircle(map, pc, 0, 3) == 1)
                    {
                        /*
                        ft_putstr_fd("PLACED DIAGONAL AT: ", 2);
                        ft_putnbr_fd(x, 2);
                        ft_putstr_fd(", ", 2);
                        ft_putnbr_fd(y, 2);
                        ft_putstr_fd("\n", 2);
                        */
                        map->founddiagonal = 1;
                        return (1);
                    }
                }
            }
            x++;
        }
        y++;
        x = 5;
    }
    return (0);
}

int     updatestrategy(t_map *map, t_piece *pc)
{
    int     turns;

    turns = 15; // Best guess so far 15: 43/50 and 33/50 against Carli
    if (map->mapW > 30)
        turns = 40; // Best guess so far 40: 43/50 and 26/50 against Carli
    if (map->mapW > 90)
        turns = 150; // Best guess so far 200
    if (map->round < ((map->mapH * map->mapW) / (10 * turns))) // Smaller = Initial state stays longer
        map->strategy = 1;
    else if (map->round > ((map->mapH * map->mapW) / turns)) // Bigger = late comes earlier
        latestrategy(map, pc);
    else
        branchstrategy(map, pc);
    if (checkdiagonals(map, pc) == 1)
        map->founddiagonal = 1;
    return (0);
}

int     fizzylogic(t_map *map, t_piece *pc)
{
    updatestrategy(map, pc);
    entercoordinates(map, pc);
    return (0);
}