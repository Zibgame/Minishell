/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:58:30 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/05 20:57:26 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_n(char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] != 'n')
		return (0);
	i = 2;
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}

static void	putstr_without_quotes(char *s)
{
	int	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	if (len >= 2 && ((s[0] == '\'' && s[len - 1] == '\'')
			|| (s[0] == '"' && s[len - 1] == '"')))
	{
		write(STDOUT_FILENO, s + 1, len - 2);
		return ;
	}
	ft_putstr_fd(s, STDOUT_FILENO);
}

int	echo_pipe(t_cmd *cmd)
{
	int	nl;

	nl = 1;
	cmd = cmd->next;
	while (cmd && is_valid_n(cmd->name))
	{
		nl = 0;
		cmd = cmd->next;
	}
	while (cmd && (cmd->type == ARGUMENT || cmd->type == OPTION))
	{
		putstr_without_quotes(cmd->name);
		if (cmd->next && (cmd->next->type == ARGUMENT
				|| cmd->next->type == OPTION))
			write(STDOUT_FILENO, " ", 1);
		cmd = cmd->next;
	}
	if (nl)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
