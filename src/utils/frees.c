/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:10:09 by aeherve           #+#    #+#             */
/*   Updated: 2025/12/22 16:54:32 by zcadinot         ###   ########.fr       */
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
	char	*new_line;

	new_line = ft_strjoin(s1, s2);
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	return (new_line);
}

/*
clear actual node if exists and go to the next one if exists
*/
void	clean_command_free(t_shell *shell)
{
	if (!shell || shell->in_pipeline)
		return ;
	if (shell->cmd)
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
