/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:58:02 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/17 18:32:01 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtin_pipe(t_shell *shell, t_cmd *cmd)
{
	int	built;

	built = 1;
	if (!cmd || !cmd->name)
		return (1);
	if (!ft_strncmp(cmd->name, "echo", 5))
		built = echo_pipe(cmd);
	if (!ft_strncmp(cmd->name, "pwd", 4))
		built = pwd_pipe();
	if (!ft_strncmp(cmd->name, "env", 4))
		built = env_pipe(shell->envp_tmp);
	free_shell(shell);
	return (built);
}
