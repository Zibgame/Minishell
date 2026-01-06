/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:20:15 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/06 11:57:27 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	convert_env_variables(t_shell *shell, char **envp)
{
	int			i;
	char		**tmp;

	i = -1;
	shell->envp = NULL;
	while (envp[++i])
	{
		tmp = ft_split(envp[i], '=');
		if (!tmp)
			exit(EXIT_FAILURE);
		if (!get_value(shell, tmp[0]))
		{
			ft_lkladd_back(&shell->envp,
				ft_lklnew(ft_strdup(tmp[0]), ft_strdup(tmp[1])));
			free_array(tmp);
		}
	}
}

char	*get_value(t_shell *shell, char *name)
{
	t_var_list	*tmp;

	if (!shell || !name)
		return (NULL);
	tmp = shell->envp;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(name) + 1) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

t_shell	*create_shell_struct(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		exit(EXIT_FAILURE);
	convert_env_variables(shell, envp);
	recreate_envp(shell);
	shell->cmd = NULL;
	shell->last_return = 0;
	if (!shell->envp)
		exit(EXIT_FAILURE);
	return (shell);
}
