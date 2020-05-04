/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 09:49:09 by tlouekar          #+#    #+#             */
/*   Updated: 2020/05/04 12:06:50 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"
#include <unistd.h>
#include <fcntl.h>

int         printdebug(t_map *map, t_piece *pc, int pieceonly)
{
    int y;
    int y2;

    y = 0;
    y2 = 0;

    ft_putstr_fd("\n\n******* DEBUG INFO ********\n", 2);
    if (pieceonly == 0)
    {
        ft_putstr_fd("Map height: ", 2);
        ft_putnbr_fd(map->mapH, 2);
        ft_putstr_fd("\n", 2);
        ft_putstr_fd("Map width: ", 2);
        ft_putnbr_fd(map->mapW, 2);
        ft_putstr_fd("\n", 2);
        ft_putstr_fd("Player start X: ", 2);
        ft_putnbr_fd(map->psX, 2);
        ft_putstr_fd("\n", 2);
        ft_putstr_fd("Player start Y: ", 2);
        ft_putnbr_fd(map->psY, 2);
        ft_putstr_fd("\n", 2);
        ft_putstr_fd("Opponent start X: ", 2);
        ft_putnbr_fd(map->esX, 2);
        ft_putstr_fd("\n", 2);
        ft_putstr_fd("Opponent start Y: ", 2);
        ft_putnbr_fd(map->esY, 2);
        ft_putstr_fd("\n", 2);
        ft_putstr_fd("Piece height: ", 2);
        ft_putnbr_fd(pc->pieceH, 2);
        ft_putstr_fd("\n", 2);
        ft_putstr_fd("Piece width: ", 2);
        ft_putnbr_fd(pc->pieceW, 2);
        ft_putstr_fd("\n", 2);
        ft_putstr_fd("Debug INT: ", 2);
        ft_putnbr_fd(map->dbg, 2);
        ft_putstr_fd("\n", 2);
        ft_putstr_fd("Map: \n", 2);
        while (y < map->mapH)
        {
            ft_putstr_fd(map->map[y], 2);
            ft_putstr_fd("\n", 2);
            y++;
        }
    }
    ft_putstr_fd("\n", 2);
    ft_putstr_fd("PIECE: \n", 2);
    while (y2 < pc->pieceH)
    {
        ft_putstr_fd(pc->pcmap[y2], 2);
        ft_putstr_fd("\n", 2);
        y2++;
    }
    return (0);
}

int     main(int argc, char **argv)
{
    t_map   *map;
    t_piece *pc;
    int     fd;

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