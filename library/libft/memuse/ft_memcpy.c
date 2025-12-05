/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:18:30 by aeherve           #+#    #+#             */
/*   Updated: 2025/11/26 19:59:08 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int				i;
	unsigned char	*src_tmp;

	i = 0;
	if (!dest && !src)
		return (NULL);
	src_tmp = (unsigned char *)src;
	while (i < (int)n)
	{
		ft_memset(dest, src_tmp[i], 1);
		dest++;
		i++;
	}
	return (dest - n);
}
