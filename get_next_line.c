/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 13:56:19 by jszabo            #+#    #+#             */
/*   Updated: 2018/01/23 16:31:50 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "./libft/libft.h"
#include <stdio.h>

static char	*ft_read_file(const int fd, char *str, int *end)
{
	int size;

	size = 0;
	if (!(size = read(fd, str, BUFF_SIZE)))
		*end = 1;
	str[size] = '\0';
	return (str);
}

static char	*ft_store_line(const int fd, char *str, int *end, int *i)
{
	char	*new;
	char	*saved;
	int		j;

	j = 0;
	if (!(new = ft_strnew(BUFF_SIZE)))
		return (NULL);
	while (str[j] != '\n' && !*end)
	{
		j++;
		if (!str[j])
		{
			new = ft_read_file(fd, new, end);
			if (!(saved = ft_strjoin(str, new)))
				return (NULL);
			ft_strdel(&str);
			str = ft_strnew(ft_strlen(saved));
			str = ft_strcpy(str, saved);
			ft_strdel(&saved);
		}
	}
	ft_strdel(&new);
	*i = 0;
	while (!(*end) && str[*i] != '\n')
		(*i)++;
	return (str);
}

static int	str_mod(char **line, int i, char **str)
{
	if (!(*line = ft_strnew(i)))
		return (0);
	*line = ft_strncpy(*line, *str, i);
	*str = (char *)ft_memmove
(*str, (*str) + i + 1, ft_strlen(*str) - i + 1);
	return (1);
}

static int	getline_final(char **line, char **str)
{
	*line = NULL;
	ft_strdel(str);
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char	*str;
	int			end;
	int			i;

	end = 0;
	ERROR(BUFF_SIZE < 1 || fd < 0 || line == NULL);
	if (str && str[0] == '\0')
		ft_strdel(&str);
	if (!str)
	{
		ERROR(!(str = ft_strnew(BUFF_SIZE)));
		str = ft_read_file(fd, str, &end);
		ERROR(!str[0] && !end);
		if (end)
			return (getline_final(line, &str));
	}
	ERROR(!(str = ft_store_line(fd, str, &end, &i)) ||
((!end) && !(str_mod(line, i, &str))));
	if (end)
	{
		*line = ft_strnew(ft_strlen(str));
		*line = ft_strcpy(*line, str);
		ft_strdel(&str);
	}
	return (1);
}

// modify for list
// continously check
// norm..
// ...DONE!
