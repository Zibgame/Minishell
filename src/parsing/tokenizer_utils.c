/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:27:49 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/13 12:58:36 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_operator_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	is_double_operator(char *s)
{
	if (!s || !s[1])
		return (0);
	if ((s[0] == '<' && s[1] == '<')
		|| (s[0] == '>' && s[1] == '>'))
		return (1);
	return (0);
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
