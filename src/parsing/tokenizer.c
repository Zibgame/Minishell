/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:27:42 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/06 11:21:56 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*read_token(char *s, int *i, char *quote)
{
	char	buf[4096];
	int		j;
	char	current;

	j = 0;
	current = 0;
	*quote = 0;
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
	if (!s[*i])
		return (NULL);
	while (s[*i])
	{
		if (!current && (s[*i] == '\'' || s[*i] == '"'))
		{
			current = s[*i];
			if (!*quote)
				*quote = current;
			buf[j++] = s[(*i)++];
		}
		else if (current && s[*i] == current)
		{
			current = 0;
			buf[j++] = s[(*i)++];
		}
		else if (!current && (s[*i] == ' ' || s[*i] == '\t'))
			break ;
		else
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


