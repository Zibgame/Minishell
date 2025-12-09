/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:15:28 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/09 11:01:00 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtins(t_cmd cmd, t_shell *shell)
{
	(void)shell;
	if (!cmd.name)
		return (0);
	if (!ft_strncmp(cmd.name, "echo", 4))
		echo(&cmd, shell);
	if (!ft_strncmp(cmd.name, "cd", 2))
		cd(&cmd, shell);
	if (!ft_strncmp(cmd.name, "pwd", 3))
		pwd(&cmd, shell);
	if (!ft_strncmp(cmd.name, "export", 6))
		return (1);
	if (!ft_strncmp(cmd.name, "unset", 5))
		return (1);
	if (!ft_strncmp(cmd.name, "env", 3))
		env(&cmd, shell);
	if (!ft_strncmp(cmd.name, "exit", 4))
		finish(&cmd, shell);
	if (!ft_strncmp(cmd.name, "clear", 5))
		clear();
	return (0);
}
