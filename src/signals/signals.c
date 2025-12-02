/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:44:17 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/02 08:53:17 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
