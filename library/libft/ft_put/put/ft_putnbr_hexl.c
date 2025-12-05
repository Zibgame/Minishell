/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 20:28:26 by aeherve           #+#    #+#             */
/*   Updated: 2025/10/23 20:28:26 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_putnbr_hexl(unsigned long n, int maj)
{
	char	c;

	if (n < 16)
	{
		if (maj == 0)
			c = "0123456789abcdef"[n];
		else
			c = "0123456789ABCDEF"[n];
		write(1, &c, 1);
		return (1);
	}
	else
		return (ft_putnbr_hexl(n / 16, maj) + ft_putnbr_hexl(n % 16, maj));
}
