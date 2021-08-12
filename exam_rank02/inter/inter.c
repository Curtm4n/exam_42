/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 11:37:24 by cdapurif          #+#    #+#             */
/*   Updated: 2020/03/06 11:48:20 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

void	ft_remove_double(char *str)
{
	int i;
	int j;
	int	found;

	i = -1;
	while (str[++i])
	{
		found = 0;
		j = i;
		while (--j >= 0)
			if (str[j] == str[i])
				found = 1;
		if (!found)
			write(1, &str[i], 1);
	}
}

void	ft_inter(char *s1, char *s2)
{
	int i;
	int j;
	int k;
	char str[ft_strlen(s1) + ft_strlen(s2) + 1];

	i = -1;
	k = 0;
	while (s1[++i])
	{
		j = -1;
		while (s2[++j])
			if (s1[i] == s2[j])
			{
				str[k] = s1[i];
				k++;
			}
	}
	str[k] = '\0';
	ft_remove_double(str);
	write(1, "\n", 1);
}

int		main(int ac, char **av)
{
	if (ac != 3)
		write(1, "\n", 1);
	else
		ft_inter(av[1], av[2]);
	return (0);
}
