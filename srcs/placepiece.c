/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placepiece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:39:54 by tlouekar          #+#    #+#             */
/*   Updated: 2020/06/09 15:04:41 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int     isplacevalid(t_map *map, t_piece *pc, int x, int y)
{
    int pY;
    int pX;
    int mY;
    int mX;
    int i;

    pY = 0;
    pX = 0;
    mY = y;
    mX = x;
    i = 0;
    
    while (pY < pc->pieceH)
    {
        while (pX < pc->pieceW)
        {
            if (mY + pY >= map->mapH || mX + pX >= map->mapW || mY + (pY + pc->offset_top) < 0 || mX + (pX + pc->offset_left) < 0)
            {
                pc->isvaliddot = 0;
                pc->isvalidx = 0;
                return (0);
            }
            if (pc->pcmap[pY][pX] == '*')
            {
                if (map->map[mY + pY][mX + (pX - pc->offset_left)] == '.')
                {
                    pX++;
                    pc->isvaliddot = 1;
                }
                else if (map->map[mY + pY][mX + (pX - pc->offset_left)] == map->psymbol)
                {
                    pX++;
                    pc->isvalidx++;
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
        pX = 0;
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
    pc->placeY = mY;
    pc->placeX = mX - pc->offset_left;
    map->lastpcY = mY;
    map->lastpcX = mX;
    return (1);
}

int drawcircle(t_map *map, t_piece *pc, int tries, int radius)
{
    int x = radius;
    int y = 0;
    int err = 0;
 
    while (x >= y)
    {
        if (isplacevalid(map, pc, map->tempX + x, map->tempY + y))
            return (1);
        else if (isplacevalid(map, pc, map->tempX + y, map->tempY + x))
            return (1);
        else if(isplacevalid(map, pc, map->tempX - y, map->tempY + x))
            return (1);
        else if(isplacevalid(map, pc, map->tempX - x, map->tempY + y))
            return (1);
        else if(isplacevalid(map, pc, map->tempX - x, map->tempY - y))
            return (1);
        else if(isplacevalid(map, pc, map->tempX - y, map->tempY - x))
            return (1);
        else if(isplacevalid(map, pc, map->tempX + y, map->tempY - x))
            return (1);
        else if(isplacevalid(map, pc, map->tempX + x, map->tempY - y))
            return (1);
        else
        {
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
    }
    if (map->founddiagonal != 1)
    {
        map->radius++;
    }
    /*
    if (map->radius > 100)
    {
        map->radius = 2;
        map->tempX = map->psX;
        map->tempY = map->psY;
    }*/
    if (tries % 200 == 0)
    {
        map->tempX++;
    }
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

    y = -50;
    x = -50;
    i = 0;
    tries++;
    if (tries > 2000)
    {
        while (y < map->mapH)
        {
            x = -50;
            while (x < map->mapW)
            {
                if (isplacevalid(map, pc, x, y) == 1)
                    return (1);
                x++;
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