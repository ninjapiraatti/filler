/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 13:02:27 by tlouekar          #+#    #+#             */
/*   Updated: 2020/07/13 09:37:52 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# define BUFF_SIZE 21
# define TURNS_THRESHOLD_SMALL 15
# define TURNS_THRESHOLD_MEDIUM 24
# define TURNS_THRESHOLD_LARGE 120
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
    int         x;
    int         y;
}               t_ping;

typedef struct  s_map
{
    int         psx;
    int         psy;
    int         h;
    int         w;
    int         osx;
    int         osy;
    char        **map;
	int			**heatmap;
    int         state;
    int         round;
    int         foundplayer;
    int         foundop;
    int         strategy;
    int         tempx;
    int         tempy;
    char        psymbol;
    char        osymbol;
    int         lastpcx;
    int         lastpcy;
    int         lastpcopfound;
    int         lastpcopx;
    int         lastpcopy;
    int         radius;
    int         targetx;
    int         targety;
    int         dirh;
    int         dirv;
    int         raytrace;
    int         rttargetx;
    int         rttargety;
	int			validplaces;
	int			threshold;
    t_ping      *ping;
    t_area      *area;
}               t_map;

typedef struct  s_piece
{
    int         pieceh;
    int         piecew;
    char        **pcmap;
    int         status;
    int         placey;
    int         placex;
    int         toplefty;
    int         topleftX;
    int         bottomrighty;
    int         bottomrightx;
    int         topleftset;
    int         isvaliddot;
    int         isvalidx;
    int         horizontal;
    int         vertical;
    int         diagonal;
    int         offset_top;
    int         offset_left;
	int			bestvalue;
	int			bestvaluetemp;
	int			bestvaluex;
	int			bestvaluey;
}               t_piece;


int			readinput(t_map *map, t_piece *pc, int fd);
int         initmap(t_map *map);
int         initpiece(t_piece *pc);
int         printdebug(t_map *map, t_piece *pc, int pieceonly);
int         searchplace(t_map *map, t_piece *pc, int strategy);
int			isplacevalid(t_map *map, t_piece *pc, int x, int y);
int         definepiece(t_map *map, t_piece *pc);
int         fizzylogic(t_map *map, t_piece *pc);
void		strategy_to_dir(t_map *map);
int         direction (t_map *map, t_piece *pc, int dir);
t_ping      *ping(t_map *map, int pingx, int pingy, char c);
int         drawcircle(t_map *map, t_piece *pc, int tries, int threshold);
int         raytrace(t_map *map, t_piece *pc);
void		heatmap(t_map *map);
void    	initheatmap(t_map *map);

#endif