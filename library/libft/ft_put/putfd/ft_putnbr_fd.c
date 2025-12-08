/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:25:33 by aeherve           #+#    #+#             */
/*   Updated: 2025/12/08 16:40:16 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int	i;
	int	j;

	j = 0;
	if (n < 0)
	{
		write(fd, "-", 1);
		j = 1;
		if (n == -2147483648)
		{
			write(fd, "2147483648", 10);
			return (11);
		}
		else
			n *= -1;
	}
	if (n < 10)
	{
		i = '0' + n;
		write(fd, &i, 1);
		return (j + 1);
	}
	else
		return (j + ft_putnbr(n / 10) + ft_putnbr(n % 10));
}
