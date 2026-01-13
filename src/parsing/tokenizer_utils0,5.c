/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils0,5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:27:49 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/13 12:58:45 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	read_unquoted(char *s, int i)
{
	while (s[i] && s[i] != ' ' && !is_quote(s[i]))
		i++;
	return (i);
}

char	get_token_quote(char *s)
{
	int		i;
	char	current;

	if (!s)
		return (0);
	i = 0;
	current = 0;
	while (s[i])
	{
		if (!current && (s[i] == '\'' || s[i] == '"'))
			current = s[i];
		else if (current && s[i] == current)
			return (current);
		i++;
	}
	return (0);
}

char	is_quoted(char *s)
{
	int	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	if (len < 2)
		return (0);
	if ((s[0] == '\'' || s[0] == '"') && s[len - 1] == s[0])
		return (s[0]);
	return (0);
}
