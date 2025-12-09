/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:38:24 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/09 15:58:53 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unset(t_cmd *cmd, t_shell *shell)
{
	t_var_list	*curr;
	char		*target;

	if (!cmd->args || !cmd->args[1])
		return (0);
	target = cmd->args[1];
	curr = shell->envp;
	while (curr)
	{
		if (!ft_strncmp(curr->name, target, ft_strlen(curr->name) + 1))
		{
			ft_lklremove(&shell->envp, curr);
			free_array(shell->envp_tmp);
			recreate_envp(shell);
			return (0);
		}
		curr = curr->next;
	}
	return (1);
}
