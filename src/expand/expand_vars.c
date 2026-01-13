/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:02:19 by aeherve           #+#    #+#             */
/*   Updated: 2026/01/13 13:00:02 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	append_char(char **dst, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strjoin(*dst, buf);
	if (!tmp)
		return (0);
	free(*dst);
	*dst = tmp;
	return (1);
}

static int	append_str(char **dst, char *src)
{
	char	*tmp;

	if (!src)
		return (1);
	tmp = ft_strjoin(*dst, src);
	if (!tmp)
		return (0);
	free(*dst);
	*dst = tmp;
	return (1);
}

static int	is_valid_var_start(char c)
{
	if (ft_isalpha(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

static char	*expand_token(t_shell *shell, char *s)
{
	char	*res;
	char	*var;
	char	*value;
	int		i;
	int		start;
	char	quote;

	res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
	i = 0;
	quote = 0;
	while (s[i])
	{
		if (!quote && (s[i] == '\'' || s[i] == '"'))
			quote = s[i];
		else if (quote && s[i] == quote)
			quote = 0;
		else if (s[i] == '$' && quote != '\'' && s[i + 1] == '?')
		{
			value = ft_itoa(shell->last_return);
			if (!value || !append_str(&res, value))
				return (free(value), free(res), NULL);
			free(value);
			i += 2;
			continue ;
		}
		else if (s[i] == '$' && quote != '\'')
		{
			i++;
			if (!s[i] || !is_valid_var_start(s[i]))
			{
				if (!append_char(&res, '$'))
					return (free(res), NULL);
				continue ;
			}
			start = i;
			while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
				i++;
			var = ft_substr(s, start, i - start);
			if (!var)
				return (free(res), NULL);
			value = get_value(shell, var);
			if (!value)
				value = "";
			if (!append_str(&res, value))
				return (free(var), free(res), NULL);
			free(var);
			continue ;
		}
		if (!append_char(&res, s[i]))
			return (free(res), NULL);
		i++;
	}
	return (res);
}

void	expand_vars(t_shell *shell)
{
	t_cmd	*cmd;
	char	*new;

	cmd = shell->cmd;
	while (cmd)
	{
		if (cmd->name)
		{
			new = expand_token(shell, cmd->name);
			if (!new)
				return ;
			free(cmd->name);
			cmd->name = new;
		}
		cmd = cmd->next;
	}
}
