/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:40:36 by tlouekar          #+#    #+#             */
/*   Updated: 2019/12/02 09:20:24 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		strsize;
	int		i;

	strsize = ft_strlen((char *)s1);
	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * strsize + 1)))
		return (NULL);
	while (i < strsize)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
