/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 09:49:09 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/13 15:23:49 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"
#include <unistd.h>
#include <fcntl.h>

int			main(int argc, char **argv)
{
	t_map	*map;
	t_piece	*pc;
	int		fd;

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
	readinput(map, pc, fd);
	return (0);
}
