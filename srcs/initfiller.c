/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initfiller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 15:52:40 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/13 18:42:15 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		init_more_map(t_map *map)
{
	map->state = 1;
	map->round = 1;
	map->foundplayer = 0;
	map->foundop = 0;
	map->strategy = 0;
	map->dirh = 0;
	map->dirv = 0;
	map->raytrace = 0;
	map->rttargetx = -1;
	map->rttargety = -1;
	map->validplaces = 0;
	map->threshold = 0;
	if (!(map->ping = (t_ping *)malloc(sizeof(t_ping))))
		return (0);
	return (1);
}

int		initmap(t_map *map)
{
	int	i;

	i = 0;
	map->map = (char **)malloc(sizeof(char *) * (map->h + 1));
	while (i < map->h)
	{
		map->map[i] = (char *)malloc(sizeof(char *) * (map->w + 1));
		i++;
	}
	i = 0;
	map->heatmap = (int **)malloc(sizeof(int *) * (map->h + 1));
	while (i < map->h)
	{
		map->heatmap[i] = (int *)malloc(sizeof(int *) * (map->w + 1));
		i++;
	}
	if (init_more_map(map) == 0)
		return (0);
	return (1);
}

void	get_start_positions(t_map *map, char *line)
{
	int		x;
	int		y;
	int		i;

	x = 0;
	y = ft_atoi(line);
	i = 4;
	while (x < map->w)
	{
		if ((line[i] == map->psymbol) && map->foundplayer == 0)
		{
			map->psx = x;
			map->psy = y;
			map->foundplayer = 1;
		}
		else if ((line[i] == map->osymbol) && map->foundop == 0)
		{
			map->osx = x;
			map->osy = y;
			map->foundop = 1;
		}
		x++;
		i++;
	}
}

void	initheatmap(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < map->h)
	{
		while (x < map->w)
		{
			map->heatmap[y][x] = 0;
			x++;
		}
		y++;
	}
}

int		initpiece(t_piece *pc)
{
	int	i;

	i = 0;
	pc->pcmap = (char **)malloc(sizeof(char *) * (pc->h + 1));
	while (i < pc->h)
	{
		pc->pcmap[i] = (char *)malloc(sizeof(char *) * (pc->w + 1));
		i++;
	}
	pc->topleftset = 0;
	pc->isvaliddot = 0;
	pc->isvalidx = 0;
	pc->bestvaluey = 0;
	pc->bestvaluex = 0;
	pc->bestvalue = 1000000;
	pc->offset_left = -1;
	pc->offset_top = -1;
	return (0);
}
