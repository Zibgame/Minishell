/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:03:04 by aeherve           #+#    #+#             */
/*   Updated: 2025/12/09 11:40:57 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	convert_envp(t_shell *shell, int size, t_var_list *tmp)
{
	int	i;
	int	line_size;

	i = 0;
	while (i < size)
	{
		line_size = 2;
		if (tmp->name)
			line_size += ft_strlen(tmp->name);
		if (tmp->value)
			line_size += ft_strlen(tmp->value);
		shell->envp_tmp[i] = ft_calloc(line_size, 1);
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
	int			size;
	t_var_list	*tmp;

	tmp = shell->envp;
	size = ft_lklsize(tmp);
	shell->envp_tmp = ft_calloc(size + 1, sizeof(char *));
	convert_envp(shell, size, tmp);
	shell->envp_tmp[size] = NULL;
}

void	set_value(char *value)
{
	(void)value;
	return ;
}
