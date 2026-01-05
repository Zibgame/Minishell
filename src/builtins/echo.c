/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:44:04 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/05 21:09:23 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_n_option(char *s)
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
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '"')
			write(STDOUT_FILENO, &s[i], 1);
		i++;
	}
}


int	echo(t_shell *shell)
{
	t_cmd	*cmd;
	int		newline;

	if (!shell || !shell->cmd)
		return (1);
	newline = 1;
	cmd = shell->cmd->next;
	while (cmd && is_n_option(cmd->name))
	{
		newline = 0;
		cmd = cmd->next;
	}
	while (cmd && (cmd->type == ARGUMENT || cmd->type == OPTION))
	{
		putstr_without_quotes(cmd->name);
		if (cmd->next && (cmd->next->type == ARGUMENT
				|| cmd->next->type == OPTION))
			ft_putchar_fd(' ', STDOUT_FILENO);
		cmd = cmd->next;
	}	
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	clean_command_free(shell);
	return (0);
}
