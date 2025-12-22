/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:41:46 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/22 17:30:28 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	print_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp_tmp[i])
		printf("%s\n", shell->envp_tmp[i++]);
	return (0);
}

int	env(t_shell *shell)
{
	clean_command_free(shell);
	if (!shell->cmd)
		return (print_env(shell));
	printf("env: '%s': No such file or directory\n", shell->cmd->name);
	clean_command_free(shell);
	shell->last_return = 127;
	return (127);
}
