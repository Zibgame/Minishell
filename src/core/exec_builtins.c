/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:15:28 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/11 13:00:28 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtins(t_shell *shell)
{
	if (!shell->cmd || !shell->cmd->name || shell->cmd->type != BUILTINS)
		return (-1);
	if (!ft_strncmp(shell->cmd->name, "echo", 4))
		echo(shell);
	if (!ft_strncmp(shell->cmd->name, "cd", 2))
		cd(shell);
	// if (!ft_strncmp(shell->cmd->name, "pwd", 3))
	// 	pwd(&cmd, shell);
	// if (!ft_strncmp(shell->cmd->name, "export", 6))
	// 	export(&cmd, shell);
	// if (!ft_strncmp(shell->cmd->name, "unset", 5))
	// 	return (1);
	// if (!ft_strncmp(shell->cmd->name, "env", 3))
	// 	env(&cmd, shell);
	// if (!ft_strncmp(shell->cmd->name, "exit", 4))
	// 	finish(&cmd, shell);
	if (!ft_strncmp(shell->cmd->name, "clear", 5))
		clear();
	return (0);
}
