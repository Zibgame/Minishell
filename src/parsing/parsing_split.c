/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:32:07 by dadoune           #+#    #+#             */
/*   Updated: 2025/12/10 18:36:26 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/minishell.h"
#include <stdlib.h>
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str && str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			break ;
		i++;
	}
	if (s[i] == (char) c)
		return ((char *) s + i);
	return (NULL);
}

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
		{
			i++;
			state = !ft_strchr(seps, str[i]);
		}
		if (str[i])
		{
			count++;
			old_state = state;
		}
	}
	return (count);
}

static void	next_word(char **word_ptr, size_t *size, char *c)
{
	int 	state;
	int		old_state;
	size_t	i;

	*word_ptr += *size;
	*size = 0;
	i = 0;
	state = !ft_strchr(c, *word_ptr[i]);
	old_state = state;
	printf("state: %d, char: |%c| size: %zu \n", state, *word_ptr[i], *size);
	while (**word_ptr && state == old_state)
	{
		(*word_ptr)++;
		(*size)++;
		state = !ft_strchr(c, **word_ptr);
	}
	printf("state: %d, char: |%c| size: %zu \n", state, *word_ptr[i], *size);
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
		temp -= len_temp;
		ft_strlcpy(sep[i], temp, len_temp + 1);
		temp += len_temp - 1;
		i++;
	}
	sep[i] = NULL;
	return (sep);
}

int main(void)
{
	char *test = "\ttruc truc\ttruc\t truc ";
	char *charset = " \t";
	char **seped;
	int		i = 0;
	
	seped = ft_split_charset(test, charset);
	while (seped[i])
	{
		printf("|%s|\n", seped[i]);
		i++;
	}
}