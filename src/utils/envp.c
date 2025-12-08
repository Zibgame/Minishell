/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:03:04 by aeherve           #+#    #+#             */
/*   Updated: 2025/12/08 19:04:05 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	convert_envp(t_shell *shell, int total_size, t_var_list	*tmp)
{
	int	i;
	int	line_size;

	i = 0;
	while (i < total_size)
	{
		line_size = 2;
		if (tmp->name)
			line_size += ft_strlen(tmp->name);
		if (tmp->value)
			line_size += ft_strlen(tmp->value);
		shell->envp_tmp[i] = ft_calloc(line_size * sizeof(char) + 2, 1);
		if (tmp->name)
			shell->envp_tmp[i] = join_and_free(shell->envp_tmp[i], tmp->name);
		if (tmp->value)
		{
			shell->envp_tmp[i] = join_and_free(shell->envp_tmp[i], "=");
			shell->envp_tmp[i] = join_and_free(shell->envp_tmp[i], tmp->value);
		}
		tmp = tmp->next;
		i++;
	}
}

void	recreate_envp(t_shell *shell)
{
	int			total_size;
	t_var_list	*tmp;

	tmp = shell->envp;
	total_size = ft_lklsize(tmp);
	shell->envp_tmp = ft_calloc(sizeof(char *) * total_size + 1, 1);
	convert_envp(shell, total_size, tmp);
	shell->envp_tmp[total_size - 1] = NULL; 
}
