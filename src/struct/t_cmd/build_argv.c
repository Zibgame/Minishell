/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:40:42 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/07 13:24:38 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	count_args(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd && cmd->type != PIPE)
	{
		if (cmd->type == ARGUMENT || cmd->type == OPTION
			|| cmd->type == BUILTINS)
			count++;
		cmd = cmd->next;
	}
	return (count);
}

char	**build_argv(t_cmd *cmd)
{
	char	**argv;
	int		i;

	if (!cmd)
		return (NULL);
	argv = malloc(sizeof(char *) * (count_args(cmd) + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (cmd && cmd->type != PIPE)
	{
		if (cmd->type == ARGUMENT || cmd->type == OPTION
			|| cmd->type == BUILTINS)
			argv[i++] = ft_strdup(cmd->name);
		cmd = cmd->next;
	}
	argv[i] = NULL;
	return (argv);
}

int	has_pipe(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->type == PIPE)
			return (1);
		if (cmd->type == OPERATOR && cmd->name
			&& cmd->name[0] == '|' && cmd->name[1] == '\0')
			return (1);
		cmd = cmd->next;
	}
	return (0);
}
