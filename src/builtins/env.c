/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:41:46 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/05 11:09:12 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_env_ordered(t_var_list *envp)
{
	t_var_list	*tmp;
	t_var_list	*underscore;

	tmp = envp;
	underscore = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "_", 2))
			underscore = tmp;
		else if (tmp->value)
			printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	if (underscore && underscore->value)
		printf("_=%s\n", underscore->value);
}

int	env(t_shell *shell)
{
	clean_command_free(shell);
	if (shell->cmd)
	{
		printf("env: '%s': No such file or directory\n", shell->cmd->name);
		clean_command_free(shell);
		shell->last_return = 127;
		return (127);
	}
	print_env_ordered(shell->envp);
	shell->last_return = 0;
	return (0);
}
