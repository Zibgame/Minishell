/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:02:01 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/25 18:11:36 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	valid_char(char c)
{
	if (('A' <= c && c <= 'Z')
		|| ('a' <= c && c <= 'z')
		|| ('0' <= c && c <= '9')
		|| c == '_' || c == ' ')
		return (1);
	return (0);
}

static int	valid_first_char(char c)
{
	if (('A' <= c && c <= 'Z')
		|| ('a' <= c && c <= 'z')
		|| c == '_' || c == ' ')
		return (1);
	return (0);
}

static char	is_valid_assignment(char *s)
{
	int	i;

	if (!s || !valid_first_char(s[0]))
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		if (!valid_char(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	export(t_shell *shell)
{
	char	**env_var;

	clean_command_free(shell);
	if (!shell->cmd)
	{
		printf("Did you really tried to export air?\n");
		return (1);
	}
	if (shell->cmd->name && is_valid_assignment(shell->cmd->name))
	{
		env_var = ft_split(shell->cmd->name, '=');
		set_value(&shell, ft_strdup(env_var[0]), ft_strdup(env_var[1]));
		clean_command_free(shell);
		shell->last_return = 0;
		free_array(env_var);
		return (0);
	}
	ft_printf_fd("bash: export: `%s': not a valid identifier\n", 2, \
		shell->cmd->name);
	clean_command_free(shell);
	shell->last_return = 1;
	return (1);
}
