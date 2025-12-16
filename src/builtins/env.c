/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:41:46 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/16 02:38:51 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	print_env(t_shell *shell)
{
	int i;
	
	i = 0;
	while (shell->envp_tmp[i])
		printf("%s\n", shell->envp_tmp[i++]);
	return (0);
}

int	env(t_shell *shell)
{
	clean_command_free(shell);
	if (!shell->cmd)
		shell->last_return = print_env(shell);
	else if (shell->cmd->type != PARSEERROR)
	{
		if (!ft_strncmp(shell->cmd->name, "pwd", 4))
			return(pwd(shell));
		else if (!ft_strncmp(shell->cmd->name, "env", 4))
			return (env(shell));
		printf("env: '%s': No such file or directory\n", shell->cmd->name);
		clean_command_free(shell);
		shell->last_return = 127;
		return (127);
	}
	shell->last_return = 0;
	return (0);
}
