/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 12:36:28 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/12 17:56:25 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

/* Ping and its buddy ping_circle takescoordinates from the map, the "needle" character and radius. 
Ping returns the number of occurrences of that character within the radius. */

void			ping_circle(t_map *map, int x, int y, char c)
{
	if(!((map->ping->y + y >= map->h - 1) || (map->ping->x + x >= map->w - 1)))
		if(map->map[map->ping->y + y][map->ping->x + x] == c)
			map->ping->count++;
	if(!((map->ping->y + x >= map->h - 1) || (map->ping->x + y >= map->w - 1)))
		if(map->map[map->ping->y + x][map->ping->x + y] == c)
			map->ping->count++;
	if(!((map->ping->y + x >= map->h - 1) || (map->ping->x - y < 0)))
		if(map->map[map->ping->y + x][map->ping->x - y] == c)
			map->ping->count++;
	if(!((map->ping->y + y >= map->h - 1) || (map->ping->x - x < 0)))
		if(map->map[map->ping->y + y][map->ping->x - x] == c)
			map->ping->count++;
	if(!((map->ping->y - y < 0) || (map->ping->x - x < 0)))
		if(map->map[map->ping->y - y][map->ping->x - x] == c)
			map->ping->count++;
	if(!((map->ping->y - x < 0) || (map->ping->x - y < 0)))
		if(map->map[map->ping->y - x][map->ping->x - y] == c)
			map->ping->count++;
	if(!((map->ping->y - x < 0) || (map->ping->x + y >= map->w - 1)))
		if(map->map[map->ping->y - x][map->ping->x + y] == c)
			map->ping->count++;
	if(!((map->ping->y - y < 0) || (map->ping->x + x >= map->w - 1)))
		if(map->map[map->ping->y - y][map->ping->x + x] == c)
			map->ping->count++;
}

t_ping		*ping(t_map *map, int pingX, int pingY, char c)
{
	int x = map->radius;
	int y = 0;
	int err = 0;
	map->ping->count = 0;
	map->ping->x = pingX;
	map->ping->y = pingY;

	while (x >= y)
    {
		ping_circle(map, x, y, c);
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

void	strategy_to_dir(t_map *map)
{
	if (map->psx <= map->osx && (map->dirh == 0 || map->dirv == 0))
	{
		if (map->psy <= map->osy)
		{
			map->dirh = 2;
			map->dirv = 7;
			map->strategy = STRATEGY_TO_SE;
		}
		else
		{
			map->dirh = 3;
			map->dirv = 12;
			map->strategy = STRATEGY_TO_NE;
		}
	}
	else if (map->dirh == 0 || map->dirv == 0)
	{
		if (map->psy >= map->osy)
		{
			map->dirh = 9;
			map->dirv = 1;
			map->strategy = STRATEGY_TO_NW;
		}
		else
		{
			map->dirh = 9;
			map->dirv = 6;
			map->strategy = STRATEGY_TO_SW;
		}
	}
}
/* Direction takes an integer as a direction (like "bogey at your six") and turns it into coordinate on the map */

int     direction (t_map *map, t_piece *pc, int dir)
{
    if (dir < 1)
        dir = 12;
    if (dir == 11 || dir == 12 || dir == 1)
    {
        map->targety = 0;
        if (dir == 1)
            map->targetx = (map->w / 4) * 3;
        else  
            map->targetx = (map->w / 4) * (dir - 10);    
    }
    else if (dir == 2 || dir == 3 || dir == 4)
    {
        map->targetx = map->w - 1; 
        map->targety = (map->h / 4) * (dir - 1); 
    }
    else if (dir == 5 || dir == 6 || dir == 7)
    {
        map->targety = map->h - 1;   
        map->targetx = (map->w / 4) * (8 - dir);  
    }
    else if (dir == 8 || dir == 9 || dir == 10)
    {
        map->targetx = 0;  
        map->targety = (map->h / 4) * (11 - dir);
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
    while (y < map->h - 1)
    {
        x = 0;
        while (x < map->w - 1)
        {
            while(map->map[y][x] == '.')
                x++;
            if (map->map[y][x] == map->psymbol)
            {
                if (x > count && map->rttargetx != 0)
                {
                    map->rttargetx = 0;
                    map->rttargety = y;
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
    while (y < map->h - 1)
    {
        x = map->w - 1;
        while (x > 0)
        {
            while(map->map[y][x] == '.')
                x--;
            if (map->map[y][x] == map->psymbol)
            {
                if ((map->w - x) > count)
                {
                    map->rttargetx = map->w - 1;
                    map->rttargety = y;
                    count = map->w - x;
                    break ;
                }
                else
                    break ;
            }
            else
            {
                x = map->w - 1;
                break;
            }
        }
        y++;
    }
    x = 0;
    if (map->round > 140)
    {
        while (x < map->w - 1)
        {
            y = map->h - 1;
            while (y > 0)
            {
                while(map->map[y][x] == '.' && y > 0)
                    y--;
                if (map->map[y][x] == map->psymbol)
                {
                    if ((map->h - y) > count)
                    {
                        map->rttargetx = x;
                        map->rttargety = map->h - 1;
                        count = map->h - y;
                        break ;
                    }
                    else
                        break ;
                }
                else
                {
                    y = map->h - 1;
                    break;
                }
            }
            x++;
        }
        x = 0;
        while (x < map->w - 1)
        {
            y = 0;
            while (y < map->h)
            {
                while(map->map[y][x] == '.' && y < map->h - 1)
                {
                    y++;
                }
                if (map->map[y][x] == map->psymbol)
                {
                    if (y > count)
                    {
                        map->rttargetx = x;
                        map->rttargety = 0;
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

