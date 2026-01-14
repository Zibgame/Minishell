/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:10:09 by aeherve           #+#    #+#             */
/*   Updated: 2025/12/16 13:56:52 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->cmd)
			ft_cmdclear(&shell->cmd);
		if (shell->envp)
			ft_lklclear(&shell->envp);
		if (shell->envp_tmp)
			free_array(shell->envp_tmp);
		free(shell);
	}
}

char	*join_and_free(char *s1, char *s2)
{
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = ft_strjoin(s1, s2);
	if (!res)
	{
		free(s1);
		return (NULL);
	}
	free(s1);
	return (res);
}

/*
clear actual node if exists and go to the next one if exists
*/
void	clean_command_free(t_shell *shell)
{
	if (shell && shell->cmd)
	{
		if (shell->cmd->next)
		{
			shell->cmd = shell->cmd->next;
			ft_cmddelone(shell->cmd->prev);
			shell->cmd->prev = NULL;
		}
		else
		{
			ft_cmddelone(shell->cmd);
			shell->cmd = NULL;
		}
	}
}
