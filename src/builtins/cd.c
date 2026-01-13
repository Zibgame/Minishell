/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 10:51:52 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/13 13:38:13 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_env_var(t_shell *shell, char *name, char *value)
{
	t_var_list	*cur;
	t_var_list	*new;

	cur = shell->envp;
	while (cur)
	{
		if (!ft_strncmp(cur->name, name, ft_strlen(name) + 1))
		{
			free(cur->value);
			cur->value = ft_strdup(value);
			return ;
		}
		cur = cur->next;
	}
	new = ft_lklnew(name, value);
	if (!new)
		return ;
	ft_lkladd_back(&shell->envp, new);
}

static void	update_pwd_vars(t_shell *shell)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	oldpwd = get_value(shell, "PWD");
	if (oldpwd)
		set_env_var(shell, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		set_env_var(shell, "PWD", cwd);
	free_array(shell->envp_tmp);
	recreate_envp(shell);
}

static int	cd_home(t_shell *shell)
{
	char	*home;

	home = get_value(shell, "HOME");
	if (!home)
	{
		ft_printf_fd("minishell: cd: HOME not set\n", 2);
		shell->last_return = 1;
		return (1);
	}
	if (chdir(home) != 0)
	{
		perror("minishell: cd");
		shell->last_return = 1;
		return (1);
	}
	update_pwd_vars(shell);
	shell->last_return = 0;
	return (0);
}

static int	non_existing_path(t_shell *shell)
{
	perror("minishell: cd");
	shell->last_return = 1;
	clean_command_free(shell);
	return (1);
}

int	cd(t_shell *shell)
{
	t_cmd	*arg;

	arg = shell->cmd->next;
	if (arg && arg->next)
	{
		ft_printf_fd("minishell: cd: too many arguments\n", 2);
		shell->last_return = 1;
		clean_command_free(shell);
		return (2);
	}
	if (!arg)
	{
		cd_home(shell);
		clean_command_free(shell);
		return (shell->last_return);
	}
	if (chdir(arg->name) != 0)
		return (non_existing_path(shell));
	update_pwd_vars(shell);
	shell->last_return = 0;
	clean_command_free(shell);
	return (0);
}
