/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:27:42 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/05 23:30:49 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*

	Ici code a modifier je sais ou est l'erreur a voir comment la corriger

*/
static char	*read_token(char *s, int *i, char *quote)
{
	char	buf[4096];
	int		j;

	j = 0;
	*quote = 0;
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
	if (!s[*i])
		return (NULL);
	if (s[*i] == '\'' || s[*i] == '"')
	{
		*quote = s[*i];
		(*i)++;
		while (s[*i] && s[*i] != *quote)
			buf[j++] = s[(*i)++];
		if (s[*i] == *quote)
			(*i)++;
	}
	else
	{
		while (s[*i] && s[*i] != ' ' && s[*i] != '\t')
			buf[j++] = s[(*i)++];
	}
	buf[j] = '\0';
	return (ft_strdup(buf));
}

char	**tokenize_line(char *line)
{
	char	**tokens;
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	tokens = ft_calloc(1024, sizeof(char *));
	if (!tokens)
		return (NULL);
	while (line[i])
	{
		tokens[count] = read_token(line, &i, &quote);
		if (!tokens[count])
			break ;
		count++;
	}
	return (tokens);
}

