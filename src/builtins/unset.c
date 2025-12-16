/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:38:24 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/16 12:32:37 by aeherve          ###   ########.fr       */
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

int	unset(t_cmd *cmd, t_shell *shell)
{
	// t_var_list	*curr;
	// char		*target;
	(void)cmd;
	(void)shell;
	// if (!cmd->args || !cmd->args[1])
	// 	return (0);
	// target = cmd->args[1];
	// if (!is_valid_identifier(target))
	// {
	// 	printf("unset: %s: invalid parameter name\n", target);
	// 	return (1);
	// }
	// curr = shell->envp;
	// while (curr)
	// {
	// 	if (!ft_strncmp(curr->name, target, ft_strlen(curr->name) + 1))
	// 	{
	// 		ft_lklremove(&shell->envp, curr);
	// 		free_array(shell->envp_tmp);
	// 		recreate_envp(shell);
	// 		return (0);
	// 	}
	// 	curr = curr->next;
	// }
	// return (1);
}
