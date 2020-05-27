/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 09:49:09 by tlouekar          #+#    #+#             */
/*   Updated: 2020/05/12 20:26:36 by tlouekar         ###   ########.fr       */
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
        ft_putstr_fd("\n\nSTR:", 2);
        ft_putnbr_fd(map->strategy, 2);
        ft_putstr_fd(" | tempX, tempY: ", 2);
        ft_putnbr_fd(map->tempX, 2);
        ft_putstr_fd(", ", 2);
        ft_putnbr_fd(map->tempY, 2);
        ft_putstr_fd(" | rtX, rtY: ", 2);
        ft_putnbr_fd(map->rttargetX, 2);
        ft_putstr_fd(", ", 2);
        ft_putnbr_fd(map->rttargetY, 2);
        ft_putstr_fd(" | LatestosX, LatestosY: ", 2);
        ft_putnbr_fd(map->lastpcopX, 2);
        ft_putstr_fd(", ", 2);
        ft_putnbr_fd(map->lastpcopY, 2);
        ft_putstr_fd(" | Directions, H, V: ", 2);
        ft_putnbr_fd(map->dirh, 2);
        ft_putstr_fd(", ", 2);
        ft_putnbr_fd(map->dirv, 2);
        ft_putstr_fd(" | Pinged at X, Y: ", 2);
        ft_putnbr_fd(map->ping->pingedX, 2);
        ft_putstr_fd(", ", 2);
        ft_putnbr_fd(map->ping->pingedY, 2);
        ft_putchar_fd('\n', 2);
        ft_putstr_fd(" Number ping count: ", 2);
        ft_putnbr_fd(map->ping->count, 2);
        ft_putchar_fd('\n', 2);
        /*
        while (y < map->mapH)
        {
            ft_putstr_fd(map->map[y], 2);
            ft_putstr_fd("\n", 2);
            y++;
        }
        */
    }
    /*
    ft_putstr_fd("\n", 2);
    ft_putstr_fd("PIECE: \n", 2);
    while (y2 < pc->pieceH)
    {
        ft_putstr_fd(pc->pcmap[y2], 2);
        ft_putstr_fd("\n", 2);
        y2++;
    }
    */
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