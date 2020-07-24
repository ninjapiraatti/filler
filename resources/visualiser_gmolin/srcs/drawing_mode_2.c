/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_mode_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmolin <gmolin@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:28:22 by gmolin            #+#    #+#             */
/*   Updated: 2020/02/10 09:43:15 by gmolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualiser.h"

void		draw_square(int start_x, int start_y, int size, t_env *p)
{
	int		i;
	int		i2;
	int		tmp;

	i2 = 0;
	tmp = 0;
	while (i2 < (size * 4))
	{
		i = 0;
		while (i < (size * 4))
		{
			p->ret[i + tmp + ((start_y * WIDTH * 4) +
				(start_x * 4))] = p->red;
			p->ret[i + tmp + 1 + ((start_y * WIDTH * 4) +
				(start_x * 4))] = p->green;
			p->ret[i + tmp + 2 + ((start_y * WIDTH * 4) +
				(start_x * 4))] = p->blue;
			p->ret[i + tmp + 3 + ((start_y * WIDTH * 4) +
				(start_x * 4))] = 0;
			i += 4;
		}
		i2 += 4;
		tmp += (WIDTH * 4);
	}
}

void		draw_rectangle(int x, int y, t_env *p)
{
	int		i;
	int		i2;
	int		t;

	i2 = 0;
	t = 0;
	while (i2 < (p->height * 4))
	{
		i = 0;
		while (i < (p->width * 4))
		{
			p->ret[i + t + ((y * WIDTH * 4) + (x * 4))] = p->red;
			p->ret[i + t + 1 + ((y * WIDTH * 4) + (x * 4))] = p->green;
			p->ret[i + t + 2 + ((y * WIDTH * 4) + (x * 4))] = p->blue;
			p->ret[i + t + 3 + ((y * WIDTH * 4) + (x * 4))] = 0;
			i += 4;
		}
		i2 += 4;
		t += (WIDTH * 4);
	}
}

void		draw_rectangle2(int x, int y, t_env *p)
{
	int		i;
	int		i2;
	int		t;

	i2 = 0;
	t = 0;
	while (i2 < (p->height * 4))
	{
		i = 0;
		while (i < (p->width * 4))
		{
			p->ret[i + t + ((y * WIDTH * 4) + (x * 4))] = p->red;
			p->ret[i + t + 1 + ((y * WIDTH * 4) + (x * 4))] = p->green;
			p->ret[i + t + 2 + ((y * WIDTH * 4) + (x * 4))] = p->blue;
			p->ret[i + t + 3 + ((y * WIDTH * 4) + (x * 4))] = 0;
			i += 4;
		}
		y -= 3;
		i2 += 4;
		t += (WIDTH * 4);
	}
}
