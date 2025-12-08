/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:08:48 by dadoune           #+#    #+#             */
/*   Updated: 2025/12/08 18:15:33 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_putnbr_unsigned_fd(unsigned int n, int fd)
{
	int	i;

	if (n < 10)
	{
		i = '0' + n;
		write(fd, &i, 1);
		return (1);
	}
	else
		return (ft_putnbr_unsigned_fd(n / 10, fd) + \
		ft_putnbr_unsigned_fd(n % 10, fd));
}
