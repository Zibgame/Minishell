/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:02:19 by aeherve           #+#    #+#             */
/*   Updated: 2026/01/05 21:46:00 by dadoune          ###   ########.fr       */
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

static char	*extract_var_name(char *s, int *i)
{
	int		start;
	char	*name;

	start = *i;
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	name = ft_strndup(&s[start], *i - start + 1);
	return (name);
}

static char	*expand_token(t_shell *shell, char *s)
{
	char	*res;
	char	*var;
	char	*value;
	int		i;

	res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '?')
		{
			value = ft_itoa(shell->last_return);
			if (!append_str(&res, value))
				return (free(value), free(res), NULL);
			free(value);
			i += 2;
		}
		else if (s[i] == '$' && s[i + 1])
		{
			i++;
			var = extract_var_name(s, &i);
			value = get_value(shell, var);
			if (!append_str(&res, value))
				return (free(var), free(res), NULL);
			free(var);
		}
		else
		{
			if (!append_char(&res, s[i]))
				return (free(res), NULL);
			i++;
		}
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
		if (cmd->quote == '\'')
			return ;
		// printf("\t%s, %d\n", cmd->name, cmd->quote);
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

