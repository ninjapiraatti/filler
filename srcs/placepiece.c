/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placepiece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:39:54 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/01 09:27:17 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int     isplacevalid(t_map *map, t_piece *pc, int x, int y)
{
    int pY;
    int pX;
    int pH;
    int pW;
    int i;
    int j;

    pY = pc->offset_top;
    pX = pc->offset_left;
    pW = pc->bottomrightX - pc->topleftX + 1;
    pH = pc->bottomrightY - pc->topleftY + 1; 
    i = 0;
    j = 0;
    pc->bestvaluetemp = 0;
	pc->isvalidx = 0;
    while (pY < pc->pieceH)
    {
        while (pX < pc->pieceW)
        {
            if (y + pY >= map->mapH || x + pW > map->mapW || (y + pY) < 0 || (x + pX) < 0)
            {
                pc->isvaliddot = 0;
                pc->isvalidx = 0;
                return (0);
            }
            if (pc->pcmap[pY][pX] == '*')
            {
                if (map->map[y + pY][x + pX] == '.')
                {
                    pc->isvaliddot = 1;
					pc->bestvaluetemp += map->heatmap[y + pY][x + pX];
                    pX++;
                }
                else if (map->map[y + pY][x + pX] == map->psymbol)
                {
                    pc->isvalidx++;
                    pX++;
                }
                else
                {
                    pc->isvaliddot = 0;
                    pc->isvalidx = 0;
                    return (0);
                }
            }
            else
                pX++;
        }
        pX = pc->offset_left;
        pY++;
    }
    if (pc->isvaliddot == 0 || pc->isvalidx == 0 || pc->isvalidx > 1)
    {
        pc->isvaliddot = 0;
        pc->isvalidx = 0;
        return (0);
    }
	if (pc->bestvaluetemp < pc->bestvalue && pc->bestvaluetemp > 0)
	{
		pc->bestvalue = pc->bestvaluetemp;
		pc->bestvalueX = x;
		pc->bestvalueY = y;
		pc->placeY = pc->bestvalueY;
    	pc->placeX = pc->bestvalueX;
	}
	else if (pc->bestvalue != 1000000)
	{
		pc->placeY = pc->bestvalueY;
    	pc->placeX = pc->bestvalueX;
	}
	else 
	{
		pc->placeY = y;
    	pc->placeX = x;
	}
    map->lastpcY = y;
    map->lastpcX = x;
    return (1);
}

int drawcircle(t_map *map, t_piece *pc, int tries, int radius, int threshold)
{
    int x = radius;
    int y = 0;
    int err = 0;
 
    while (x >= y)
    {
		if (map->validplaces > threshold)
			return (1);
        if (isplacevalid(map, pc, map->tempX + x, map->tempY + y))
            map->validplaces++;
        if (isplacevalid(map, pc, map->tempX + y, map->tempY + x))
            map->validplaces++;
        if (isplacevalid(map, pc, map->tempX - y, map->tempY + x))
            map->validplaces++;
        if (isplacevalid(map, pc, map->tempX - x, map->tempY + y))
            map->validplaces++;
        if (isplacevalid(map, pc, map->tempX - x, map->tempY - y))
            map->validplaces++;
        if (isplacevalid(map, pc, map->tempX - y, map->tempY - x))
            map->validplaces++;
        if (isplacevalid(map, pc, map->tempX + y, map->tempY - x))
            map->validplaces++;
        if (isplacevalid(map, pc, map->tempX + x, map->tempY - y))
            map->validplaces++;
		if (err <= 0)
		{
			y += 1;
			err += 2*y + 1;
		}
	
		if (err > 0)
		{
			x -= 1;
			err -= 2*x + 1;
		}   
    }
    map->radius++;
    if (tries % TRIES_INTERVAL == 0)
        map->tempX++;
    return (0);
}

int crosscheck(t_map *map, t_piece *pc)
{
    int     x;
    int     y;
    
    y = -100;
    while (y < 100)
    {
        x = -1;
        while (x < 1)
        {
            if (isplacevalid(map, pc, map->targetX, map->targetY + y))
                return (1);
            x++;
        }
        y++;
    }
    x = -100;
    while (y < 1)
    {
        y = -1;
        while (y < 1)
        {
            if (isplacevalid(map, pc, map->targetX + x, map->targetY))
                return (1);
            y++;
        }
        x++;
    }
    return (0);
}

int recursion (t_map *map, t_piece *pc, int tries)
{
    int     x;
    int     y;
    int     i;

    y = -80;
    x = -80;
    i = 0;
    tries++;
    if (tries > 2000)
    {
        while (y < map->mapH)
        {
            x = -80;
            while (x < map->mapW)
            {
                if (isplacevalid(map, pc, x, y) == 1)
                    return (1);
                x++;
                i++;
            }
            y++;
        }
        return (0);
    }
    if (map->mapW > 50 && map->round < 300 && map->raytrace == 1 && crosscheck(map, pc) == 1)
       return (1);
    if (drawcircle(map, pc, tries, map->radius, map->threshold) == 1)
        return (1);
    if (recursion(map, pc, tries) == 0)
    {
        return (0);
    }
    return (1);
}

int     placepiece(t_map *map, t_piece *pc, int strategy)
{
    int     i;
    i = 0;
    map->radius = 0;
	map->validplaces = 0;
    if (recursion(map, pc, 2) == 1)
        return (1);
    ft_putstr_fd("Failed to place a piece:\n", 2);
    while (i < pc->pieceH)
    {
        ft_putstr_fd(pc->pcmap[i], 2);
        ft_putstr_fd("\n", 2);
        i++;
    }
    return (0);
}