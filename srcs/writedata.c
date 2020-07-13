/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writedata.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 13:06:17 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/13 18:38:28 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

/*
** Writeplayer just tells which characters to use.
*/

char		*writeplayer(t_map *map, char *line)
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

/*
** Getmapsize gets the map size and fires initmap.
*/

char		*getmapsize(t_map *map, char *line)
{
	while (ft_isdigit(*line) == 0)
		line++;
	map->h = ft_atoi(line);
	while (ft_isdigit(*line) == 1)
		line++;
	map->w = ft_atoi(line);
	initmap(map);
	return (line);
}

/*
** get_last_op_pos gets the last opponent position and writes it to the struct.
*/

void		get_last_op_pos(t_map *map, char *line)
{
	int		x;
	int		y;
	int		i;

	x = 0;
	y = ft_atoi(line);
	i = 4;
	while (x < map->w)
	{
		if (line[i] == map->osymbol &&
		map->map[y][x] == '.' && map->lastpcopfound == 0)
		{
			map->lastpcopx = x;
			map->lastpcopy = y;
			map->lastpcopfound = 1;
		}
		map->map[y][x] = line[i];
		x++;
		i++;
	}
	get_start_positions(map, line);
}

/*
** Writepiecemap gets the piece and makes a 2D-array of it.
*/

char		*writepiecemap(t_piece *pc, char *line)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (pc->pcmap[y][x] == '.' || pc->pcmap[y][x] == '*')
		y++;
	if (y == pc->h - 1)
		pc->status = 2;
	while (x < pc->w)
	{
		pc->pcmap[y][x] = *line;
		x++;
		line++;
	}
	return (0);
}

/*
** Writepiece gets the piece dimensions.
*/

char		*writepiece(t_piece *pc, char *line)
{
	while (ft_isdigit(*line) == 0)
		line++;
	pc->h = ft_atoi(line);
	while (ft_isdigit(*line) == 1)
		line++;
	pc->w = ft_atoi(line);
	return (line);
}
