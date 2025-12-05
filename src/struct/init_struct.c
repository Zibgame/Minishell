/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:20:15 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/05 14:27:48 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_var_list	*convert_env_variables(char **envp)
{
	int			i;
	char		**tmp;
	t_var_list	*env;
	
	i = 0;
	if (envp[0])
	{
		
		while(envp[++i])
		{
			tmp = ft_split(envp[i], '=');
			if (!tmp)
			{
				//mettre message d'erreur
				exit (EXIT_FAILURE);
			}
			ft_lkladd_back(env, ft_lklnew(tmp[0], tmp[1]));
		}
	}
	else
		return (NULL);
	return (env);
}

char	*get_value(t_shell *shell, char *name)
{
	(void)shell;
	(void)name;
	return ("");
}

t_shell	create_shell_struct(char **envp)
{
	t_shell	shell;

	shell.envp_tmp = envp;
	shell.envp = convert_env_variables(envp);
	if (!shell.envp)
	{
		//mettre message d'erreur
	}
	return (shell);
}
