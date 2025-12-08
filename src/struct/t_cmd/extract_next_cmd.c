/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_next_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:05:03 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/08 16:06:40 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	**copy_args_next(char **args)
{
	int		i;
	char	**new;

	i = 0;
	while (args[i + 1])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (args[i + 1])
	{
		new[i] = args[i + 1];
		i++;
	}
	new[i] = NULL;
	return (new);
}

t_cmd	extract_next_cmd(t_cmd *cmd)
{
	t_cmd	new;
	char	**new_args;

	new.name = NULL;
	new.args = NULL;
	if (!cmd || !cmd->args || !cmd->args[1])
		return (new);
	new_args = copy_args_next(cmd->args);
	if (!new_args)
		return (new);
	new.name = new_args[0];
	new.args = new_args;
	return (new);
}
