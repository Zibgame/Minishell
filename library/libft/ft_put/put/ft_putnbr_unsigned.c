/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:08:48 by dadoune           #+#    #+#             */
/*   Updated: 2025/11/26 20:23:20 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_putnbr_unsigned(unsigned int n)
{
	int	i;

	if (n < 10)
	{
		i = '0' + n;
		write(1, &i, 1);
		return (1);
	}
	else
		return (ft_putnbr(n / 10) + ft_putnbr(n % 10));
}
