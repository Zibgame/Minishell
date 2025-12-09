/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:37:44 by aeherve           #+#    #+#             */
/*   Updated: 2025/12/09 16:33:54 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	char	*duped;

	if (!s)
		return (NULL);
	duped = malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!duped)
		return (NULL);
	ft_strlcpy(duped, s, ft_strlen(s)+1);
	return (duped);
}

char	*ft_strndup(const char *s, int n)
{
	char	*duped;

	if (!s)
		return (NULL);
	duped = malloc(n * sizeof(char) + 1);
	if (!duped)
		return (NULL);
	ft_strlcpy(duped, s, n);
	duped[n] = '\0';
	return (duped);
}