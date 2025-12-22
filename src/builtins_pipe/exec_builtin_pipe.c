/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:58:02 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/22 17:23:12 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtin_pipe(t_shell *shell, t_cmd *cmd)
{
	if (!cmd || !cmd->name)
		return (0);
	if (!ft_strncmp(cmd->name, "echo", 5))
		return (echo_pipe(shell, cmd));
	if (!ft_strncmp(cmd->name, "pwd", 4))
		return (pwd_pipe());
	if (!ft_strncmp(cmd->name, "env", 4))
		return (env_pipe(shell->envp_tmp));
	if (!ft_strncmp(cmd->name, "cd", 3))
		return (0);
	if (!ft_strncmp(cmd->name, "export", 7))
		return (0);
	if (!ft_strncmp(cmd->name, "unset", 6))
		return (0);
	if (!ft_strncmp(cmd->name, "exit", 5))
		return (0);
	return (0);
}

