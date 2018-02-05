/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:04:53 by jszabo            #+#    #+#             */
/*   Updated: 2018/02/05 15:58:22 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int         main(int argc, char **argv)
{
    char    *line;
    int     fd;
	int		fd2;
    int     i;

    i = 0;

    if (argc != 3)
        return (0);
    fd = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
   while (i < 7)
    {
        printf("%d\n", get_next_line(fd, &line));
        printf("%s\n", line);
		free(line);
		printf("%d\n", get_next_line(fd2, &line));
        printf("%s\n", line);
		free(line);
        i++;
    }
	sleep(5);
    return (0);
}
