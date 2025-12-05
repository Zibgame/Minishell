/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:06:21 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/05 16:20:36 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtins(char *line)
{
	if (!line)
		return (0);
	if (ft_strncmp(line, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(line, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(line, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(line, "export", 7) == 0)
		return (1);
	if (ft_strncmp(line, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(line, "env", 4) == 0)
		return (1);
	if (ft_strncmp(line, "exit", 5) == 0)
		return (1);
	return (0);
}
