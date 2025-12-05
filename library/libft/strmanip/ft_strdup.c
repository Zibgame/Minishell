/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:37:44 by aeherve           #+#    #+#             */
/*   Updated: 2025/11/26 20:00:03 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	char	*duped;

	duped = malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!duped)
		return (NULL);
	ft_strlcpy(duped, s, ft_strlen(s)+1);
	return (duped);
}
