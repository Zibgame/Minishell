/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:09:44 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/19 13:54:57 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_redirs(t_shell *shell, t_redir *r)
{
	while (r)
	{
		if (r->type == R_HEREDOC)
		{
			r->fd = handle_heredoc(shell, r->target);
			if (r->fd < 0)
				return ;
		}
		r = r->next;
	}
}

void	prepare_heredocs(t_shell *shell, t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->redirs)
			process_redirs(shell, cmd->redirs);
		cmd = get_next_cmd(cmd);
	}
}
