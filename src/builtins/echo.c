/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:44:04 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/15 19:55:22 by dadoune          ###   ########.fr       */
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

static int	is_status_var(char *s)
{
	return (s && s[0] == '$' && s[1] == '?' && s[2] == '\0');
}

static void	display_argument(t_shell *shell)
{
	if (is_status_var(shell->cmd->name))
		print_status(shell);
	else
	{
		ft_putstr_fd(shell->cmd->name, 1);
		if (shell->cmd->next && \
			(shell->cmd->next->type == OPTION || shell->cmd->next->type == ARGUMENT))
			write(1, " ", 1);
		clean_command_free(shell);
	}
}

int	echo(t_shell *shell)
{
	int		nl;

	nl = 1;
	clean_command_free(shell);
	while (shell->cmd && shell->cmd->type == 1 && is_valid_n(shell->cmd->name))
	{
		nl = 0;
		clean_command_free(shell);
	}
	while (shell->cmd && shell->cmd->type)
		display_argument(shell);
	if (nl)
		write(1, "\n", 1);
	return (0);
}
