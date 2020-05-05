/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placepiece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:39:54 by tlouekar          #+#    #+#             */
/*   Updated: 2020/05/05 11:03:01 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int     isplacevalid(t_map *map, t_piece *pc, int x, int y)
{
    int pY;
    int pX;
    int pH;
    int pW;
    int mY;
    int mX;

    pY = 0;
    pX = 0;
    pH = pc->bottomrightY - pc->topleftY;
    pW = pc->bottomrightX - pc->topleftX;
    mY = map->psY - y;
    mX = map->psX - x;
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
                else if (map->map[mY + pY][mX + pX] == 'X')
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
    //ft_putstr_fd("Place is valid.\n", 2);
    //ft_putstr_fd(pc->pcmap[0], 2);
    //ft_putstr_fd(pc->pcmap[1], 2);
    return (1);
}

int recursion (t_map *map, t_piece *pc, int x, int y, int tries)
{
    tries--;
    //ft_putstr_fd("Placing a piece...........\n", 2);
    if (tries == 0)
        return (0);
    if (isplacevalid(map, pc, x, y) == 0)
    {
        x--;
        y--;
        if (x < -5)
            x = 6;
        if (y < -5)
            y = 5;
        //ft_putstr_fd("FAILED TO PLACE A PIECE!\n", 2);
    }
    else
        return (1);
    if (recursion(map, pc, x, y, tries) == 0)
        return (0);
    return (1);
}

int     placepiece(t_map *map, t_piece *pc)
{
    int x;
    int y;

    x = 1;
    y = 1;
    if (recursion(map, pc, x, y, 10000) == 1)
        return (1);
    return (0);
}