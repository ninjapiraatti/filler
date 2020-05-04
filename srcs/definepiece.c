/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definepiece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:16:21 by tlouekar          #+#    #+#             */
/*   Updated: 2020/05/04 14:47:34 by tlouekar         ###   ########.fr       */
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
    return (0);
}