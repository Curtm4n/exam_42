/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <cdapurif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:36:34 by cdapurif          #+#    #+#             */
/*   Updated: 2021/12/16 11:30:24 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

#include <stdio.h>

typedef struct s_data
{
	int len;
}				t_data;

const char	*write_basic(const char	*str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '%')
		i++;
	write(1, str, i);
	data->len += i;
	return (str + i);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

void	print_string(const char *str, va_list args, t_data *data)
{
	char	*ret;

	ret = va_arg(args, char *);
	if (!ret)
		ret = "(null)";
	data->len += ft_strlen(ret);
	ft_putstr(ret);
}

int	ft_nblen(int nb)
{
	int i;

	i = 1;
	if (nb < 0)
	{
		i++;
		nb = -nb;
	}
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

int	ft_putnbr(int nb)
{
	char		c;
	long long	nbr;

	nbr = nb;
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr > 9)
		ft_putnbr(nbr / 10);
	c = nbr % 10 + '0';
	write(1, &c, 1);
}

void	print_int(const char *str, va_list args, t_data *data)
{
	int	nb;

	nb = va_arg(args, int);
	data->len += ft_nblen(nb);
	ft_putnbr(nb);
}

int	ft_hexlen(unsigned int nb)
{
	int	i;

	i = 1;
	while (nb > 15)
	{
		nb /= 16;
		i++;
	}
	return (i);
}

void	ft_puthex(unsigned int nb)
{
	char c;

	if (nb > 15)
		ft_puthex(nb / 16);
	if (nb % 16 > 9)
		c = nb % 16 + 87;
	else
		c = nb % 16 + '0';
	write(1, &c, 1);
}

void	print_hex(const char *str, va_list args, t_data *data)
{
	unsigned int nb;

	nb = va_arg(args, unsigned int);
	data->len += ft_hexlen(nb);
	ft_puthex(nb);
}

const char	*parsing(const char *str, va_list args, t_data *data)
{
	str++;
	if (*str == 's' || *str == 'd' || *str == 'x')
	{
		if (*str == 's')
			print_string(str, args, data);
		if (*str == 'd')
			print_int(str, args, data);
		if (*str == 'x')
			print_hex(str, args, data);
		str++;
	}
	else if (*str == '%')
	{
		write(1, "%", 1);
		str++;
		data->len++;
	}
	return (str);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	t_data	data;

	data.len = 0;
	if (str)
	{
		va_start(args, str);
		while (*str)
		{
			if (*str != '%')
				str = write_basic(str, &data);
			else
				str = parsing(str, args, &data);
		}
		va_end(args);
	}
	return (data.len);
}

int	main(void)
{
	int ret;

	ret = ft_printf("Magic %s is %d hexa : %x\n", "number", 42, 42);
	printf("mon printf: %d\n", ret);
	ret = printf("Magic %s is %d hexa : %x\n", "number", 42, 42);
	printf("le printf: %d\n", ret);
	return (0);
}
