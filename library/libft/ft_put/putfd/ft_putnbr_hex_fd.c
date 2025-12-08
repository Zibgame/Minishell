/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:09:27 by dadoune           #+#    #+#             */
/*   Updated: 2025/12/08 18:14:49 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_puthex_fd(unsigned int n, int maj, int fd)
{
	char	c;

	if (n < 16)
	{
		if (maj == 0)
			c = "0123456789abcdef"[n];
		else
			c = "0123456789ABCDEF"[n];
		write(fd, &c, 1);
		return (1);
	}
	else
		return (ft_puthex_fd(n / 16, maj, fd) + ft_puthex_fd(n % 16, maj, fd));
}
