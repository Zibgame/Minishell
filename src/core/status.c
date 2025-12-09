/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:44:35 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/09 11:46:11 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_status(t_shell *shell)
{
	ft_putnbr_fd(shell->last_return, 1);
	ft_putchar_fd('\n', 1);
}
