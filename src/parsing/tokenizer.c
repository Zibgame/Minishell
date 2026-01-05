/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:27:42 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/05 15:10:24 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

static int	append_char(char **buf, char c)
{
	char	tmp[2];
	char	*new;

	tmp[0] = c;
	tmp[1] = '\0';
	new = ft_strjoin(*buf, tmp);
	if (!new)
		return (0);
	free(*buf);
	*buf = new;
	return (1);
}

static char	*read_token(char *s, int *i)
{
	char	*buf;
	int		end;

	buf = ft_calloc(1, 1);
	if (!buf)
		return (NULL);
	printf ("base line -> %s\n", s);
	while (s[*i] && !is_space(s[*i]))
	{
		if (s[*i] == '\'' || s[*i] == '"')
		{
			end = read_quoted(s, *i, s[*i]);
			if (end == -1)
				return (free(buf), NULL);
			(*i)++;
			while (*i < end - 1)
			{
				if (!append_char(&buf, s[*i]))
					return (free(buf), NULL);
				(*i)++;
			}
			(*i)++;
		}
		else
		{
			if (!append_char(&buf, s[*i]))
				return (free(buf), NULL);
			(*i)++;
		}
	}
	printf ("base line -> %s\n", s);
	return (buf);
}

char	**tokenize_line(char *line)
{
	char	**tokens;
	int		i;
	int		count;

	i = 0;
	count = 0;
	tokens = ft_calloc(1024, sizeof(char *));
	if (!tokens)
		return (NULL);
	while (line[i])
	{
		while (is_space(line[i]))
			i++;
		if (!line[i])
			break ;
		tokens[count] = read_token(line, &i);
		if (!tokens[count])
			return (free_array(tokens), NULL);
		count++;
	}
	return (tokens);
}
