/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fizzylogic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:42:16 by tlouekar          #+#    #+#             */
/*   Updated: 2020/05/06 21:04:27 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int     updatestrategy(t_map *map)
{
    if (map->psX <= map->osX)
    {
        if (map->psY <= map->osY)
        {
            map->lbranchX = map->mapW - 1;
            map->lbranchY = map->psY;
            map->rbranchX = map->psX;
            map->rbranchY = map->mapH - 1;
            return (2);
        }
        else
        {
            map->lbranchX = map->psX;
            map->lbranchY = 0;
            map->rbranchX = map->mapW - 1;
            map->rbranchY = map->psY;
            return (1);
        }
    }
    else
    {
        if (map->psY >= map->osY)
        {
            map->lbranchX = 0;
            map->lbranchY = map->psY;
            map->rbranchX = map->psX;
            map->rbranchY = 0;
            return (4);
        }
        else
        {
            map->rbranchX = 0;
            map->rbranchY = map->psY;
            map->lbranchX = map->psX;
            map->lbranchY = map->mapH - 1;
            return (3);
        }
    }
}

int     fizzylogic(t_map *map, t_piece *pc)
{
    if (map->strategy == 0)
        map->strategy = updatestrategy(map);
    return (0);
}