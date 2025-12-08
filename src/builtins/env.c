/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:41:46 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/08 11:43:45 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env(t_cmd *cmd, t_shell *shell)
{
	t_var_list	*vars;

	(void)cmd;
	vars = shell->envp;
	if (!vars)
		return (1);
	if (cmd->args[1])
	{
		printf("env: ");
		printf("'%s': ", cmd->args[1]);
		printf("No such file or directory\n");
		return (127);
	}
	while (vars)
	{
		if (vars->value)
		{
			printf("%s=%s\n", vars->name, vars->value);
		}
		vars = vars->next;
	}
	return (0);
}
