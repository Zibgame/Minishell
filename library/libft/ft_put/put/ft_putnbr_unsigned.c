/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:08:48 by dadoune           #+#    #+#             */
/*   Updated: 2025/12/08 17:12:33 by aeherve          ###   ########.fr       */
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
		return (ft_putnbr_unsigned(n / 10) + ft_putnbr_unsigned(n % 10));
}
