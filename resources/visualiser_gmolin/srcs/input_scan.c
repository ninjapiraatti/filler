/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_scan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmolin <gmolin@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:24:13 by gmolin            #+#    #+#             */
/*   Updated: 2020/02/10 09:47:36 by gmolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualiser.h"

void			fetch_player_name(char *line, t_env *p)
{
	int		i;

	i = 22;
	if (line[9] == 'p' && line[10] == '1')
	{
		while (line[i])
		{
			if (line[i] == '.')
				break ;
			i++;
		}
		p->p1 = ft_strsub((const char *)line, 23, i - 23);
	}
	if (line[9] == 'p' && line[10] == '2')
	{
		while (line[i])
		{
			if (line[i] == '.')
				break ;
			i++;
		}
		p->p2 = ft_strsub((const char *)line, 23, i - 23);
	}
	ft_strdel(&line);
}

void			fetch_map(t_env *p)
{
	int		k;
	char	*line;

	k = 0;
	ft_get_next_line(0, &line);
	ft_strdel(&line);
	p->map = (char**)malloc(sizeof(char*) * p->map_size_y + 1);
	while (k < p->map_size_y && ft_get_next_line(0, &line) == 1)
	{
		p->map[k] = ft_strdup((const char*)&line[4]);
		ft_strdel(&line);
		k++;
	}
	p->map[k] = NULL;
}

void			fetch_map_size(char *line, t_env *p)
{
	int		i;

	p->map_size_x = 0;
	p->map_size_y = 0;
	p->map_size_y = ft_atoi(&line[8]);
	i = 8 + ft_len(p->map_size_y);
	p->map_size_x = ft_atoi(&line[i]);
	ft_strdel(&line);
	fetch_map(p);
}

void			input_scan(t_env *p)
{
	char *line;

	while (ft_get_next_line(0, &line) == 1)
	{
		if (ft_strncmp(line, "$$$", 2) == 0)
			fetch_player_name(line, p);
		if (ft_strncmp(line, "Plateau", 6) == 0)
			fetch_map_size(line, p);
		if (ft_strncmp(line, "Piece", 4) == 0)
		{
			ft_strdel(&line);
			return ;
		}
	}
}
