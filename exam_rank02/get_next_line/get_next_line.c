/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:33:20 by cdapurif          #+#    #+#             */
/*   Updated: 2020/03/07 11:39:03 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		check_line(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			return (i);
	return (-1);
}

int		get_line(char *buffer, char **line)
{
	int i;
	int j;

	i = -1;
	while (buffer[++i])
		if (buffer[i] == '\n')
			break ;
	buffer[i] = '\0';
	if ((*line = malloc(i + 1)) == NULL)
		return (-1);
	j = -1;
	while (++j <= i)
		(*line)[j] = buffer[j];
	j = 0;
	while (buffer[++i])
	{
		buffer[j] = buffer[i];
		j++;
	}
	buffer[j] = '\0';
	return (1);
}

char	*ft_strdup(char *buffer)
{
	char	*ret;
	int		i;

	i = 0;
	while (buffer[i])
		i++;
	if ((ret = malloc(i + 1)) == NULL)
		return (NULL);
	i = -1;
	while (buffer[++i])
		ret[i] = buffer[i];
	ret[i] = '\0';
	buffer = NULL;
	return(ret);
}

char	*ft_strjoin(char *s1, char *s2, int cond)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (s1)
		i = ft_strlen(s1);
	if ((str = malloc(i + ft_strlen(s2) + 1)) == NULL)
		return (NULL);
	if (s1)
	{
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
	}
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	if (s1)
		free(s1);
	if (cond)
		free(s2);
	return (str);
}

int		read_line(char *buffer, char **line)
{
	char	*str;
	int		ret;

	str = NULL;
	if (buffer && buffer[0] != '\0')
		if ((str = ft_strdup(buffer)) == NULL)
			return (-1);
	while ((ret = read(0, buffer, 127)) > 0)
	{
		buffer[ret] = '\0';
		if (check_line(buffer) != -1)
		{
			if (get_line(buffer, line) == -1)
				return (-1);
			if (str)
				if ((*line = ft_strjoin(str, *line, 1)) == NULL)
					return (-1);
			return (1);
		}
		if ((str = ft_strjoin(str, buffer, 0)) == NULL)
			return (-1);
	}
	*line = str;
	return (ret);
}

int		get_next_line(char **line)
{
	static char buffer[128];
	int			ret;

	if (!line)
		return (-1);
	if (check_line(buffer) != -1)
		return (get_line(buffer, line));
	if ((ret = read_line(buffer, line)) == -1)
		return (-1);
	if (*line == NULL)
	{
		if ((*line = malloc(1)) == NULL)
			return (-1);
		*line[0] = '\0';
	}
	if (ret == 0)
		buffer[0] = '\0';
	return (ret);
}
