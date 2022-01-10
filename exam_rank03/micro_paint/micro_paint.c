/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:45:46 by cdapurif          #+#    #+#             */
/*   Updated: 2022/01/10 19:17:32 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct s_info
{
	int	width;
	int	height;
	char	background;
}		t_info;

typedef struct s_rect
{
	char	full;
	float	x;
	float	y;
	float	width;
	float	height;
	char	c;
}		t_rect;

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

char	*create_map()

int	micro_paint(char *path)
{
	int	ret;
	FILE	*file;

	file = fopen(path, "r");
	if (!file)
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}
	if ((ret = fscanf(file, "%d %d %c\n", &s->widht, &s->height, &s->background)) != 3)
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}
	map = create_map;
	/*while ((ret = fscanf(file, "", &, )) == 6)
	{

	}*/

	return (0);
}

int	main(int ac, char **av)
{
	int	ret;

	ret = 0;
	if (ac == 2)
		ret = micro_paint(av + 1);
	else
	{
		ft_putstr("Error: argument\n");
		return (1);
	}
	return (ret);
}
