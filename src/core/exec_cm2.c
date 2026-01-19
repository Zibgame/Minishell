/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cm2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:04:17 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/19 16:58:22 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	return_type(t_shell *shell, char *line)
{
	if (!ft_strncmp("$", line, 1) && ft_strncmp("$?", line, 2)
		&& ft_strlen(line) > 1)
		shell->last_return = 0;
	else
		shell->last_return = 127;
}

int	handle_direct_path(t_shell *shell, char *cmd)
{
	struct stat	st;

	if (stat(cmd, &st) != 0)
	{
		ft_printf_fd("minishell: %s: No such file or directory\n", 2, cmd);
		shell->last_return = 127;
		return (1);
	}
	if (S_ISDIR(st.st_mode))
	{
		ft_printf_fd("minishell: %s: Is a directory\n", 2, cmd);
		shell->last_return = 126;
		return (1);
	}
	if (access(cmd, X_OK) != 0 || access(cmd, R_OK) != 0)
	{
		ft_printf_fd("minishell: %s: Permission denied\n", 2, cmd);
		shell->last_return = 126;
		return (1);
	}
	return (0);
}
