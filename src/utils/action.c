/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:36:59 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/17 20:11:14 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear(void)
{
	printf("\e[1;1H\e[2J");
	print_header("src/utils/header.txt");
	return ;
}

t_cmd	*get_next_cmd(t_cmd *cmd)
{
	while (cmd && cmd->type != PIPE)
		cmd = cmd->next;
	if (cmd && cmd->type == PIPE)
		cmd = cmd->next;
	return (cmd);
}
