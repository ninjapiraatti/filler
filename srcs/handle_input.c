/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 09:20:21 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/15 15:46:19 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../includes/filler.h"

/*
** handle_input takes in the map from standard input
** and turns it into nicer data.
*/

int			writedatas(t_map *map, t_piece *pc, char *line, int i)
{
	if (map->state != 1)
	{
		if (ft_strstr(line, "$$$") != NULL)
			write_player_symbols(map, line);
		if (ft_strstr(line, "Plateau") != NULL)
		{
			get_map_size_and_init(map, line);
			init_heatmap(map);
		}
	}
	if (ft_strstr(line, "000") != NULL)
		i = 0;
	if (i < map->h && i >= 0)
	{
		get_last_op_pos(map, line);
		i++;
	}
	pc->status == 1 ? write_piece(pc, line) : 0;
	if (ft_strstr(line, "Piece") != NULL)
	{
		pc->status = 1;
		get_piece_size(pc, line);
		init_piece(pc);
	}
	return (i);
}

void		handle_input(t_map *map, t_piece *pc, int fd)
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
			define_piece(map, pc);
			fizzylogic(map, pc);
			search_place(map, pc);
			free(pc->pcmap);
			ft_putnbr(pc->placey);
			ft_putchar(' ');
			ft_putnbr(pc->placex);
			ft_putchar('\n');
			pc->status = 0;
			i = -1;
			map->round++;
			map->lastpcopfound = 0;
		}
		free(line);
	}
}
