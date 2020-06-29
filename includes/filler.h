/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 13:02:27 by tlouekar          #+#    #+#             */
/*   Updated: 2020/06/29 10:51:23 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# define BUFF_SIZE 21
# define TURNS_THRESHOLD_SMALL 15
# define TURNS_THRESHOLD_MEDIUM 24
# define TURNS_THRESHOLD_LARGE 140
# define TURNS_MULTIPLIER 20
# define STRATEGY_INITIAL 1
# define STRATEGY_LATE 2
# define STRATEGY_TO_SE 20
# define STRATEGY_TO_SW 30
# define STRATEGY_TO_NE 10
# define STRATEGY_TO_NW 40
# define TRIES_INTERVAL 200


# include "../libft/includes/libft.h"

typedef struct  s_area
{
    int         **empties;
    int         rows;
}               t_area;

typedef struct  s_ping
{
    int         count;
    char        ndl;
    char        hstck;
    int         pingedX;
    int         pingedY;
}               t_ping;

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
	char		**heatmap;
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
    int         lastpcopfound;
    int         lastpcopX;
    int         lastpcopY;
    int         radius;
    int         lwallreached;
    int         rwallreached;
    int         targetX;
    int         targetY;
    int         dirh;
    int         dirv;
    int         founddiagonal;
    int         raytrace;
    int         rttargetX;
    int         rttargetY;
    t_ping      *ping;
    t_area      *area;
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
    int         diagonal;
    int         offset_top;
    int         offset_left;
}               t_piece;


int			readinput(t_map *map, t_piece *pc, int fd);
int         initmap(t_map *map);
int         initpiece(t_piece *pc);
int         printdebug(t_map *map, t_piece *pc, int pieceonly);
int         placepiece(t_map *map, t_piece *pc, int strategy);
int         definepiece(t_map *map, t_piece *pc);
int         fizzylogic(t_map *map, t_piece *pc);
int         direction (t_map *map, t_piece *pc, int dir);
t_ping      *ping(t_map *map, int pingX, int pingY, char c, int radius);
int         drawcircle(t_map *map, t_piece *pc, int tries, int radius);
int         checkdiagonals(t_map *map, t_piece *pc);
int         raytrace(t_map *map, t_piece *pc);
int         closedarea(t_map *map, t_piece *pc, int ox, int oy, int rounds);

#endif