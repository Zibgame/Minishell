/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:15:28 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/16 12:31:36 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtins(t_shell *shell)
{
	if (!shell->cmd->name)
		return (0);
	else if (!ft_strncmp(shell->cmd->name, "echo", 4))
		echo(shell);
	else if (!ft_strncmp(shell->cmd->name, "cd", 2))
		cd(shell);
	else if (!ft_strncmp(shell->cmd->name, "pwd", 3))
		pwd(shell);
	else if (!ft_strncmp(shell->cmd->name, "export", 6))
		export(shell);
	else if (!ft_strncmp(shell->cmd->name, "unset", 5))
		return (1);
	else if (!ft_strncmp(shell->cmd->name, "env", 3))
		env(shell);
	else if (!ft_strncmp(shell->cmd->name, "exit", 4))
		finish(shell);
	else if (!ft_strncmp(shell->cmd->name, "clear", 5))
		clear();
	return (0);
}
