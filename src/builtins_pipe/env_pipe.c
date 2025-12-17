/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:58:12 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/17 10:58:18 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_pipe(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], STDOUT_FILENO);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
