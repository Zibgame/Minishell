/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:06:21 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/06 14:08:10 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtins(char *name)
{
	if (!name)
		return (-1);
	if (!ft_strncmp(name, "echo", 5))
		return (BUILTINS);
	if (!ft_strncmp(name, "cd", 3))
		return (BUILTINS);
	if (!ft_strncmp(name, "pwd", 4))
		return (BUILTINS);
	if (!ft_strncmp(name, "export", 7))
		return (BUILTINS);
	if (!ft_strncmp(name, "unset", 6))
		return (BUILTINS);
	if (!ft_strncmp(name, "env", 4))
		return (BUILTINS);
	if (!ft_strncmp(name, "exit", 5))
		return (BUILTINS);
	if (!ft_strncmp(name, "clear", 6))
		return (BUILTINS);
	if (!ft_strncmp(name, "-", 1))
		return ((OPTION));
	return (-1);
}

int	has_multi_redir(char *str)
{
	int	i;
	int	j;

	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			j++;
		else
			j = 0;
		if (j == 2)
			if (str[i] != str[i - 1])
				return (PARSEERROR);
		if (j > 2)
			return (PARSEERROR);
		i++;
	}
	if (j == i && j == 2)
		return (REDIRECTION);
	return (0);
}

int	is_redirect(t_cmd *cmd)
{
	char	**new_args;

	new_args = NULL;
	if (ft_strchr(cmd->name, '<') || ft_strchr(cmd->name, '>'))
	{
		if (ft_strlen(cmd->name) > 1)
		{
			// printf("Redirs: %d, chaine: %s\n echo >>./outfiles/outfile01 bye >./test_files/invalid_permission\n", has_multi_redir(cmd->name), cmd->name);
			if (has_multi_redir(cmd->name) != 0)
				return (has_multi_redir(cmd->name));
			// if (comb_redir_oper_pipes(cmd->name) != 0)
			// 	return (comb_redir_oper_pipes(cmd->name));
			new_args = NULL;
			new_args = ft_split_charset(cmd->name, "<>");
			if (!new_args)
				return (0);
			add_commands(&cmd, new_args);
			free_array(new_args);
			return (TOREMOVE);
		}
		return (REDIRECTION);
	}
	return (0);
}

int	has_multi_pipes(char *str)
{
	int	i;
	int	j;

	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '|')
			j++;
		else
			j = 0;
		if (j > 2)
			return (PARSEERROR);
		i++;
	}
	if (j == i && j == 2)
		return (OPERATOR);
	return (0);
}

int	is_pipe(t_cmd *cmd)
{
	char	**new_args;

	if (ft_strchr(cmd->name, '|'))
	{
		if (ft_strlen(cmd->name) > 1)
		{
			if (has_multi_pipes(cmd->name) != 0)
				return (has_multi_pipes(cmd->name));
			if (comb_redir_oper_pipes(cmd->name) != 0)
				return (comb_redir_oper_pipes(cmd->name));
			new_args = NULL;
			new_args = ft_split_charset(cmd->name, "|");
			if (!new_args)
				return (0);
			add_commands(&cmd, new_args);
			free_array(new_args);
			return (TOREMOVE);
		}
		return (PIPE);
	}
	return (0);
}
