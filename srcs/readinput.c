/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readinput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 12:00:16 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/13 15:15:26 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../includes/filler.h"

/*
** Readinput takes in the map from standard input and turns it into nicer data.
*/

int			writedatas(t_map *map, t_piece *pc, char *line, int i)
{
	if (map->state != 1)
	{
		if (ft_strstr(line, "$$$") != NULL)
			writeplayer(map, line);
		if (ft_strstr(line, "Plateau") != NULL)
		{
			getmapsize(map, line);
			initheatmap(map);
		}
	}
	if (ft_strstr(line, "000") != NULL)
		i = 0;
	if (i < map->h && i >= 0)
	{
		getplayers(map, line);
		i++;
	}
	pc->status == 1 ? writepiecemap(pc, line) : 0;
	if (ft_strstr(line, "Piece") != NULL)
	{
		pc->status = 1;
		writepiece(pc, line);
		initpiece(pc);
	}
	return (i);
}

int			readinput(t_map *map, t_piece *pc, int fd)
{
	char	*line;
	int		i;

	i = -1;
	line = NULL;
	while (get_next_line(fd, &line) == 1)
	{
		i = writedatas(map, pc, line, i);
		if (pc->status == 2)
		{
			definepiece(map, pc);
			fizzylogic(map, pc);
			searchplace(map, pc, map->strategy);
			ft_putnbr(pc->placey);
			ft_putchar(' ');
			ft_putnbr(pc->placex);
			ft_putchar('\n');
			pc->status = 0;
			pc->pcmap = NULL;
			i = -1;
			map->round++;
			map->lastpcopfound = 0;
		}
	}
	return (0);
}
