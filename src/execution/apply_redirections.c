/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:42:14 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/15 13:32:15 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	apply_redirections(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (open_all_redirections(cmd))
		return (1);
	dup_redirections(cmd);
	return (0);
}

int	open_all_redirections(t_cmd *cmd)
{
	t_redir	*r;

	if (!cmd)
		return (0);
	r = cmd->redirs;
	while (r)
	{
		if (r->type == R_IN)
			r->fd = open(r->target, O_RDONLY);
		else if (r->type == R_OUT)
			r->fd = open(r->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (r->type == R_APPEND)
			r->fd = open(r->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (r->fd < 0)
		{
			perror(r->target);
			while (cmd->redirs)
			{
				if (cmd->redirs->fd >= 0)
					close(cmd->redirs->fd);
				cmd->redirs->fd = -1;
				cmd->redirs = cmd->redirs->next;
			}
			return (1);
		}
		r = r->next;
	}
	return (0);
}

void	dup_redirections(t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == R_IN || r->type == R_HEREDOC)
			dup2(r->fd, STDIN_FILENO);
		else
			dup2(r->fd, STDOUT_FILENO);
		close(r->fd);
		r = r->next;
	}
}
