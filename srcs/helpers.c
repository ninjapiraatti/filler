/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 12:36:28 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/09 19:44:42 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

/* Ping and its buddy ping_circle takescoordinates from the map, the "needle" character and radius. 
Ping returns the number of occurrences of that character within the radius. */

void			ping_circle(t_map *map, int x, int y, char c, int radius)
{
	if(!((map->ping->pingedY + y >= map->mapH - 1) || (map->ping->pingedX + x >= map->mapW - 1)))
		if(map->map[map->ping->pingedY + y][map->ping->pingedX + x] == c)
			map->ping->count++;
	if(!((map->ping->pingedY + x >= map->mapH - 1) || (map->ping->pingedX + y >= map->mapW - 1)))
		if(map->map[map->ping->pingedY + x][map->ping->pingedX + y] == c)
			map->ping->count++;
	if(!((map->ping->pingedY + x >= map->mapH - 1) || (map->ping->pingedX - y < 0)))
		if(map->map[map->ping->pingedY + x][map->ping->pingedX - y] == c)
			map->ping->count++;
	if(!((map->ping->pingedY + y >= map->mapH - 1) || (map->ping->pingedX - x < 0)))
		if(map->map[map->ping->pingedY + y][map->ping->pingedX - x] == c)
			map->ping->count++;
	if(!((map->ping->pingedY - y < 0) || (map->ping->pingedX - x < 0)))
		if(map->map[map->ping->pingedY - y][map->ping->pingedX - x] == c)
			map->ping->count++;
	if(!((map->ping->pingedY - x < 0) || (map->ping->pingedX - y < 0)))
		if(map->map[map->ping->pingedY - x][map->ping->pingedX - y] == c)
			map->ping->count++;
	if(!((map->ping->pingedY - x < 0) || (map->ping->pingedX + y >= map->mapW - 1)))
		if(map->map[map->ping->pingedY - x][map->ping->pingedX + y] == c)
			map->ping->count++;
	if(!((map->ping->pingedY - y < 0) || (map->ping->pingedX + x >= map->mapW - 1)))
		if(map->map[map->ping->pingedY - y][map->ping->pingedX + x] == c)
			map->ping->count++;
}

t_ping		*ping(t_map *map, int pingX, int pingY, char c, int radius)
{
	int x = radius;
	int y = 0;
	int err = 0;
	map->ping->count = 0;
	map->ping->pingedX = pingX;
	map->ping->pingedY = pingY;

	while (x >= y)
    {
		ping_circle(map, x, y, c, radius);
        if (err <= 0)
        {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2*x + 1;
        }
    }
	return (map->ping);
}

/* Direction takes an integer as a direction (like "bogey at your six") and turns it into coordinate on the map */

int     direction (t_map *map, t_piece *pc, int dir)
{
    if (dir < 1)
        dir = 12;
    if (dir == 11 || dir == 12 || dir == 1)
    {
        map->targetY = 0;
        if (dir == 1)
            map->targetX = (map->mapW / 4) * 3;
        else  
            map->targetX = (map->mapW / 4) * (dir - 10);    
    }
    else if (dir == 2 || dir == 3 || dir == 4)
    {
        map->targetX = map->mapW - 1; 
        map->targetY = (map->mapH / 4) * (dir - 1); 
    }
    else if (dir == 5 || dir == 6 || dir == 7)
    {
        map->targetY = map->mapH - 1;   
        map->targetX = (map->mapW / 4) * (8 - dir);  
    }
    else if (dir == 8 || dir == 9 || dir == 10)
    {
        map->targetX = 0;  
        map->targetY = (map->mapH / 4) * (11 - dir);
    }
    return (0);
}

/* Raytrace finds the biggest stretch of empty spaces between an edge of the map and first player character. 
It tries, with variable degree of success, not to get the new result too close to the previous one. */

int     raytrace(t_map *map, t_piece *pc)
{
    int     x;
    int     y;
    int     i;
    int     count;

    x = 0;
    y = 0;
    i = 0;
    count = 0;
    while (y < map->mapH - 1)
    {
        x = 0;
        while (x < map->mapW - 1)
        {
            while(map->map[y][x] == '.')
                x++;
            if (map->map[y][x] == map->psymbol)
            {
                if (x > count && map->rttargetX != 0)
                {
                    map->rttargetX = 0;
                    map->rttargetY = y;
                    count = x;
                    break ;
                }
                else
                    break ;
            }
            else
            {
                x = 0;
                break;
            }
        }
        y++;
    }
    y = 0;
    while (y < map->mapH - 1)
    {
        x = map->mapW - 1;
        while (x > 0)
        {
            while(map->map[y][x] == '.')
                x--;
            if (map->map[y][x] == map->psymbol)
            {
                if ((map->mapW - x) > count)
                {
                    map->rttargetX = map->mapW - 1;
                    map->rttargetY = y;
                    count = map->mapW - x;
                    break ;
                }
                else
                    break ;
            }
            else
            {
                x = map->mapW - 1;
                break;
            }
        }
        y++;
    }
    x = 0;
    if (map->round > 140)
    {
        while (x < map->mapW - 1)
        {
            y = map->mapH - 1;
            while (y > 0)
            {
                while(map->map[y][x] == '.' && y > 0)
                    y--;
                if (map->map[y][x] == map->psymbol)
                {
                    if ((map->mapH - y) > count)
                    {
                        map->rttargetX = x;
                        map->rttargetY = map->mapH - 1;
                        count = map->mapH - y;
                        break ;
                    }
                    else
                        break ;
                }
                else
                {
                    y = map->mapH - 1;
                    break;
                }
            }
            x++;
        }
        x = 0;
        while (x < map->mapW - 1)
        {
            y = 0;
            while (y < map->mapH)
            {
                while(map->map[y][x] == '.' && y < map->mapH - 1)
                {
                    y++;
                }
                if (map->map[y][x] == map->psymbol)
                {
                    if (y > count)
                    {
                        map->rttargetX = x;
                        map->rttargetY = 0;
                        count = y;
                        break ;
                    }
                    else
                        break ;
                }
                else
                {
                    y = 0;
                    x++;
                    break;
                }
            }
            x++;
        }
    }
    map->raytrace = 1;
    return (0);
}

