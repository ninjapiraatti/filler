/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 13:02:27 by tlouekar          #+#    #+#             */
/*   Updated: 2020/05/07 15:55:37 by tlouekar         ###   ########.fr       */
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
    int         osX;
    int         osY;
    int         dbg;
    char        **map;
    int         state;
    int         round;
    int         foundplayer;
    int         foundop;
    int         lbranchY;
    int         lbranchX;
    int         rbranchY;
    int         rbranchX;
    int         strategy;
    int         tempX;
    int         tempY;
    char        psymbol;
    char        osymbol;
    int         lastpcX;
    int         lastpcY;
    int         lastpcopX;
    int         lastpcopY;
    int         radius;
    int         lwallreached;
    int         rwallreached;
}               t_map;

typedef struct  s_piece
{
    int         pieceH;
    int         pieceW;
    char        **pcmap;
    int         status;
    int         placeY;
    int         placeX;
    int         topleftY;
    int         topleftX;
    int         bottomrightY;
    int         bottomrightX;
    int         topleftset;
    int         isvaliddot;
    int         isvalidx;
    int         horizontal;
    int         vertical;

}               t_piece;

int			readinput(t_map *map, t_piece *pc, int fd);
int         initmap(t_map *map);
int         initpiece(t_piece *pc);
int         printdebug(t_map *map, t_piece *pc, int pieceonly);
int         placepiece(t_map *map, t_piece *pc, int strategy);
int         definepiece(t_piece *pc);
int         fizzylogic(t_map *map, t_piece *pc);

#endif