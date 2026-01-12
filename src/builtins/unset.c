/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:38:24 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/12 16:39:39 by zcadinot         ###   ########.fr       */
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

static void	remove_var(t_shell *shell, char *name)
{
	t_var_list	*cur;

	cur = shell->envp;
	while (cur)
	{
		if (!ft_strncmp(cur->name, name, ft_strlen(name) + 1))
		{
			if (cur->previous)
				cur->previous->next = cur->next;
			else
				shell->envp = cur->next;
			if (cur->next)
				cur->next->previous = cur->previous;
			ft_lkldelone(cur);
			return ;
		}
		cur = cur->next;
	}
}

int	unset(t_shell *shell)
{
	t_cmd	*arg;

	if (!shell || !shell->cmd)
		return (1);
	arg = shell->cmd->next;
	while (arg)
	{
		if (!is_valid_identifier(arg->name))
		{
			ft_printf_fd("unset: `%s': not a valid identifier\n", 2, arg->name);
			shell->last_return = 1;
			clean_command_free(shell);
			return (1);
		}
		remove_var(shell, arg->name);
		arg = arg->next;
	}
	free_array(shell->envp_tmp);
	recreate_envp(shell);
	shell->last_return = 0;
	clean_command_free(shell);
	return (0);
}
