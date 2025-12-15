/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:02:01 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/15 20:28:22 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	valid_char(char c)
{
	if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') || ('0' <= c && c <= '9'))
		return (1);
	return (0);
}

static int	valid_first_char(char c)
{
	if (c == '=' || ('!' <= c && c <= '@') || \
	('[' <= c && c <= '^') || ('{' <= c && c <= '~'))
		return (0);
	return (1);
}

static char	is_valid_assignment(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (!valid_first_char(s[i++]))
		return (0);
	while (s[i])
	{
		if (!valid_char(s[i]))
			return (0);
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	export(t_shell *shell)
{
	char	**env_var;

	clean_command_free(shell);
	if (!shell->cmd)
		return (1);
	if (shell->cmd->name && is_valid_assignment(shell->cmd->name))
	{
		env_var = ft_split(shell->cmd->name, '=');
		set_value(&shell, env_var[0], env_var[1]);
		clean_command_free(shell);
		return (0);
	}
	printf("bash: export: `%s': not a valid identifier\n", \
		shell->cmd->name);
	clean_command_free(shell);
	return (1);
}
