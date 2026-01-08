/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 10:51:52 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/08 19:31:52 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	use_HOME(t_shell *shell)
{
	char	*home;
	
	home = get_value(shell, "HOME");
	if (!home)
	{
		ft_printf_fd("minishell: cd: HOME not set\n", 2);
		shell->last_return = 1;
		return (1);
	}
	if (chdir(home) == -1)
	{
		ft_printf_fd("minishell: cd: %s: No such file or directory\n", 2, home);
		shell->last_return = 1;
		return (1);
	}
	shell->last_return = 0;
	return (0);
}

int	cd(t_shell *shell)
{
	char	*path;

	if (ft_cmdsize(shell->cmd) == 1)
		return (use_HOME(shell));
	if (ft_cmdsize(shell->cmd) > 2)
	{
		ft_printf_fd("cd: too many arguments\n", 2);
		shell->last_return = 1;
		return (1);
	}
	if (!shell->cmd->next || shell->cmd->next->type != ARGUMENT)
		return (1);
	path = shell->cmd->next->name;
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		ft_printf_fd("minishell: cd: %s: No such file or directory\n", 2, path);
		shell->last_return = 1;
		return (1);
	}
	shell->last_return = 0;
	clean_command_free(shell);
	clean_command_free(shell);
	return (0);
}
