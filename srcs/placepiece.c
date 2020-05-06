/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placepiece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:39:54 by tlouekar          #+#    #+#             */
/*   Updated: 2020/05/06 21:29:03 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int     getbetterplace(t_map *map, t_piece *pc, int tries)
{
    int offset;

    if (tries % 2 == 0)
        offset = tries / (map->mapH * 10);
    else
        offset = -tries / (map->mapH * 10);
    if (offset > 15 || offset < -15)
        offset = offset / 4;
    tries++;
    if (tries % 4000 ==  0)
    {
        if (pc->horizontal == 1)
            pc->horizontal = 0;
        else
            pc->horizontal = 1;
        if (map->strategy == 1 || map->strategy == 3)
        {
            if (pc->horizontal == 1)
            {
                map->tempX = map->rbranchX;
                map->tempY = map->rbranchY;
            }
            else
            {
                map->tempX = map->lbranchX;
                map->tempY = map->lbranchY;
            }
        }
        else
        {
            if (pc->horizontal == 1)
            {
                map->tempX = map->lbranchX;
                map->tempY = map->lbranchY;
            }
            else
            {
                map->tempX = map->rbranchX;
                map->tempY = map->rbranchY;
            }
        }
        ft_putstr_fd("X: ", 2);
        ft_putnbr_fd(map->tempX, 2);
        ft_putstr_fd("\nY: ", 2);
        ft_putnbr_fd(map->tempY, 2);
        ft_putstr_fd("\nOffset: ", 2);
        ft_putnbr_fd(offset, 2);
        ft_putstr_fd("\n\n", 2);
    }
    if (pc->horizontal == 1 && (map->strategy == 1 || map->strategy == 2))
    {
        map->tempX--;
        map->tempY += offset;
        if (map->tempX < 0)
            map->tempX = 0;
    }
    if (pc->horizontal == 1 && (map->strategy == 3 || map->strategy == 4))
    {
        map->tempX++;
        map->tempY += offset;
        if (map->tempX > map->mapW)
        map->tempX = map->mapW - 1;
    }
    if (pc->vertical == 1 && (map->strategy == 1 || map->strategy == 4))
    {
        map->tempY++;
        map->tempX += offset;
        if (map->tempY > map->mapH)
        map->tempY = map->mapH - 1;
    }
    if (pc->vertical == 1 && (map->strategy == 2 || map->strategy == 3))
    {
        map->tempY--;
        map->tempX += offset;
        if (map->tempY < 0)
        map->tempY = 0;
    }
    /*
    if (map->tempX < 0)
        map->tempX = 0;
    if (map->tempY < 0)
        map->tempY = 0;
    if (map->tempX > map->mapW)
        map->tempX = map->mapW - 1;
    if (map->tempY > map->mapH)
        map->tempY = map->mapH - 1;
    */
    return (tries);
}

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
    return (1);
}

int recursion (t_map *map, t_piece *pc, int tries)
{

    //ft_putstr_fd("Placing a piece...........\n", 2);
    if (tries > 20000)
    {
        ft_putstr_fd("TRIES OVERLOAD!!!!\n\n\n\n\n\n\n\n", 2);
        return (0);
    }
    if (isplacevalid(map, pc, map->tempX, map->tempY) == 0)
    {
        tries = getbetterplace(map, pc, tries);
    }
    else
        return (1);
    if (recursion(map, pc, tries) == 0)
        return (0);
    return (1);
}

int     placepiece(t_map *map, t_piece *pc, int strategy)
{
    if (map->strategy == 1 || map->strategy == 3)
    {
        if (pc->horizontal == 1)
        {
            map->tempX = map->rbranchX;
            map->tempY = map->rbranchY;
        }
        else
        {
            map->tempX = map->lbranchX;
            map->tempY = map->lbranchY;
        }
    }
    else
    {
        if (pc->horizontal == 1)
        {
            map->tempX = map->lbranchX;
            map->tempY = map->lbranchY;
        }
        else
        {
            map->tempX = map->rbranchX;
            map->tempY = map->rbranchY;
        }
    }
    
    if (recursion(map, pc, 1) == 1)
        return (1);
    return (0);
}