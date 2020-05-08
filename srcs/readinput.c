/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readinput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 12:00:16 by tlouekar          #+#    #+#             */
/*   Updated: 2020/05/08 14:58:59 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/filler.h"


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
    j = 0;
    line = NULL;
    while (get_next_line(fd, &line) == 1)
    {
        if (map->state != 1)
        {
            if (ft_strstr(line, "$$$") != NULL)
                writeplayer(map, line);
            if (ft_strstr(line, "Plateau") != NULL)
                writemapsize(map, line);
        }
        if (ft_strstr(line, "000") != NULL)
            i = 0;
        if (i < map->mapH && i >= 0)
        {
            writemap(map, line);
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
            ft_putstr_fd("\n\nSTR:", 2);
            ft_putnbr_fd(map->strategy, 2);
            /*
            ft_putstr_fd(" | psX, psY: ", 2);
            ft_putnbr_fd(map->psX, 2);
            ft_putstr_fd(", ", 2);
            ft_putnbr_fd(map->psY, 2);
            ft_putstr_fd(" | osX, osY: ", 2);
            ft_putnbr_fd(map->osX, 2);
            ft_putstr_fd(", ", 2);
            ft_putnbr_fd(map->osY, 2);
            */
            ft_putstr_fd(" | tempX, tempY: ", 2);
            ft_putnbr_fd(map->tempX, 2);
            ft_putstr_fd(", ", 2);
            ft_putnbr_fd(map->tempY, 2);
            ft_putstr_fd(" | LatestosX, LatestosY: ", 2);
            ft_putnbr_fd(map->lastpcopX, 2);
            ft_putstr_fd(", ", 2);
            ft_putnbr_fd(map->lastpcopY, 2);
            ft_putstr_fd(" | Walls, LR: ", 2);
            ft_putnbr_fd(map->lwallreached, 2);
            ft_putnbr_fd(map->rwallreached, 2);
            ft_putstr_fd(" | Number of op @ ping: ", 2);
            ft_putnbr_fd(map->ping->count, 2);
            ft_putchar_fd('\n', 2);
            
            //printdebug(map, pc, 0);
            definepiece(map, pc);
            fizzylogic(map, pc);
            placepiece(map, pc, map->strategy);
            ping(map, pc, pc->placeX, pc->placeY, map->osymbol, 3);
            //ft_putnbr(map->psY - pc->bottomrightY);
            ft_putnbr(pc->placeY);
            ft_putchar(' ');
            //ft_putnbr(map->psX - pc->bottomrightX);
            ft_putnbr(pc->placeX);
            ft_putchar('\n');
            pc->status = 0;
            pc->pcmap = NULL;
            i = -1;
            j = 0;
            map->round++;
            map->lastpcopfound = 0;
        }
    }
    return (0);
}