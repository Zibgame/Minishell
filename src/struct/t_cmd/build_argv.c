/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:40:42 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/16 12:12:54 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	count_args(t_cmd *cmd)
{
	int	count;

	count = 1;
	cmd = cmd->next;
	while (cmd && (cmd->type == ARGUMENT || cmd->type == OPTION))
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

char	**build_argv(t_cmd *cmd)
{
	char	**argv;
	int		i;

	if (!cmd || !cmd->name)
		return (NULL);
	argv = malloc(sizeof(char *) * (count_args(cmd) + 1));
	if (!argv)
		return (NULL);
	i = 0;
	argv[i++] = ft_strdup(cmd->name);
	cmd = cmd->next;
	while (cmd && cmd->type == ARGUMENT)
	{
		argv[i++] = ft_strdup(cmd->name);
		cmd = cmd->next;
	}
	argv[i] = NULL;
	return (argv);
}

int	has_pipe(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (current->type == PIPE)
			return (1);
		current = current->next;
	}
	return (0);
}
