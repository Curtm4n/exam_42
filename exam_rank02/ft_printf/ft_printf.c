/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 12:42:21 by cdapurif          #+#    #+#             */
/*   Updated: 2020/03/06 13:42:52 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct	s_struct
{
	int	nb_char;
	long long width;
	long long precision;
}				t_struct;

void	reset_struct(t_struct *data)
{
	data->width = 0;
	data->precision = -1;
}

long long	ft_atoi(char *str)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

long long	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long long	ft_nbrlen(long long nbr)
{
	int cpt;

	cpt = 1;
	if (nbr < 0)
		nbr = - nbr;
	while (nbr > 9)
	{
		nbr /= 10;
		cpt++;
	}
	return (cpt);
}

long long	ft_hexlen(long long nbr)
{
	int cpt;

	cpt = 1;
	if (nbr < 0)
		nbr = - nbr;
	while (nbr > 15)
	{
		nbr /= 16;
		cpt++;
	}
	return (cpt);
}

void	ft_putstr(char *str, int len)
{
	int i;

	i = -1;
	while (str[++i] && i < len)
		write(1, &str[i], 1);
}

void	ft_putnbr(long long nbr)
{
	char n;

	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr > 9)
		ft_putnbr(nbr / 10);
	n = nbr % 10 + '0';
	write(1, &n, 1);
}

void	ft_puthex(long long nbr)
{
	char n;

	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr > 15)
		ft_puthex(nbr / 16);
	if (nbr % 16 < 10)
		n = nbr % 16 + '0';
	else
		n = nbr % 16 + 87;
	write(1, &n, 1);
}

int		ft_write_basics(t_struct *data, char *format)
{
	int i;

	i = 0;
	while (format[i] && format[i] != '%')
		i++;
	write(1, format, i);
	data->nb_char += i;
	return (i);
}

char	*ft_width(t_struct *data, char *format)
{
	if (*format >= '0' && *format <= '9')
		data->width = ft_atoi(format);
	while (*format >= '0' && *format <= '9')
		format++;
	return (format);
}

char	*ft_precision(t_struct *data, char *format)
{
	if (*format == '.')
	{
		format++;
		if (*format >= '0' && *format <= '9')
			data->precision = ft_atoi(format);
		while (*format >= '0' && *format <= '9')
			format++;
	}
	return (format);
}

void	place_sep(int len)
{
	int i;

	i = -1;
	while (++i < len)
		write(1, " ", 1);
}

void	place_pre(int len)
{
	int i;

	i = -1;
	while (++i < len)
		write(1, "0", 1);
}

void	ft_print_string(t_struct *data, va_list args)
{
	long long	len;
	char		*str;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (data->precision > -1)
		len = (data->precision < len) ? data->precision : len;
	place_sep(data->width - len);
	ft_putstr(str, len);
	len = (data->width > len) ? data->width : len;
	data->nb_char += len;
}

void	ft_print_int(t_struct *data, va_list args)
{
	long long len;
	long long nbr;

	nbr = va_arg(args, int);
	len = ft_nbrlen(nbr);
	if (data->precision > -1)
		len = (data->precision > len) ? data->precision : len;
	if (nbr < 0)
		len++;
	place_sep(data->width - len);
	if (nbr < 0)
		write(1, "-", 1);
	place_pre(data->precision - ft_nbrlen(nbr));
	if (nbr < 0)
		nbr = -nbr;
	ft_putnbr(nbr);
	len = (data->width > len) ? data->width : len;
	data->nb_char += len;
}

void	ft_print_hex(t_struct *data, va_list args)
{
	long long len;
	long long nbr;

	nbr = va_arg(args, unsigned int);
	len = ft_hexlen(nbr);
	if (data->precision > -1)
		len = (data->precision > len) ? data->precision : len;
	place_sep(data->width - len);
	place_pre(data->precision - ft_hexlen(nbr));
	ft_puthex(nbr);
	len = (data->width > len) ? data->width : len;
	data->nb_char += len;
}

char	*ft_pars_specifier(t_struct *data, va_list args, char *format)
{
	format++;
	reset_struct(data);
	format = ft_width(data, format);
	format = ft_precision(data, format);
	if (*format == 's' || *format == 'd' || *format == 'x')
	{
		if (*format == 's')
			ft_print_string(data, args);
		if (*format == 'd')
			ft_print_int(data, args);
		if (*format == 'x')
			ft_print_hex(data, args);
		format++;
	}
	return (format);
}

int		ft_printf(char *format, ...)
{
	va_list		args;
	t_struct	data;

	va_start(args, format);
	data.nb_char = 0;
	while (*format)
	{
		if (*format != '%')
			format += ft_write_basics(&data, format);
		if (*format == '%')
			format = ft_pars_specifier(&data, args, format);
	}
	va_end(args);
	return (data.nb_char);
}
