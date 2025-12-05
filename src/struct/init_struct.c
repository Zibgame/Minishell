/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:20:15 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/05 10:48:34 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*convert_env_variables(char **envp)
{
	t_list	*env;
	
	env = ft_lstnew(ft_split(envp[0], '='));
	printf("%s %s", env->content[0], env->content[0]);
	return (env);
}

t_shell	create_shell_struct(char **envp)
{
	t_shell	shell;

	shell.env = envp;
	convert_env_variables(envp);
	return (shell);
}
