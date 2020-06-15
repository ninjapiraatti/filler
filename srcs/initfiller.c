/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initfiller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 15:52:40 by tlouekar          #+#    #+#             */
/*   Updated: 2020/06/11 09:14:40 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int     initmap(t_map *map)
{
    int i;

    i = 0;
    map->map = (char **)malloc(sizeof(char *) * (map->mapH + 1));
    while (i < map->mapH)
    {
        map->map[i] = (char *)malloc(sizeof(char *) * (map->mapW + 1));
        i++;
    }
    map->state = 1;
    map->round = 1;
    map->foundplayer = 0;
    map->foundop = 0;
    map->strategy = 0;
    map->dirh = 0;
    map->dirv = 0;
    map->raytrace = 0;
    map->rttargetX = -1;
    map->rttargetY = -1;
    if (!(map->ping = (t_ping *)malloc(sizeof(t_ping))))
		return (0);
    if (!(map->area = (t_area *)malloc(sizeof(t_area))))
		return (0);
    return (0);
}

int     initpiece(t_piece *pc)
{
    int i;

    i = 0;
    pc->pcmap = (char **)malloc(sizeof(char *) * (pc->pieceH + 1));
    while (i < pc->pieceH)
    {
        pc->pcmap[i] = (char *)malloc(sizeof(char *) * (pc->pieceW + 1));
        i++;
    }
    pc->topleftset = 0;
    pc->isvaliddot = 0;
    pc->isvalidx = 0;
    pc->offset_left = -1;
    pc->offset_top = -1;
    return (0);
}