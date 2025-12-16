/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:38:24 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/16 14:37:28 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_identifier(char *s)
{
	int	i;

	if (!s || !(ft_isalpha(s[0]) || s[0] == '_'))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static int	search_and_unset(t_shell *shell)
{
	t_var_list	*tmp;

	tmp = shell->envp;
	while (shell->cmd && shell->cmd->type == ARGUMENT)
	{
		if (!is_valid_identifier(shell->cmd->name))
			return (1);
		if (!ft_strncmp(shell->cmd->name, tmp->name, ft_strlen(shell->cmd->name) + 1))
		{
			if (tmp->next)
				tmp->next->previous = tmp->previous;
			if (tmp->previous)
				tmp->previous->next = tmp->next;
			ft_lkldelone(tmp);
			free_array(shell->envp_tmp);
			recreate_envp(shell);
			clean_command_free(shell);
			tmp = shell->envp;
		}
		tmp = tmp->next;
		if (!tmp)
		{
			tmp = shell->envp;
			clean_command_free(shell);
		}
	}
	return (0);
}

int	unset(t_shell *shell)
{
	clean_command_free(shell);
	if (!shell->cmd || !shell->cmd->name)
	{
		printf("unset: not enough arguments\n");
		shell->last_return = 1;
		return (1);
	}
	if (search_and_unset(shell))
	{
		printf("unset: %s: invalid parameter name\n", shell->cmd->name);
		shell->last_return = 1;
		return (1);
	}
	return (1);
}
