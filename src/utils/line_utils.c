/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:05:42 by aeherve           #+#    #+#             */
/*   Updated: 2026/01/20 10:11:39 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**cmdtoarg(t_cmd *cmd)
{
	int		i;
	char	**tmp;

	if (!cmd)
		return (NULL);
	tmp = ft_calloc(ft_cmdsize(cmd) + 1, sizeof(char *));
	if (!tmp)
		return (NULL);
	i = 0;
	while (cmd)
	{
		tmp[i] = ft_strdup(cmd->name);
		i++;
		cmd = cmd->next;
	}
	return (tmp);
}

static int	join_elems(char **args, char **new_line, int i)
{
	char	*tmp;

	while (args[i])
	{
		tmp = join_and_free(*new_line, args[i]);
		if (!tmp)
			break ;
		*new_line = tmp;
		if (args[i + 1])
		{
			tmp = join_and_free(*new_line, " ");
			if (!tmp)
				break ;
			*new_line = tmp;
		}
		free(args[i]);
		i++;
	}
	return (i);
}

void	recreate_line(t_shell *shell, char **line)
{
	int		i;
	char	**args;
	char	*new_line;

	args = cmdtoarg(shell->cmd);
	if (!args)
		return ;
	new_line = ft_calloc(1, sizeof(char));
	if (!new_line)
		return (free_array(args));
	i = join_elems(args, &new_line, 0);
	while (args[i])
		free(args[i++]);
	free(args);
	free(*line);
	*line = new_line;
}
