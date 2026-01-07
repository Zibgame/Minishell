/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:42:14 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/07 15:36:05 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == R_IN)
		{
			fd = open(r->target, O_RDONLY);
			if (fd < 0)
			{
				if (!builtin_uses_stdin(cmd->type))
				{
					r = r->next;
					continue;
				}
				return (perror(r->target), 1);
			}
		}
		else if (r->type == R_OUT)
			fd = open(r->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (r->type == R_APPEND)
			fd = open(r->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = r->fd;
		if (fd < 0)
			return (perror(r->target), 1);
		if (r->type == R_IN || r->type == R_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		r = r->next;
	}
	return (0);
}

