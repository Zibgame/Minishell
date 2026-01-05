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

static int	ft_check_flags(const char *s, int fd, va_list p_args, int *index)
{
	char	c;

	if (s[++(*index)])
	{
		if (s[*index] == 'c')
		{
			c = va_arg(p_args, int);
			write(1, &c, 1);
		}
		else if (s[*index] == 's')
			return (ft_putstr_fd(va_arg(p_args, char *), fd));
		else if (s[*index] == 'p')
			return (ft_putptr_fd(va_arg(p_args, void *), fd));
		else if (s[*index] == 'd' || s[*index] == 'i')
			return (ft_putnbr_fd(va_arg(p_args, int), fd));
		else if (s[*index] == 'u')
			return (ft_putnbr_unsigned_fd(va_arg(p_args, unsigned int), fd));
		else if (s[*index] == 'x' || s[*index] == 'X')
			return (ft_puthex_fd(va_arg(p_args, int), (s[*index] == 'X'), fd));
		else if (s[*index] == '%')
			write(1, "%", 1);
		return (1);
	}
	(*index)++;
	return (0);
}

int	ft_printf_fd(const char *str, int fd, ...)
{
	int		i;
	int		p_len;
	va_list	p_args;

	if (!str)
		return (0);
	i = 0;
	p_len = 0;
	va_start(p_args, fd);
	while (str[i])
	{
		if (str[i] == '%')
		{
			p_len += ft_check_flags(str, fd, p_args, &i);
			i++;
		}
		else
		{
			write(fd, &str[i], 1);
			i++;
			p_len++;
		}
	}
	va_end(p_args);
	return (p_len);
}
