/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definepiece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:16:21 by tlouekar          #+#    #+#             */
/*   Updated: 2020/05/06 15:55:31 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int     definepiece(t_piece *pc)
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
    if (pc->bottomrightX - pc->topleftX > pc->bottomrightY - pc->topleftY)
        pc->horizontal = 1;
    else
        pc->vertical = 1;
    return (0);
}