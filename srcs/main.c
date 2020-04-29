/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 09:49:09 by tlouekar          #+#    #+#             */
/*   Updated: 2020/04/29 13:53:45 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/filler.h"

int			main(void)
{
    char    *line;

    line = NULL;
    write(1, "X\n", 2);
    if (get_next_line(0, &line))
    {
        //printf("Read something!");
        ft_putstr("12 13\n");
    }
    else
        printf("Did not read anything.");
    return (0);
}