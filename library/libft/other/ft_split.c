/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 09:18:08 by aeherve           #+#    #+#             */
/*   Updated: 2025/12/10 17:33:39 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	**free_sep(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static size_t	count_words(const char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == sep))
			i++;
		if (str[i])
			count++;
		while (str[i] && !(str[i] == sep))
			i++;
	}
	return (count);
}

static void	next_word(char **word_ptr, size_t *size, char c)
{
	size_t	i;

	*word_ptr += *size;
	*size = 0;
	i = 0;
	while (**word_ptr && **word_ptr == c)
		(*word_ptr)++;
	while ((*word_ptr)[i])
	{
		if ((*word_ptr)[i] == c)
			return ;
		(*size)++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**sep;
	char	*temp;
	size_t	len_temp;
	size_t	i;

	if (!s)
		return (NULL);
	sep = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!sep)
		return (NULL);
	i = 0;
	temp = (char *)s;
	len_temp = 0;
	while (i < count_words(s, c))
	{
		next_word(&temp, &len_temp, c);
		sep[i] = (char *)malloc(sizeof(char) * (len_temp + 1));
		if (!sep[i])
			return (free_sep(sep));
		ft_strlcpy(sep[i], temp, len_temp + 1);
		i++;
	}
	sep[i] = NULL;
	return (sep);
}
