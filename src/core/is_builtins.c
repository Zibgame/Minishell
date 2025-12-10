/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:06:21 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/10 17:31:45 by dadoune          ###   ########.fr       */
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
	int		code;
	char	**new_args;

	new_args = NULL;
	code = 0;
	if (ft_strchr(cmd->name, '<') || ft_strchr(cmd->name, '>'))
	{
		if (redirect_split(cmd, new_args))
			code = 2;
		else
		{
			add_commands(&cmd, new_args);
			code = 1;
		}
		printf("%p", new_args);
		free_array(new_args);
		return (code);
	}
	return (0);
}

void	add_pipe_sep_args(t_cmd **cmd, char **new_args)
{
	int	i;
	
	i = 0;
	while (new_args && new_args[i])
	{
		ft_cmdadd_back(cmd, ft_cmdnew(new_args[i], 0));
		ft_cmdlast(*cmd)->type = command_type(ft_cmdlast(*cmd));
		i++;
		if (!new_args[i])
			return ;
		ft_cmdadd_back(cmd, ft_cmdnew(ft_strdup("|"), 0));
		ft_cmdlast(*cmd)->type = command_type(ft_cmdlast(*cmd));
	}
}

int	is_pipe(t_cmd *cmd)
{
	char	**new_args;
	
	new_args = NULL;
	if (ft_strchr(cmd->name, '|'))
	{
		if (ft_strchr(cmd->name, '|') == ft_strrchr(cmd->name, '|'))
		{
			new_args = NULL;
			if (ft_strlen(cmd->name) > 1)
				new_args = ft_split(cmd->name, '|');
			else
				return (PIPE);
		}
	}
	else if (ft_strchr(cmd->name, '|'))
		return (OPERATOR);
	if (new_args)
	{
		add_pipe_sep_args(&cmd, new_args);
		return (TOREMOVE);
	}
	return (0);
}
