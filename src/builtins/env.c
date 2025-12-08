/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:41:46 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/08 11:49:22 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	print_env(t_var_list *vars)
{
	while (vars)
	{
		if (vars->value)
			printf("%s=%s\n", vars->name, vars->value);
		vars = vars->next;
	}
	return (0);
}

static t_cmd	create_env_cmd(t_cmd *cmd)
{
	t_cmd	new;
	int		i;
	int		j;

	new.name = cmd->args[1];
	i = 1;
	j = 0;
	while (cmd->args[i])
		i++;
	new.args = malloc(sizeof(char *) * (i));
	if (!new.args)
	{
		new.args = NULL;
		return (new);
	}
	i = 1;
	while (cmd->args[i])
	{
		new.args[j] = cmd->args[i];
		i++;
		j++;
	}
	new.args[j] = NULL;
	return (new);
}

int	env(t_cmd *cmd, t_shell *shell)
{
	t_cmd	new;

	if (!cmd->args[1])
		return (print_env(shell->envp));
	if (!is_builtins(cmd->args[1]))
	{
		printf("env: '%s': No such file or directory\n", cmd->args[1]);
		return (127);
	}
	new = create_env_cmd(cmd);
	if (!new.args)
		return (1);
	return (exec_builtins(new, shell));
}
