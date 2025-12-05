/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:55:23 by aeherve           #+#    #+#             */
/*   Updated: 2025/11/26 20:00:35 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	s += i;
	if (c == '\0')
		return ((char *)s);
	while (i >= 0)
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		i--;
		s--;
	}
	return (NULL);
}
