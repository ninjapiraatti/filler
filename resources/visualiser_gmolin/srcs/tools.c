/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmolin <gmolin@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 15:42:27 by lcharvol          #+#    #+#             */
/*   Updated: 2020/02/10 09:52:19 by gmolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualiser.h"

int			is_aly_adj(t_env *p, int i, int i2)
{
	if (i2 + 1 >= p->map_size_x || i2 - 1 < 0 || i + 1 >= p->map_size_y
		|| i - 1 < 0)
		return (0);
	if (p->map[i][i2 + 1] == 'X' || p->map[i][i2 - 1] == 'X' ||
		p->map[i][i2 + 1] == 'O' || p->map[i][i2 - 1] == 'O')
		return (1);
	if (p->map[i + 1][i2] == 'X' || p->map[i - 1][i2] == 'X' ||
		p->map[i + 1][i2] == 'O' || p->map[i - 1][i2] == 'O')
		return (1);
	if (i2 + 2 >= p->map_size_x || i2 - 2 < 0 || i + 2 >= p->map_size_y
		|| i - 2 < 0)
		return (0);
	if (p->map[i][i2 + 2] == 'X' || p->map[i][i2 - 2] == 'X' ||
		p->map[i][i2 + 2] == 'O' || p->map[i][i2 - 2] == 'O')
		return (2);
	if (p->map[i + 2][i2] == 'X' || p->map[i - 2][i2] == 'X' ||
		p->map[i + 2][i2] == 'O' || p->map[i - 2][i2] == 'O')
		return (2);
	return (0);
}

void		calc_score(t_env *p)
{
	int		i;
	int		i2;

	i = 0;
	p->scorep1 = 0;
	p->scorep2 = 0;
	while (i < p->map_size_y)
	{
		i2 = 0;
		while (i2 < p->map_size_x)
		{
			if (p->map[i][i2] == 'X' || p->map[i][i2] == 'x')
				p->scorep1 += 1;
			if (p->map[i][i2] == 'O' || p->map[i][i2] == 'o')
				p->scorep2 += 1;
			i2++;
		}
		i++;
	}
}

void		modif_color(int red, int green, int blue, t_env *p)
{
	p->red = red;
	p->green = green;
	p->blue = blue;
}

void		print_final(t_env *p)
{
	char	*str;

	str = ft_itoa(p->scorep1);
	mlx_string_put(p->mlx, p->win, (WIDTH / 2) + 390, (HEIGHT / 2) + 145,
		0xFFFFFFF, str);
	str = ft_itoa(p->scorep2);
	mlx_string_put(p->mlx, p->win, (WIDTH / 2) + 180, (HEIGHT / 2) + 145,
		0xFFFFFFF, str);
	str = p->p2;
	mlx_string_put(p->mlx, p->win, (WIDTH / 2) + 330, (HEIGHT / 2) + 175,
		0xb176ed, str);
	str = p->p1;
	mlx_string_put(p->mlx, p->win, (WIDTH / 2) + 120, (HEIGHT / 2) + 175,
		0x67E8BA, str);
}
