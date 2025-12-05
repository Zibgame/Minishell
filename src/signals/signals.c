/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:44:17 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/05 10:31:04 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\nminishell> ", 12);
	}
	return ;
}

void	init_signal(void)
{
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, SIG_IGN);
	return ;
}
