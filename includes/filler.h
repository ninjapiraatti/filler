/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 13:02:27 by tlouekar          #+#    #+#             */
/*   Updated: 2020/05/04 11:38:14 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# define BUFF_SIZE 21

# include "../libft/includes/libft.h"

typedef struct  s_map
{
    int         psX;
    int         psY;
    int         mapH;
    int         mapW;
    int         esX;
    int         esY;
    int         dbg;
    char        **map;
    int         state;
    int         round;
    int         foundx;
}               t_map;

typedef struct  s_piece
{
    int         pieceH;
    int         pieceW;
    char        **pcmap;
    int         status;
}               t_piece;

int			readinput(t_map *map, t_piece *pc, int fd);
int         initmap(t_map *map);
int         initpiece(t_piece *pc);
int         printdebug(t_map *map, t_piece *pc);

#endif