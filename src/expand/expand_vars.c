/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:02:19 by aeherve           #+#    #+#             */
/*   Updated: 2026/01/06 11:49:40 by aeherve          ###   ########.fr       */
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

static char	*extract_var_name(char *s, int *i)
{
	int		start;
	char	*name;

	start = *i;
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	name = ft_strndup(&s[start], *i - start);
	return (name);
}

static char	*expand_token(t_shell *shell, char *s)
{
	char	*res;
	char	*var;
	char	*value;
	int		i;
	char	current;

	res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
	i = 0;
	current = 0;
	while (s[i])
	{
		if (!current && (s[i] == '\'' || s[i] == '"'))
			current = s[i];
		else if (current && s[i] == current)
			current = 0;
		else if (s[i] == '$' && current != '\'' && s[i + 1] == '?')
		{
			value = ft_itoa(shell->last_return);
			if (!append_str(&res, value))
				return (free(value), free(res), NULL);
			free(value);
			i += 2;
			continue ;
		}
		else if (s[i] == '$' && current != '\'')
		{
			if (!s[i + 1] || !is_valid_var_start(s[i + 1]))
			{
				if (!append_char(&res, '$'))
					return (free(res), NULL);
				i++;
				continue ;
			}
			i++;
			var = extract_var_name(s, &i);
			value = get_value(shell, var);
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


