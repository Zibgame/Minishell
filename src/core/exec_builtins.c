/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:15:28 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/01 23:15:28 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	exec_builtins(t_shell *shell)
// {
// 	int	save_stdin;
// 	int	save_stdout;

// 	shell->in_pipeline = 0;
// 	if (!shell->cmd->name)
// 		return (0);

// 	save_stdin = dup(STDIN_FILENO);
// 	save_stdout = dup(STDOUT_FILENO);

// 	if (apply_redirections(shell->cmd) < 0)
// 	{
// 		dup2(save_stdin, STDIN_FILENO);
// 		dup2(save_stdout, STDOUT_FILENO);
// 		close(save_stdin);
// 		close(save_stdout);
// 		return (1);
// 	}

// 	if (!ft_strncmp(shell->cmd->name, "echo", 4))
// 		echo(shell);
// 	else if (!ft_strncmp(shell->cmd->name, "cd", 2))
// 		cd(shell);
// 	else if (!ft_strncmp(shell->cmd->name, "pwd", 3))
// 		pwd(shell);
// 	else if (!ft_strncmp(shell->cmd->name, "export", 6))
// 		export(shell);
// 	else if (!ft_strncmp(shell->cmd->name, "unset", 5))
// 		unset(shell);
// 	else if (!ft_strncmp(shell->cmd->name, "env", 3))
// 		env(shell);
// 	else if (!ft_strncmp(shell->cmd->name, "exit", 4))
// 		finish(shell);
// 	else if (!ft_strncmp(shell->cmd->name, "clear", 5))
// 		clear();

// 	dup2(save_stdin, STDIN_FILENO);
// 	dup2(save_stdout, STDOUT_FILENO);
// 	close(save_stdin);
// 	close(save_stdout);

// 	return (0);
// }

int	exec_builtins(t_shell *shell)
{
	shell->in_pipeline = 0;
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
		unset(shell);
	else if (!ft_strncmp(shell->cmd->name, "env", 3))
		env(shell);
	else if (!ft_strncmp(shell->cmd->name, "exit", 4))
		finish(shell);
	else if (!ft_strncmp(shell->cmd->name, "clear", 5))
		clear();
	return (0);
}
