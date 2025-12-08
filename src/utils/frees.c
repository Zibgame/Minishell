/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:10:09 by aeherve           #+#    #+#             */
/*   Updated: 2025/12/08 13:28:53 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->actual_command)
			ft_cmdclear(&shell->actual_command);
		if (shell->envp)
			ft_lklclear(&shell->envp);
		if (shell->envp_tmp)
			free_array(shell->envp_tmp);
		free(shell);
	}
}
