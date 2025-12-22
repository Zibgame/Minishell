/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:51:08 by dadoune           #+#    #+#             */
/*   Updated: 2025/12/22 12:14:47 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expansion(t_cmd *cmd, t_shell *shell)
{
	// char	*env_var;
	
	// env_var = get_value(shell, cmd->name);
	printf("Got there\n");	
	(void)cmd;
	(void)shell;
	// check if variable exists
	//expand :
	//		actual type = -2 (to remove)
	// 		
	//		add_comands: without redir or pipes
	//		
}
