/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:20:15 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/08 11:06:06 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_var_list	*convert_env_variables(char **envp)
{
	int			i;
	char		**tmp;
	t_var_list	*env;

	i = -1;
	env = NULL;
	while (envp[++i])
	{
		tmp = ft_split(envp[i], '=');
		if (!tmp)
			exit(EXIT_FAILURE);
		ft_lkladd_back(&env,
			ft_lklnew(ft_strdup(tmp[0]), ft_strdup(tmp[1])));
		free_array(tmp);
	}
	return (env);
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
	shell->envp_tmp = envp;
	shell->envp = convert_env_variables(envp);
	if (!shell->envp)
		exit(EXIT_FAILURE);
	return (shell);
}

t_cmd	create_command(char *line)
{
	t_cmd	command;
	char	**args;

	args = ft_split(line);
	command.name = args[0];
	command.is_builtin = is_builtin(command.command);
	command.args = args;
	return (command);
}
