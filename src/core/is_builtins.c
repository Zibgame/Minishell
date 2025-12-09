/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:06:21 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/09 10:59:51 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtins(char *name)
{
	if (!name)
		return (0);
	if (!ft_strncmp(name, "echo", 4))
		return (1);
	if (!ft_strncmp(name, "cd", 2))
		return (1);
	if (!ft_strncmp(name, "pwd", 3))
		return (1);
	if (!ft_strncmp(name, "export", 6))
		return (1);
	if (!ft_strncmp(name, "unset", 5))
		return (1);
	if (!ft_strncmp(name, "env", 3))
		return (1);
	if (!ft_strncmp(name, "exit", 4))
		return (1);
	if (!ft_strncmp(name, "clear", 5))
		return (1);
	return (0);
}
