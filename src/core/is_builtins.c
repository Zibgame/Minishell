/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:06:21 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/09 17:55:21 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtins(char *name)
{
	if (!name)
		return (0);
	if (!ft_strncmp(name, "echo", 5))
		return (BUILTINS + 1);
	if (!ft_strncmp(name, "cd", 3))
		return (BUILTINS + 1);
	if (!ft_strncmp(name, "pwd", 4))
		return (BUILTINS + 1);
	if (!ft_strncmp(name, "export", 7))
		return (BUILTINS + 1);
	if (!ft_strncmp(name, "unset", 6))
		return (BUILTINS + 1);
	if (!ft_strncmp(name, "env", 4))
		return (BUILTINS + 1);
	if (!ft_strncmp(name, "exit", 5))
		return (BUILTINS + 1);
	if (!ft_strncmp(name, "clear", 6))
		return (BUILTINS + 1);
	if (!ft_strncmp(name, "-", 1))
		return (OPTION + 1);
	return (0);
}

int	is_redirect(t_cmd *cmd)
{
	int		i;
	char	**new_args;

	if (ft_strchr(cmd->name, '<') || ft_strchr(cmd->name, '>'))
	{
		if (redirect_split(cmd, new_args))
			return (2);
		else
			add_commands(&cmd, new_args);
		return (1);
	}
	return (0);
}

int	is_pipe(t_cmd *cmd)
{
	int		i;
	char	**new_args;
	
	if (ft_strchr(cmd->name, '|') && ft_strchr(cmd->name, '|') == ft_strrchr(cmd->name, '|'))
	{
		new_args = NULL;
		if (ft_strlen(cmd->name) > 1)
			new_args = ft_split(cmd->name, '|');
		if (new_args)
		{
			i = 0;
			while (new_args[i])
			{
				ft_cmdadd_back(cmd, ft_cmdnew(new_args[i], 0));
				ft_cmdlast(cmd)->type = command_type(ft_cmdlast(cmd));
				ft_cmdadd_back(cmd, ft_cmdnew(ft_strdup("|"), 0));
				ft_cmdlast(cmd)->type = command_type(ft_cmdlast(cmd));
				i++;
			}
		}
		return (1);
	}
	if (ft_strchr(cmd->name, '|'))
		return (OPERATOR);
}
