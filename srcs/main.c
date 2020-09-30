/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 09:49:09 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/20 14:39:04 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"
#include <unistd.h>
#include <fcntl.h>

void		freemaps(t_map *map, t_piece *pc)
{
	int		i;

	i = 0;
	while (i < map->h)
	{
		free(map->map[i]);
		i++;
	}
	i = 0;
	while (i < map->h)
	{
		free(map->heatmap[i]);
		i++;
	}
	free(map->ping);
	free(map->map);
	free(map->heatmap);
	free(map);
	free(pc);
}

int			main(int argc, char **argv)
{
	t_map	*map;
	t_piece	*pc;
	int		fd;
	int		i;

	i = 0;
	fd = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		ft_putnbr(fd);
		ft_putstr(" is the fd. Using file.\n");
	}
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (0);
	if (!(pc = (t_piece *)malloc(sizeof(t_piece))))
		return (0);
	handle_input(map, pc, fd);
	freemaps(map, pc);
	return (0);
}
