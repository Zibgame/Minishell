/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 22:49:34 by dadoune           #+#    #+#             */
/*   Updated: 2026/01/01 23:13:27 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_redirect(t_shell *shell)
{
	t_cmd	*tmp;
	
	if (shell)
	{
		tmp = shell->cmd;
		while (tmp && tmp->type != PIPE)
		{
			if (tmp->type == REDIRECTION)
				return (1);
			tmp = tmp->next;
		}
	}
	return(0);
}

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == R_IN)
			fd = open(r->filename, O_RDONLY);
		else if (r->type == R_OUT)
			fd = open(r->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (r->type == R_APPEND)
			fd = open(r->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (r->type == R_HEREDOC)
			fd = r->fd;

		if (fd < 0)
			return (perror(r->filename), -1);

		if (r->type == R_IN || r->type == R_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);

		close(fd);
		r = r->next;
	}
	return (0);
}
