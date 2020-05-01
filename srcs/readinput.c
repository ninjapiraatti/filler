/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readinput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 12:00:16 by tlouekar          #+#    #+#             */
/*   Updated: 2020/05/01 14:28:47 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/filler.h"


char    *writeplayer(t_map *map, char *line)
{
    return (line);
}

char    *writemapsize(t_map *map, char *line)
{
    while (ft_isdigit(*line) == 0)
        line++;
    map->mapH = ft_atoi(line);
    while (ft_isdigit(*line) == 1)
        line++;
    map->mapW = ft_atoi(line);
    return (line);
}

char    *writemap(t_map *map, char *line)
{
    return (line);
}

char    *writepiece(t_piece *pc, char *line)
{
    while (ft_isdigit(*line) == 0)
        line++;
    pc->pieceH = ft_atoi(line);
    while (ft_isdigit(*line) == 1)
        line++;
    pc->pieceW = ft_atoi(line);
    return (line);
}

int     readinput(t_map *map, t_piece *pc)
{
    char    *line;

    line = NULL;
    while (get_next_line(0, &line) == 1)
    {
        if (ft_strstr(line, "$$$") != NULL)
            writeplayer(map, line);
        if (ft_strstr(line, "Plateau") != NULL)
            writemapsize(map, line);
        if (ft_strstr(line, "000") != NULL)
            writemap(map, line);
        if (ft_strstr(line, "Piece") != NULL)
            writepiece(pc, line);
        ft_putstr("12 13\n");
    }
    printdebug(map, pc);
    return (0);
}