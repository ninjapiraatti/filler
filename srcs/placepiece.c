/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placepiece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:39:54 by tlouekar          #+#    #+#             */
/*   Updated: 2020/05/04 20:53:27 by tlouekar         ###   ########.fr       */
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
            if (pc->pcmap[pY][pX] == '*')
            {
                if (map->map[mY - pH + pY][mX - pW + pX] == '.')
                    pX++;
                else if (map->map[mY - pH + pY][mX - pW + pX] == 'X')
                {
                    pX++;
                    pc->isvalidplace = 1;
                }
                else
                    return (0);
            }
            else
                pX++;
        }
        pX = 0;
        pY++;
    }
    if (pc->isvalidplace == 0)
        return (0);
    pc->placeY = mY;
    pc->placeX = mX;
    ft_putstr_fd("Place is valid.\n", 2);
    ft_putstr_fd(pc->pcmap[0], 2);
    ft_putstr_fd(pc->pcmap[1], 2);
    return (1);
}

int recursion (t_map *map, t_piece *pc, int x, int y, int tries)
{
    tries--;
    ft_putstr_fd("Placing a piece...........\n", 2);
    if (tries == 0)
        return (0);
    if (isplacevalid(map, pc, x, y) == 0)
    {
        x--;
        y--;
        if (x < -3)
            x = 4;
        if (y < -3)
            y = 2;
        ft_putstr_fd("FAILED TO PLACE A PIECE!\n", 2);
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

    x = 0;
    y = 0;
    if (recursion(map, pc, x, y, 100) == 1)
        return (1);
    return (0);
}