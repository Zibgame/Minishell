/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:58:37 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/22 17:30:39 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd_pipe(void)
{
	char	buf[2048];
	char	*path;

	path = getcwd(buf, sizeof(buf));
	if (!path)
	{
		ft_putstr_fd("pwd: error retrieving current directory\n", STDERR_FILENO);
		return (1);
	}
	ft_putstr_fd(path, STDOUT_FILENO);
	write(1, "\n", 1);
	return (0);
}
