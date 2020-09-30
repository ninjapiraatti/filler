/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 13:02:27 by tlouekar          #+#    #+#             */
/*   Updated: 2020/09/30 16:19:28 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# define BUFF_SIZE 21
# define TURNS_THRESHOLD_SMALL 15
# define TURNS_THRESHOLD_MEDIUM 24
# define TURNS_THRESHOLD_LARGE 180
# define TURNS_MULTIPLIER 20
# define STRATEGY_INITIAL 1
# define STRATEGY_LATE 2
# define STRATEGY_TO_SE 20
# define STRATEGY_TO_SW 30
# define STRATEGY_TO_NE 10
# define STRATEGY_TO_NW 40
# define TRIES_INTERVAL 200
# define TRIES 2000
# define INITIAL_BEST 1000000

# include "../libft/includes/libft.h"

typedef struct	s_ping
{
	int			count;
	char		ndl;
	char		hstck;
	int			x;
	int			y;
}				t_ping;

typedef struct	s_map
{
	int			psx;
	int			psy;
	int			h;
	int			w;
	int			osx;
	int			osy;
	char		**map;
	int			**heatmap;
	int			state;
	int			round;
	int			foundplayer;
	int			foundop;
	int			strategy;
	int			tempx;
	int			tempy;
	char		psymbol;
	char		osymbol;
	int			lastpcopfound;
	int			lastpcopx;
	int			lastpcopy;
	int			radius;
	int			targetx;
	int			targety;
	int			dirh;
	int			dirv;
	int			validplaces;
	int			threshold;
	t_ping		*ping;
}				t_map;

typedef struct	s_piece
{
	int			h;
	int			w;
	int			x;
	int			y;
	char		**pcmap;
	int			status;
	int			placey;
	int			placex;
	int			toplefty;
	int			topleftx;
	int			bottomrighty;
	int			bottomrightx;
	int			topleftset;
	int			isvaliddot;
	int			isvalidx;
	int			horizontal;
	int			vertical;
	int			offset_top;
	int			offset_left;
	int			bestvalue;
	int			bestvaluetemp;
	int			bestvaluex;
	int			bestvaluey;
}				t_piece;

void			handle_input(t_map *map, t_piece *pc, int fd);
char			*write_player_symbols(t_map *map, char *line);
char			*get_map_size_and_init(t_map *map, char *line);
void			get_last_op_pos(t_map *map, char *line);
void			get_start_positions(t_map *map, char *line);
char			*get_piece_size(t_piece *pc, char *line);
char			*write_piece(t_piece *pc, char *line);
int				init_map(t_map *map);
int				init_piece(t_piece *pc);
int				search_place(t_map *map, t_piece *pc);
int				placement(t_map *map, t_piece *pc, int x, int y);
int				define_piece(t_map *map, t_piece *pc);
int				fizzylogic(t_map *map, t_piece *pc);
void			strategy_to_dir(t_map *map);
int				direction(t_map *map, int dir);
t_ping			*ping(t_map *map, int pingx, int pingy, char c);
int				midpoint(t_map *map, t_piece *pc, int tries, int threshold);
void			heatmap(t_map *map);
void			init_heatmap(t_map *map);

#endif
