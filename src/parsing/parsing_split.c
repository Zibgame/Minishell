/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:32:07 by dadoune           #+#    #+#             */
/*   Updated: 2025/12/10 20:14:05 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <stdio.h>

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

static size_t	count_words(const char *str, char *seps)
{
	int	i;
	int	state;
	int	count;
	int	old_state;

	i = 0;
	state = !ft_strchr(seps, str[i]);
	old_state = state;
	count = 0;
	while (str[i])
	{
		while (str[i] && state == old_state)
			state = !ft_strchr(seps, str[i++]);
		count++;
		old_state = state;
	}
	if (state != !ft_strchr(seps, str[i - 2]))
		count++;
	return (count);
}

static void	next_word(char **word_ptr, size_t *size, char *c)
{
	int 	state;
	size_t	i;

	*size = 0;
	i = 0;
	state = !ft_strchr(c, *word_ptr[i]);
	while (**word_ptr && state == !ft_strchr(c, **word_ptr))
	{
		(*word_ptr)++;
		(*size)++;
	}
}

char	**ft_split_charset(char const *s, char *c)
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
		ft_strlcpy(sep[i], temp - len_temp, len_temp + 1);
		i++;
	}
	sep[i] = NULL;
	return (sep);
}
