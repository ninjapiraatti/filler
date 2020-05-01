/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 09:49:09 by tlouekar          #+#    #+#             */
/*   Updated: 2020/05/01 14:26:52 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"
#include <unistd.h>

int         printdebug(t_map *map, t_piece *pc)
{
    ft_putstr_fd("\n\n******* DEBUG INFO ********\n", 2);
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
    return (0);
}

int			main(void)
{
    t_map   *map;
    t_piece *pc;

    if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (0);
    if (!(pc = (t_piece *)malloc(sizeof(t_piece))))
		return (0);
    readinput(map, pc);
    return (0);
}