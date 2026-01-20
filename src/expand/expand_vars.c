/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:02:19 by aeherve           #+#    #+#             */
/*   Updated: 2026/01/20 10:33:56 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	append_char(char **dst, char c)
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

int	is_valid_var_start(char c)
{
	if (ft_isalpha(c) || c == '_' || c == '?')
		return (1);
	return (0);
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
int	append_str(char **dst, char *src)
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
