/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 12:36:28 by tlouekar          #+#    #+#             */
/*   Updated: 2020/05/12 20:23:00 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

t_ping     *ping(t_map *map, t_piece *pc, int pingX, int pingY, char c, int radius)
{
    int x = radius;
    int y = 0;
    int err = 0;
    map->ping->count = 0;
    map->ping->pingedX = pingX;
    map->ping->pingedY = pingY;
    
    while (x >= y)
    {
        if(!((pingY + y >= map->mapH - 1) || (pingX + x >= map->mapW - 1)))
            if(map->map[pingY + y][pingX + x] == c)
                map->ping->count++;
        if(!((pingY + x >= map->mapH - 1) || (pingX + y >= map->mapW - 1)))
            if(map->map[pingY + x][pingX + y] == c)
                map->ping->count++;
        if(!((pingY + x >= map->mapH - 1) || (pingX - y < 0)))
            if(map->map[pingY + x][pingX - y] == c)
                map->ping->count++;
        if(!((pingY + y >= map->mapH - 1) || (pingX - x < 0)))
            if(map->map[pingY + y][pingX - x] == c)
                map->ping->count++;
        if(!((pingY - y < 0) ||(pingX - x < 0)))
            if(map->map[pingY - y][pingX - x] == c)
                map->ping->count++;
        if(!((pingY - x < 0) || (pingX - y < 0)))
            if(map->map[pingY - x][pingX - y] == c)
                map->ping->count++;
        if(!((pingY - x < 0) || (pingX + y >= map->mapW - 1)))
            if(map->map[pingY - x][pingX + y] == c)
                map->ping->count++;
        if(!((pingY - y < 0) || (pingX + x >= map->mapW - 1)))
            if(map->map[pingY - y][pingX + x] == c)
                map->ping->count++;
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

int     raytrace(t_map *map, t_piece *pc)
{
    int     x;
    int     y;
    int     count;

    x = 0;
    y = 0;
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
                if (x > count)
                {
                    map->rttargetX = 0;
                    map->rttargetY = y;
                    count = x;
                    /*
                    ft_putstr_fd("Raytrace from left: ", 2);
                    ft_putnbr_fd(count, 2);
                    ft_putstr_fd("\n", 2);
                    */
                    break ;
                }
            }
            else
                break ;
            x++;
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
                    /*
                    ft_putstr_fd("Raytrace from right: ", 2);
                    ft_putnbr_fd(count, 2);
                    ft_putstr_fd("\n", 2);
                    */
                    break ;
                }
            }
            else
                break;
            x--;
        }
        y++;
    }
    map->raytrace = 1;
    /*
    ft_putstr_fd("\n\n\n", 2);
    ft_putstr_fd("Raytrace coords: ", 2);
    ft_putnbr_fd(map->rttargetX, 2);
    ft_putstr_fd(", ", 2);
    ft_putnbr_fd(map->rttargetY, 2);
    */
    return (0);
}