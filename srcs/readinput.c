/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readinput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 12:00:16 by tlouekar          #+#    #+#             */
/*   Updated: 2020/05/03 23:35:12 by tlouekar         ###   ########.fr       */
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
    initmap(map);
    return (line);
}

char    *writemap(t_map *map, char *line)
{
    int x;
    int y;
    int i;
    int set;

    set = 0;
    x = 0;
    y = ft_atoi(line);
    i = 4;
    while (x < map->mapW)
    {
        map->map[y][x] = line[i];
        if ((line[i] == 'X' || line[i] == 'x') && set == 0)
        {
            map->psX = x;
            map->psY = y;
            set = 1;
            ft_putstr_fd("Found xX\n", 2);
        }
        x++;
        i++;
    }
    return (0);
}

char    *writepiecemap(t_piece *pc, char *line, int y)
{
    int x;

    x = 0;
    while (x < pc->pieceW)
    {
        pc->pcmap[y][x] = *line;
        x++;
        line++;
    }
    return (0);
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

int     readinput(t_map *map, t_piece *pc, int fd)
{
    char    *line;
    int     i;
    int     j;
    
    i = -1;
    j = -1;
    line = NULL;
    while (get_next_line(fd, &line) == 1)
    {
        if (map->state != 1)
        {
            //if (ft_strstr(line, "$$$") != NULL)
            //    writeplayer(map, line);
            if (ft_strstr(line, "Plateau") != NULL)
            {
                writemapsize(map, line);
            }
        }
        if (ft_strstr(line, "000") != NULL)
            i = 0;
        if (i < map->mapH && i >= 0)
        {
            writemap(map, line);
            ft_putnbr_fd(map->round, 2);
            i++;
        }
        /*
        if (j < pc->pieceH && j >= 0)
        {
            writepiecemap(pc, line, j);
            j++;
        }
        if (ft_strstr(line, "Piece") != NULL)
        {
            j = 0;
            writepiece(pc, line);
            initpiece(pc);
        }*/
        if (i == map->mapH)
        {
            ft_putnbr_fd(map->psY, 2);
            ft_putnbr_fd(map->psX, 2);
            ft_putnbr(map->psY - 1);
            ft_putchar(' ');
            ft_putnbr(map->psX);
            ft_putchar('\n');
            //pc = NULL;
            //map->map = NULL;
            i = -1;
            j = -1;
            map->round++;
        }
    }
    //printdebug(map, pc);
    return (0);
}