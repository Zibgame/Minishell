/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:02:01 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/09 16:43:08 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_assignment(char *s)
{
	int	i;
	int	has_equal;

	i = 0;
	has_equal = 0;
	if (!s || s[0] == '=')
		return (0);
	while (s[i])
	{
		if (s[i] == '=')
		{
			has_equal = 1;
			if (s[i + 1] == '\0')
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

int	export(t_cmd *cmd, t_shell *shell)
{
	char	**env_var;

	if (cmd->name && is_valid_assignment(cmd->name))
	{
		env_var = ft_split(cmd->name, '=');
		set_value(&shell, env_var[0], env_var[1]);
		return (0);
	}
	printf("error: mabitee");
	return (1);
}
