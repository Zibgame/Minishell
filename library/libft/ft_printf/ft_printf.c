/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 20:25:10 by aeherve           #+#    #+#             */
/*   Updated: 2025/10/23 20:25:10 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_check_flags(const char *str, va_list p_args, int *index)
{
	char	c;

	if (str[++(*index)])
	{
		if (str[*index] == 'c')
		{
			c = va_arg(p_args, int);
			write(1, &c, 1);
		}
		else if (str[*index] == 's')
			return (ft_putstr(va_arg(p_args, char *)));
		else if (str[*index] == 'p')
			return (ft_putptr(va_arg(p_args, void *)));
		else if (str[*index] == 'd' || str[*index] == 'i')
			return (ft_putnbr(va_arg(p_args, int)));
		else if (str[*index] == 'u')
			return (ft_putnbr_unsigned(va_arg(p_args, unsigned int)));
		else if (str[*index] == 'x' || str[*index] == 'X')
			return (ft_putnbr_hex(va_arg(p_args, int), (str[*index] == 'X')));
		else if (str[*index] == '%')
			write(1, "%", 1);
		return (1);
	}
	(*index)++;
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		p_len;
	va_list	p_args;

	if (!str)
		return (0);
	i = 0;
	p_len = 0;
	va_start(p_args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			p_len += ft_check_flags(str, p_args, &i);
			i++;
		}
		else
		{
			write(1, &str[i], 1);
			i++;
			p_len++;
		}
	}
	va_end(p_args);
	return (p_len);
}

// int	main(void)
// {
// 	ft_printf("je t%ec %ce %s ce pointeur est %p",'e', "montre", NULL, 'l');
// }