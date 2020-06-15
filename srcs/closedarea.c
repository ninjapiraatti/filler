/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closedarea.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 15:17:38 by tlouekar          #+#    #+#             */
/*   Updated: 2020/06/11 09:47:16 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"


int     checkadjacent(t_area *area, int x, int y, int rounds)
{
    int     i;

    i = 0;
    y -= 1;
    while (i < (rounds * 100))
    {
        if (area->empties[i][0] == x && area->empties[i][1] == y)
            return (1);
        i++;
    }
    i = 0;
    y += 1;
    x += 1;
    while (i < (rounds * 100))
    {
        if (area->empties[i][0] == x && area->empties[i][1] == y)
            return (1);
        i++;
    }
    i = 0;
    y += 1;
    x -= 1;
    while (i < (rounds * 100))
    {
        if (area->empties[i][0] == x && area->empties[i][1] == y)
            return (1);
        i++;
    }
    i = 0;
    y -= 1;
    x -= 1;
    while (i < (rounds * 100))
    {
        if (area->empties[i][0] == x && area->empties[i][1] == y)
            return (1);
        i++;
    }
    return (0);
}

int     addtolist(t_area *area, int x, int y, int count)
{
    int     i;

    i = 0;
    while (i < count)
    {
        if (area->empties[i][0] == x && area->empties[i][1] == y)
            return (0);
        i++;
    }
    area->empties[count][0] = x;
    area->empties[count][1] = y;
    return (1);
}

int closedarea(t_map *map, t_piece *pc, int ox, int oy, int rounds)
{
    int     x;
    int     y;
    int     i;
    int     j;
    int     limit; 
    int     count;  

    i = 0;
    j = 0;
    limit = 2;
    count = 0;
    x = ox;
    y = oy;
    map->area->empties = (int **)malloc(sizeof(int *) * (rounds * 100));
    while (i < (rounds * 100))
    {
        map->area->empties[i] = (int *)malloc(sizeof(int *) * 2);
        i++;
    }
    i = 0;
    if (map->map[y][x] != '.' || map->map[y - 1][x] != '.')
        return (0);
    addtolist(map->area, x, y - 1, count);
    while (i < rounds)
    {
        j = 0;
        y = oy + ((i + 1) * -1);
        while (j < limit)
        {
            while (y <= oy + limit && y < map->mapH)
            {   
                x = ox + ((i + 1) * -1);
                while (y < 0)
                    y++;
                while (x <= ox + limit && x < map->mapW)
                {
                    while (x < 0)
                        x++;
                    if (y < map->mapH && x < map->mapW && y > 0 && x >= 0)
                    {
                        if (map->map[y][x] == '.' && checkadjacent(map->area, x, y, rounds) == 1)
                        {
                            if (addtolist(map->area, x, y, count) == 1)
                            {
                                count++;
                                ft_putstr_fd(".", 2);
                            }
                        }
                        else if (map->map[y][x] == map->osymbol && checkadjacent(map->area, x, y, rounds) == 1)
                        {
                            ft_putstr_fd("Not a closed area!", 2);
                            return (0);
                        }
                    }
                    x++;
                }
                y++;
            }
            j++;
        }
        limit += 2;
        i++;
    }
    /*
    ft_putnbr_fd(area->empties[0][0], 2);
    ft_putnbr_fd(area->empties[0][1], 2);
    ft_putstr_fd("\n", 2);
    ft_putnbr_fd(area->empties[1][0], 2);
    ft_putnbr_fd(area->empties[1][1], 2);
    ft_putstr_fd("\n", 2);
    ft_putnbr_fd(area->empties[2][0], 2);
    ft_putnbr_fd(area->empties[2][1], 2);
    ft_putstr_fd("\n", 2);
    ft_putnbr_fd(area->empties[3][0], 2);
    ft_putnbr_fd(area->empties[3][1], 2);
    ft_putstr_fd("\n", 2);
    ft_putnbr_fd(area->empties[4][0], 2);
    ft_putnbr_fd(area->empties[4][1], 2);
    ft_putstr_fd("\n", 2);
    ft_putnbr_fd(area->empties[5][0], 2);
    ft_putnbr_fd(area->empties[5][1], 2);
    ft_putstr_fd("\n", 2);
    ft_putnbr_fd(area->empties[6][0], 2);
    ft_putnbr_fd(area->empties[6][1], 2);
    ft_putstr_fd("\n", 2);
    ft_putnbr_fd(area->empties[7][0], 2);
    ft_putnbr_fd(area->empties[7][1], 2);
    ft_putstr_fd("\n", 2);
    ft_putnbr_fd(area->empties[8][0], 2);
    ft_putnbr_fd(area->empties[8][1], 2);
    ft_putstr_fd("\n", 2);
    ft_putnbr_fd(area->empties[9][0], 2);
    ft_putnbr_fd(area->empties[9][1], 2);
    ft_putstr_fd("\n", 2);
    ft_putnbr_fd(area->empties[10][0], 2);
    ft_putnbr_fd(area->empties[10][1], 2);
    ft_putstr_fd("\n", 2);
    ft_putnbr_fd(area->empties[11][0], 2);
    ft_putnbr_fd(area->empties[11][1], 2);
    ft_putstr_fd("\n", 2);
    ft_putnbr_fd(area->empties[12][0], 2);
    ft_putnbr_fd(area->empties[12][1], 2);
    ft_putstr_fd("\n", 2);
    ft_putnbr_fd(area->empties[13][0], 2);
    ft_putnbr_fd(area->empties[13][1], 2);
    */
    ft_putstr_fd("\n\nIt's a closed area.\n\n", 2);
    map->area->rows = count;
    return(1);
}