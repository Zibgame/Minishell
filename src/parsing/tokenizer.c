/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:18:58 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/20 13:00:59 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_spaces_internal(char *s, int *i)
{
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
}

static char	*read_operator(char *s, int *i)
{
	char	buf[3];
	int		j;

	j = 0;
	buf[j++] = s[(*i)++];
	if ((buf[0] == '<' || buf[0] == '>' || buf[0] == '|') && s[*i] == buf[0])
		buf[j++] = s[(*i)++];
	buf[j] = '\0';
	return (ft_strdup(buf));
}

static char	*read_word(char *s, int *i, char *quote)
{
	char	buf[4096];
	int		j;
	char	current;

	j = 0;
	current = 0;
	*quote = 0;
	while (s[*i])
	{
		if (!current && (s[*i] == '\'' || s[*i] == '"'))
		{
			current = s[*i];
			if (!*quote)
				*quote = current;
		}
		else if (current && s[*i] == current)
			current = 0;
		else if (!current && (s[*i] == ' ' || s[*i] == '\t'
				|| is_operator_char(s[*i])))
			break ;
		buf[j++] = s[(*i)++];
	}
	buf[j] = '\0';
	return (ft_strdup(buf));
}

static char	*read_token(char *s, int *i, char *quote)
{
	skip_spaces_internal(s, i);
	if (!s[*i])
		return (NULL);
	if (is_operator_char(s[*i]))
		return (read_operator(s, i));
	return (read_word(s, i, quote));
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
