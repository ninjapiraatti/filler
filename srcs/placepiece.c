/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placepiece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:39:54 by tlouekar          #+#    #+#             */
/*   Updated: 2020/05/07 14:42:02 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int     isplacevalid(t_map *map, t_piece *pc, int x, int y)
{
    int pY;
    int pX;
    int mY;
    int mX;

    pY = 0;
    pX = 0;
    mY = y;
    mX = x;
    
    while (pY < pc->pieceH)
    {
        while (pX < pc->pieceW)
        {
            if (mY + pY >= map->mapH || mX + pX >= map->mapW || mY + pY < 0 || mX + pX < 0)
            {
                pc->isvaliddot = 0;
                pc->isvalidx = 0;
                return (0);
            }
            if (pc->pcmap[pY][pX] == '*')
            {
                if (map->map[mY + pY][mX + pX] == '.')
                {
                    pX++;
                    pc->isvaliddot = 1;
                }
                else if (map->map[mY + pY][mX + pX] == map->psymbol)
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
    pc->placeY = mY;
    pc->placeX = mX;
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
    map->radius++;
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
        map->tempY++;
    }
    return (0);
}

int recursion (t_map *map, t_piece *pc, int tries)
{
    tries++;
    if (tries > 2000)
    {
        ft_putstr_fd("TRIES OVERLOAD!!!!\n\n\n\n\n\n\n\n", 2);
        return (0);
    }
    /*
    if (isplacevalid(map, pc, map->tempX, map->tempY) == 0)
    {
        //tries = seekplace(map, pc, tries, map->radius);
    }
    */
    if (drawcircle(map, pc, tries, map->radius) == 1)
        return (1);
    if (recursion(map, pc, tries) == 0)
        return (0);
    return (1);
}

int     placepiece(t_map *map, t_piece *pc, int strategy)
{
    map->radius = 0;
    if (recursion(map, pc, 2) == 1)
        return (1);
    return (0);
}