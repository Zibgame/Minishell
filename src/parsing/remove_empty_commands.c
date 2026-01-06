/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empty_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:51:39 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/06 13:51:55 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_empty_unquoted(t_cmd *cmd)
{
	if (!cmd || !cmd->name)
		return (0);
	if (cmd->quote)
		return (0);
	return (cmd->name[0] == '\0');
}

void	remove_empty_commands(t_cmd **head)
{
	t_cmd	*cur;
	t_cmd	*next;

	cur = *head;
	while (cur)
	{
		next = cur->next;
		if (is_empty_unquoted(cur))
		{
			if (cur->prev)
				cur->prev->next = cur->next;
			else
				*head = cur->next;
			if (cur->next)
				cur->next->prev = cur->prev;
			ft_cmddelone(cur);
		}
		cur = next;
	}
}

