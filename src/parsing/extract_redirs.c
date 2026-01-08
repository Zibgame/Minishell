/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:22:40 by aeherve           #+#    #+#             */
/*   Updated: 2026/01/08 22:24:41 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_redir_type(char *name)
{
	if (!name)
		return (-1);
	if (!ft_strncmp(name, "<", 2))
		return (R_IN);
	if (!ft_strncmp(name, ">", 2))
		return (R_OUT);
	if (!ft_strncmp(name, ">>", 3))
		return (R_APPEND);
	if (!ft_strncmp(name, "<<", 3))
		return (R_HEREDOC);
	return (-1);
}

static int	safe_add_redir(t_cmd *cmd, int type, char *filename)
{
	t_redir	*new;

	new = redir_new(type, filename);
	if (!new)
		return (0);
	redir_add_back(&cmd->redirs, new);
	return (1);
}

static void	unlink_tokens(t_cmd **head, t_cmd *first, t_cmd *second)
{
	t_cmd	*prev;
	t_cmd	*next;

	prev = first->prev;
	next = second->next;
	if (prev)
		prev->next = next;
	else
		*head = next;
	if (next)
		next->prev = prev;
	ft_cmddelone(first);
	ft_cmddelone(second);
}

void	extract_redirections(t_cmd *cmd)
{
	t_cmd	*cur;
	t_cmd	*file;
	int		type;

	if (!cmd)
		return;
	cur = cmd;
	while (cur)
	{
		if (cur->type == REDIRECTION)
		{
			file = cur->next;
			type = get_redir_type(cur->name);
			if (!file || type == -1)
				return;
			if (!safe_add_redir(cmd, type, file->name))
				return;
			unlink_tokens(&cmd, cur, file);
			cur = cmd;
		}
		else
			cur = cur->next;
	}
}
