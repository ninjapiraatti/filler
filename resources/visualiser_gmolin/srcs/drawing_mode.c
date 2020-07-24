/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:28:22 by gmolin            #+#    #+#             */
/*   Updated: 2020/06/30 14:19:29 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualiser.h"

void		draw_background(t_env *p)
{
	int		i;

	i = 0;
	while (i < (HEIGHT * WIDTH * 4))
	{
		(p->ret)[i] = 52;
		(p->ret)[i + 1] = 52;
		(p->ret)[i + 2] = 52;
		(p->ret)[i + 3] = 0;
		i += 4;
	}
}

void		draw_menu(t_env *p)
{
	int		width;

	width = WIDTH;
	p->red = 24;
	p->green = 24;
	p->blue = 24;
	p->width = 50;
	p->height = HEIGHT;
	draw_rectangle(WIDTH / 2, 0, p);
	draw_rectangle(WIDTH - p->width, 0, p);
	p->width = WIDTH;
	p->height = 50;
	draw_rectangle(0, 0, p);
	draw_rectangle(0, HEIGHT - p->height, p);
	p->width = WIDTH / 2;
	p->height = HEIGHT;
	draw_rectangle(0, 0, p);
}

void		draw_score(t_env *p)
{
	char	*str;

	calc_score(p);
	modif_color(244, 146, 166, p);
	p->width = 150;
	p->height = ((HEIGHT / 3) * (p->scorep1 / (p->map_size_x * p->map_size_y)));
	draw_rectangle2((WIDTH / 2) + 330, (HEIGHT / 2) + 170, p);
	modif_color(103, 244, 205, p);
	p->width = 150;
	p->height = ((HEIGHT / 3) * (p->scorep2 / (p->map_size_x * p->map_size_y)));
	draw_rectangle2((WIDTH / 2) + 120, (HEIGHT / 2) + 170, p);
}

void		draw_map(t_env *p)
{
	int		i;
	int		i2;
	int		s;

	s = ((WIDTH / 2) / (p->map_size_x)) - 2;
	i = -1;
	while (++i < p->map_size_y)
	{
		i2 = -1;
		while (++i2 < p->map_size_x)
		{
			if (p->map[i][i2] == '.' && is_aly_adj(p, i, i2) == 2)
				modif_color(50, 50, 50, p);
			else if (p->map[i][i2] == '.' && is_aly_adj(p, i, i2) == 1)
				modif_color(0, 0, 0, p);
			else if (p->map[i][i2] == '.')
				modif_color(0, 0, 0, p);
			else if (p->map[i][i2] == 'X')
				modif_color(244, 146, 166, p);
			else if (p->map[i][i2] == 'O')
				modif_color(103, 244, 205, p);
			else if (p->map[i][i2] == 'x')
				modif_color(0, 0, 255, p);
			else if (p->map[i][i2] == 'o')
				modif_color(255, 0, 0, p);
			draw_square((i2 * s) + (i2 * 2) + 2, (i * s) + (i * 2) +
				((600 - (p->map_size_y * s) - (p->map_size_y * 2)) / 2), s, p);
		}
	}
}

void		draw_mode(t_env *p)
{
	draw_background(p);
	draw_menu(p);
	draw_score(p);
	draw_map(p);
}
