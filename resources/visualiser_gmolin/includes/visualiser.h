/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmolin <gmolin@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:46:42 by gmolin            #+#    #+#             */
/*   Updated: 2020/02/06 15:41:33 by gmolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALISER_H
# define VISUALISER_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include "../../libftprintf/libft/includes/libft.h"
# include "../../libftprintf/ft_printf/includes/ft_printf.h"
# include "../../includes/filler.h"
# define WIDTH 1200
# define HEIGHT 600
# define ECHAP	53
# define WINDOW_NAME "DRAGON SLAYER ARENA"

typedef struct		s_env
{
	char			*p1;
	char			*p2;
	float			scorep1;
	float			scorep2;
	char			**map;
	int				height;
	int				width;
	int				red;
	int				green;
	int				blue;
	int				map_size_x;
	int				map_size_y;
	char			*ret;
	void			*ret2;
	void			*win;
	void			*mlx;
	void			*img;
	void			*img2;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				pause;
}					t_env;

/*
** ------ MAIN.C ------
*/

int					main(void);
void				init_env(t_env *p);
int					mouse_hook(int button, int x, int y, t_env *p);
int					key_hook(int keycode, t_env *p);

/*
** ------ INPUT_SCAN.C ------
*/

void				input_scan(t_env *p);
void				fetch_map_size(char *line, t_env *p);
void				fetch_map(t_env *p);
void				fetch_player_name(char *line, t_env *p);

/*
** ------ DRAWING_MODE.C ------
*/

void				draw_mode(t_env *p);
void				draw_background(t_env *p);
void				draw_menu(t_env *p);
void				draw_score(t_env *p);
void				draw_map(t_env *p);

/*
** ------ DRAWING_MODE_2.C ------
*/

void				draw_title(t_env *p);
void				draw_square(int start_x, int start_y, int size, t_env *p);
void				draw_rectangle(int start_x, int start_y, t_env *p);
void				draw_rectangle2(int start_x, int start_y, t_env *p);

/*
** ------ TOOLS.C ------
*/

int					is_aly_adj(t_env *p, int i, int i2);
void				print_final(t_env *p);
int					is_number(char c);
void				modif_color(int r, int v, int b, t_env *p);
void				calc_score(t_env *p);

#endif
