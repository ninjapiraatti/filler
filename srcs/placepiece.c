/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placepiece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:39:54 by tlouekar          #+#    #+#             */
/*   Updated: 2020/06/29 20:22:49 by tlouekar         ###   ########.fr       */
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
    if (map->area->rows > 1 && map->round < 600) 
    {
        j = 0;
        while (j < map->area->rows)
        {
            if (map->area->empties[j][0] == x + pX && map->area->empties[j][1] == y + pY)
            {
                /*
                ft_putstr_fd("\nX and Y: ", 2);
                ft_putnbr_fd(x, 2);
                ft_putstr_fd(", ", 2);
                ft_putnbr_fd(y, 2);
                ft_putstr_fd(" Forbidden X and Y: ", 2);
                ft_putnbr_fd(map->area->empties[j][0], 2);
                ft_putstr_fd(", ", 2);
                ft_putnbr_fd(map->area->empties[j][1], 2);
                ft_putstr_fd("\nAvoided closed area", 2);
                */
                return (0);
            }
            j++;
        }
        /*
        ft_putstr_fd("\nX and Y: ", 2);
        ft_putnbr_fd(x, 2);
        ft_putstr_fd(", ", 2);
        ft_putnbr_fd(y, 2);
        ft_putstr_fd(" Forbidden X and Y: ", 2);
        ft_putnbr_fd(map->area->empties[j][0], 2);
        ft_putstr_fd(", ", 2);
        ft_putnbr_fd(map->area->empties[j][1], 2);
        */
    }
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
    /*
    ft_putstr_fd("Offset: ", 2);
    ft_putnbr_fd(pc->offset_top, 2);
    ft_putstr_fd("\nPlace X, Y: ", 2);
    ft_putnbr_fd(pc->placeX, 2);
    ft_putstr_fd(", ", 2);
    ft_putnbr_fd(pc->placeY, 2);
    ft_putstr_fd("\n", 2);
    while (i < pc->pieceH)
    {
        ft_putstr_fd(pc->pcmap[i], 2);
        ft_putstr_fd("\n", 2);
        i++;
    }*/
	if (pc->bestvaluetemp < pc->bestvalue && pc->bestvaluetemp > 0)
	{
		/*
		ft_putstr_fd("\nBestX: ", 2);
		ft_putnbr_fd(pc->bestvalueX, 2);
		ft_putstr_fd("\nBestY: ", 2);
		ft_putnbr_fd(pc->bestvalueY, 2);
		*/
		pc->bestvalue = pc->bestvaluetemp;
		pc->bestvalueX = x;
		pc->bestvalueY = y;
		//ft_putnbr_fd(pc->bestvalueX, 2);
		//ft_putstr_fd("\n", 2);
	}
    pc->placeY = y;
    pc->placeX = x;
    map->lastpcY = y;
    map->lastpcX = x;
    return (1);
}

int drawcircle(t_map *map, t_piece *pc, int tries, int radius)
{
    int x = radius;
    int y = 0;
    int err = 0;
 
    while (x >= y)
    {
		//ft_putstr_fd("Round of drawcircle! ", 2);
		if (map->validplaces > 5)
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
        map->state = 3;
        while (y < map->mapH)
        {
            x = -80;
            while (x < map->mapW)
            {
                if (isplacevalid(map, pc, x, y) == 1)
                    return (1);
                x++;
                i++;
				/*
                ft_putnbr_fd(i, 2);
                ft_putstr_fd(": ", 2);
                ft_putnbr_fd(x, 2);
                ft_putstr_fd(", ", 2);
                ft_putnbr_fd(y, 2);
                ft_putstr_fd(" | ", 2);
				*/
            }
            y++;
        }
        return (0);
    }
    if (map->mapW > 50 && map->round < 300 && map->raytrace == 1 && crosscheck(map, pc) == 1)
       return (1);
    if (drawcircle(map, pc, tries, map->radius) == 1)
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
    if (map->round == 200)
        closedarea(map, pc, 90, 50, 50);
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