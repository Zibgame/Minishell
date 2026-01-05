/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:27:49 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/05 13:43:43 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	skip_spaces(char *s, int i)
{
	while (s[i] == ' ')
		i++;
	return (i);
}

int	read_quoted(char *s, int i, char quote)
{
	i++;
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] != quote)
		return (-1);
	return (i + 1);
}

int	read_unquoted(char *s, int i)
{
	while (s[i] && s[i] != ' ' && !is_quote(s[i]))
		i++;
	return (i);
}
