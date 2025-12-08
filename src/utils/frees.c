/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:10:09 by aeherve           #+#    #+#             */
/*   Updated: 2025/12/08 20:53:01 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_shell(t_shell *shell)
{
	// int	i;

	if (shell)
	{
		if (shell->actual_command)
			free_array(shell->actual_command->args);
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
