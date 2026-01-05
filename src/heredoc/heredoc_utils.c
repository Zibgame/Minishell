/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:09:44 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/05 14:09:46 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_redirs(t_redir *r)
{
	while (r)
	{
		if (r->type == R_HEREDOC)
		{
			r->fd = handle_heredoc(r->target);
			if (r->fd < 0)
				return ;
		}
		r = r->next;
	}
}

void	prepare_heredocs(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->redirs)
			process_redirs(cmd->redirs);
		cmd = get_next_cmd(cmd);
	}
}
