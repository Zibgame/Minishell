/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:27:42 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/05 13:27:45 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_tokens(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		i = skip_spaces(s, i);
		if (!s[i])
			break;
		count++;
		if (s[i] == '\'' || s[i] == '"')
			i = read_quoted(s, i, s[i]);
		else
			i = read_unquoted(s, i);
	}
	return (count);
}

static char	*extract_token(char *s, int *i)
{
	int		start;
	char	quote;
	char	*token;

	*i = skip_spaces(s, *i);
	start = *i;
	if (s[*i] == '\'' || s[*i] == '"')
	{
		quote = s[*i];
		start++;
		*i = read_quoted(s, *i, quote);
		token = ft_substr(s, start, *i - start - 1);
	}
	else
	{
		*i = read_unquoted(s, *i);
		token = ft_substr(s, start, *i - start);
	}
	return (token);
}

char	**tokenize_line(char *line)
{
	char	**tokens;
	int		i;
	int		j;
	int		count;

	count = count_tokens(line);
	tokens = ft_calloc(count + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count)
	{
		tokens[j] = extract_token(line, &i);
		if (!tokens[j])
			return (free_array(tokens), NULL);
		j++;
	}
	return (tokens);
}
