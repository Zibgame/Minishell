/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:41:46 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/08 20:36:27 by zcadinot         ###   ########.fr       */
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

int	env(t_cmd *cmd, t_shell *shell)
{
	t_cmd	new;

	if (!cmd->args[1])
		return (print_env(shell));
	if (!is_builtins(cmd->args[1]))
	{
		printf("env: '%s': No such file or directory\n", cmd->args[1]);
		return (127);
	}
	new = extract_next_cmd(cmd);
	if (!new.args || !new.name)
		return (1);
	return (exec_builtins(new, shell));
}
