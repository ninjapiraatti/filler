/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initfiller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 15:52:40 by tlouekar          #+#    #+#             */
/*   Updated: 2020/05/03 23:15:58 by tlouekar         ###   ########.fr       */
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
    return (0);
}