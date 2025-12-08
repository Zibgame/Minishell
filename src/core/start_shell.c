/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:49:19 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/08 15:16:19 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	start_shell(t_shell *shell)
{
	(void)shell;
	printf("\n");
	cat("src/utils/header.txt");
	printf("\n");
	init_signal();
	shell_loop(shell);
}
