/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:09:27 by dadoune           #+#    #+#             */
/*   Updated: 2025/11/26 20:23:12 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_putnbr_hex(unsigned int n, int maj)
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
		return (ft_putnbr_hex(n / 16, maj) + ft_putnbr_hex(n % 16, maj));
}
