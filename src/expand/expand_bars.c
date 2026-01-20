/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_bars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:27:59 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/20 10:38:05 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_quote(char c, char *quote)
{
	if (!*quote && (c == '\'' || c == '"'))
		*quote = c;
	else if (*quote && c == *quote)
		*quote = 0;
}

static int	expand_last_status(t_shell *shell, char **res, int *i)
{
	char	*value;

	value = ft_itoa(shell->last_return);
	if (!value)
		return (0);
	if (!append_str(res, value))
		return (free(value), 0);
	free(value);
	*i += 2;
	return (1);
}

static int	expand_env_var(t_shell *shell, char *s, char **res, int *i)
{
	char	*var;
	char	*value;
	int		start;

	(*i)++;
	if (!s[*i] || !is_valid_var_start(s[*i]))
		return (append_char(res, '$'));
	start = *i;
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	var = ft_substr(s, start, *i - start);
	if (!var)
		return (0);
	value = get_value(shell, var);
	if (!value)
		value = "";
	if (!append_str(res, value))
		return (free(var), 0);
	free(var);
	return (1);
}

char	*expansion(t_shell *shell, char *s, char quote, char *res)
{
	int	i;

	i = 0;
	while (s[i])
	{
		update_quote(s[i], &quote);
		if (s[i] == '$' && quote != '\'' && s[i + 1] == '?')
		{
			if (!expand_last_status(shell, &res, &i))
				return (free(res), NULL);
			continue ;
		}
		if (s[i] == '$' && quote != '\'')
		{
			if (!expand_env_var(shell, s, &res, &i))
				return (free(res), NULL);
			continue ;
		}
		if (!append_char(&res, s[i++]))
			return (free(res), NULL);
	}
	return (res);
}

char	*expand_token(t_shell *shell, char *s)
{
	char	*res;
	char	quote;

	res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
	quote = 0;
	res = expansion(shell, s, quote, res);
	return (res);
}
