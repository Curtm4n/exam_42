/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:45:46 by cdapurif          #+#    #+#             */
/*   Updated: 2022/01/11 00:06:55 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct	s_info
{
	int		width;
	int		height;
	char	background;
}				t_info;

typedef struct	s_rect
{
	char	fill;
	float	x;
	float	y;
	float	width;
	float	height;
	char	c;
}				t_rect;

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

char	*create_map(t_info *info)
{
	char	*str;
	int		i;
	int		size;

	size = info->width * info->height;
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	str[size] = '\0';
	i = -1;
	while (++i < size)
		str[i] = info->background;
	return (str);
}

int	ret_error(FILE *file, int close)
{
	ft_putstr("Error: Operation file corrupted\n");
	if (close)
		fclose(file);
	return (1);
}

void	display_map(t_info *info, char *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < info->height)
	{
		write(1, map + (i * info->width), info->width);
		write(1, "\n", 1);
	}
}

int	read_lines(t_info *info, FILE *file, char *map)
{
	t_rect r;
	int	ret;

	while ((ret = fscanf(file, "%c %f %f %f %f %c\n", &r.fill, &r.x, &r.y, \
		&r.width, &r.height, &r.c)) == 6)
	{
		printf("line\n");
	}
	if (ret != 6 && ret != -1)
		return (1);
	return (0);
}

int	micro_paint(char *path)
{
	int		ret;
	FILE	*file;
	t_info	info;
	char	*map;

	file = fopen(path, "r");
	if (!file)
		return (ret_error(file, 0));
	if ((ret = fscanf(file, "%d %d %c\n", \
		&info.width, &info.height, &info.background)) != 3)
		return (ret_error(file, 1));
	if (info.width <= 0 || info.width > 300 || info.height <= 0 || \
		info.height > 300)
		return (ret_error(file, 1));
	map = create_map(&info);
	if (!map)
		return (ret_error(file, 1));
	if (read_lines(&info, file, map)) //ici
	{
		free(map);
		return (ret_error(file, 1));
	}
	display_map(&info, map);
	fclose(file);
	free(map);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr("Error: argument\n");
		return (1);
	}
	return (micro_paint(av[1]));
}
