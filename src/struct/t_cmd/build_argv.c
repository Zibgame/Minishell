/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:40:42 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/16 11:46:24 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**build_argv(t_cmd *cmd)
{
	char	**argv;
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = cmd;
	while (tmp && tmp->type == ARGUMENT)
	{
		i++;
		tmp = tmp->next;
	}
	argv = malloc(sizeof(char *) * (i + 2));
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(cmd->name);
	i = 1;
	tmp = cmd->next;
	while (tmp && tmp->type == ARGUMENT)
	{
		argv[i++] = ft_strdup(tmp->name);
		tmp = tmp->next;
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
