/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definepiece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:16:21 by tlouekar          #+#    #+#             */
/*   Updated: 2020/06/09 15:21:24 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int     offset(t_piece *pc)
{
    int     top;
    int     left;
    int     x;
    int     y;

    top = 0;
    left = 0;
    x = 0;
    y = 0;

    while (y < (pc->pieceH))
    {
        x = 0;
        while (x < (pc->pieceW))
        {
            if (pc->pcmap[y][x] == '*' && pc->offset_top == -1)
            {
                pc->offset_top = top;
                x++;
            }
            else
                x++;
        }
        y++;
        top++;
        //ft_putstr_fd(pc->pcmap[y], 2);
        //ft_putstr_fd("\n", 2);
    }
    x = 0;
    while (x < (pc->pieceW))
    {
        y = 0;
        while (y < (pc->pieceH))
        {
            if (pc->pcmap[y][x] == '*' && pc->offset_left == -1)
            {
                pc->offset_left = left;
                y++;
            }
            else
                y++;
        }
        x++;
        left++;
        //ft_putstr_fd(pc->pcmap[y], 2);
        //ft_putstr_fd("\n", 2);
    }
    return (1);
}

int     checkdiagonalpiece(t_map *map, t_piece *pc)
{
    int     x;
    int     y;

    x = 0;
    y = 0;
    while (y < (pc->pieceH - 1))
    {
        while (x < (pc->pieceW - 2))
        {
            if (pc->pcmap[y][x] == '.' && pc->pcmap[y][x + 1] == '*')
            {
                if (pc->pcmap[y + 1][x] == '*' && pc->pcmap[y + 1][x + 1] == '.')
                {
                    pc->diagonal = 1;
                    return (1);
                }
            }
            else if (pc->pcmap[y][x] == '*' && pc->pcmap[y][x + 1] == '.')
            {
                if (pc->pcmap[y + 1][x] == '.' && pc->pcmap[y + 1][x + 1] == '*')
                {
                    pc->diagonal = 1;
                    return (1);
                }
            }
            x++;
        }
        y++;
        x = 0;
    }
    return (0);
}

int     definepiece(t_map *map, t_piece *pc)
{
    int y;
    int x;

    y = 0;
    x = 0;
    while (y < pc->pieceH)
    {
        while (x < pc->pieceW)
        {
            if (pc->pcmap[y][x] == '*')
            {
                if (pc->topleftset == 0)
                {
                    pc->topleftY = y;
                    pc->topleftX = x;
                    pc->topleftset = 1;
                }
                else
                {
                    pc->bottomrightY = y;
                    pc->bottomrightX = x;
                }
            }
            x++;
        }
        x = 0;
        y++;
    }
    pc->horizontal = 0;
    pc->vertical = 0;
    pc->diagonal = 0;
    if (pc->bottomrightX - pc->topleftX > pc->bottomrightY - pc->topleftY)
        pc->horizontal = 1;
    else if (pc->bottomrightX - pc->topleftX < pc->bottomrightY - pc->topleftY)
        pc->vertical = 1;
    else if (map->round % 2 == 0)
        pc->horizontal = 1;
    else
        pc->vertical = 1;
    offset(pc);
    checkdiagonalpiece(map, pc);
    return (0);
}