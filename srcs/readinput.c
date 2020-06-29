/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readinput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 12:00:16 by tlouekar          #+#    #+#             */
/*   Updated: 2020/06/28 17:30:46 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/filler.h"

/* Writeplayer just tells which characters to use. */

char    *writeplayer(t_map *map, char *line)
{
	if (ft_strstr(line, "p2"))
    {
		map->psymbol = 'X';
        map->osymbol = 'O';
    }
	if (ft_strstr(line, "p1"))
    {
		map->psymbol = 'O';
        map->osymbol = 'X';
    }
    return (line);
}

/* Getmapsize gets the map size and fires initmap. */

char    *getmapsize(t_map *map, char *line)
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

/* Getplayers enters the players' initial positions to the struct. */

char    *getplayers(t_map *map, char *line)
{
    int x;
    int y;
    int i;

    x = 0;
    y = ft_atoi(line);
    i = 4;
    while (x < map->mapW)
    {
        if(line[i] == map->osymbol && map->map[y][x] == '.' && map->lastpcopfound == 0)
        {
            map->lastpcopX = x;
            map->lastpcopY = y;
            map->lastpcopfound = 1;
        }
        map->map[y][x] = line[i];
        if ((line[i] == map->psymbol) && map->foundplayer == 0)
        {
            map->psX = x;
            map->psY = y;
            map->foundplayer = 1;
        }
        else if ((line[i] == map->osymbol) && map->foundop == 0)
        {
            map->osX = x;
            map->osY = y;
            map->foundop = 1;
        }
        x++;
        i++;
    }
    return (0);
}

/* Writepiecemap gets the piece and makes a 2D-array of it. */

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
    if (y + 1 == pc->pieceH)
        pc->status = 2;
    return (0);
}

/* Writepiece gets the piece dimensions. */

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

/* Readinput takes in the map from standard input and turns it into nicer data. */

int     readinput(t_map *map, t_piece *pc, int fd)
{
    char    *line;
    int     i;
    int     j;
    
    i = -1;
    j = 0;
    line = NULL;
    while (get_next_line(fd, &line) == 1)
    {
        if (map->state != 1)
        {
            if (ft_strstr(line, "$$$") != NULL)
                writeplayer(map, line);
            if (ft_strstr(line, "Plateau") != NULL)
                getmapsize(map, line);
        }
        if (ft_strstr(line, "000") != NULL)
            i = 0;
        if (i < map->mapH && i >= 0)
        {
            getplayers(map, line);
            i++;
        }
        if (pc->status == 1)
        {
            writepiecemap(pc, line, j);
            j++;
        }
        if (ft_strstr(line, "Piece") != NULL)
        {
            pc->status = 1;
            writepiece(pc, line);
            initpiece(pc);
        }
        if (pc->status == 2)
        {   
            ft_putstr_fd(" Round: ", 2);
            ft_putnbr_fd(map->round, 2);
            ft_putstr_fd(" | lastPX, lastPY: ", 2);
            ft_putnbr_fd(map->lastpcX, 2);
            ft_putstr_fd(", ", 2);
            ft_putnbr_fd(map->lastpcY, 2);
            ft_putstr_fd(" | lastOX, lastOY: ", 2);
            ft_putnbr_fd(map->lastpcopX, 2);
            ft_putstr_fd(", ", 2);
            ft_putnbr_fd(map->lastpcopY, 2);
            ft_putstr_fd(" | Strategy: ", 2);
            ft_putnbr_fd(map->strategy, 2);
            ft_putstr_fd(" | Raytrace: ", 2);
            ft_putnbr_fd(map->raytrace, 2);
            ft_putstr_fd(" at: ", 2);
            ft_putnbr_fd(map->rttargetX, 2);
            ft_putstr_fd(", ", 2);
            ft_putnbr_fd(map->rttargetY, 2);
            ft_putstr_fd("\n", 2);

            definepiece(map, pc);
            fizzylogic(map, pc);
            placepiece(map, pc, map->strategy);
            ft_putnbr(pc->placeY);
            ft_putchar(' ');
            ft_putnbr(pc->placeX);
            ft_putchar('\n');

            pc->status = 0;
            pc->pcmap = NULL;
            i = -1;
            j = 0;
            map->round++;
            map->lastpcopfound = 0;
            map->founddiagonal = 0;
        }
    }
    return (0);
}